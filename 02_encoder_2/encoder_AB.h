/*
 * Single file class for the AB encoder functionalities
 */

#ifndef __ENCODER_AB_H__
  #define __ENCODER_AB_H__

  #include "Arduino.h"

  #define PIN_A_SET_BMSK                  0x01 // 0000 0001
  #define PIN_B_SET_BMSK                  0x02 // 0000 0010

  // Macros used to update the ticks counter appropriately
  #define CLOCKWISE(COUNTER)              ((COUNTER)++)
  #define ANTI_CLOCKWISE(COUNTER)         ((COUNTER)--)

  #define GET_ISR_ENC(ENC_PTR, ENC_ISR)   ([]{(ENC_PTR->ENC_ISR)();})

  /* ---------------------------------------------- */
  /* ----------------- CLASS BODY ----------------- */
  /* ---------------------------------------------- */
  
  class encoder_ab{
    private:

      uint8_t _irq_pin_A, _irq_pin_B;
      volatile uint8_t _pin_state;
      volatile long _counter; // Ticks' counter

      void (*ISR_callback_A)(void);
      void (*ISR_callback_B)(void);
      
    public:

      void begin(uint8_t irq_pin_A, uint8_t irq_pin_B, 
                               void (*ISR_callback_A)(void), void (*ISR_callback_B)(void));
      void handle_interrupt_A(void);
      void handle_interrupt_B(void);
      
      long get_count();
      void reset_count();
  };

  /* --------------------------------------------------- */
  /* ----------------- CLASS FUNCTIONS ----------------- */
  /* --------------------------------------------------- */

  // Interrupt pin A, Interrupt pin B, ISR A, ISR B
  // Ref: https://forum.arduino.cc/t/attachinterrupts-callback-method-from-a-c-class/461957/6
  void encoder_ab :: begin(uint8_t irq_pin_A, uint8_t irq_pin_B, 
                           void (*ISR_callback_A)(void), void (*ISR_callback_B)(void)){
    _irq_pin_A = irq_pin_A,_irq_pin_B = irq_pin_B;

    // Read pins to determine Falling/Rising edge
    pinMode(_irq_pin_A, INPUT_PULLUP);
    pinMode(_irq_pin_B, INPUT_PULLUP);
    
    // We want to detect both rising and falling edges for both pins --> direction
    attachInterrupt(digitalPinToInterrupt(_irq_pin_A), ISR_callback_A, CHANGE);
    attachInterrupt(digitalPinToInterrupt(_irq_pin_B), ISR_callback_B, CHANGE);
    _pin_state = _counter = 0;
  }

  // Ref: https://github.com/EwingKang/Simple-ROS-Arduino-odometry/blob/master/arduino_files/serial_odom/wheel_type_four.cpp
  // ISR for the change in pin A
  inline void encoder_ab :: handle_interrupt_A(void){
    if(digitalRead(_irq_pin_A)){ // Rising A
      if(_pin_state & PIN_A_SET_BMSK) return; // A already set as HIGH --> return
      if(_pin_state & PIN_B_SET_BMSK) CLOCKWISE(_counter); // A was HIGH (rised and fell) and B HIGH
      else ANTI_CLOCKWISE(_counter); // A fell then rised --> reverse sense
      _pin_state |= PIN_A_SET_BMSK;
    }
    else{ // Falling A
      if( !(_pin_state & PIN_A_SET_BMSK) ) return;
      if(_pin_state & PIN_B_SET_BMSK) ANTI_CLOCKWISE(_counter);
      else CLOCKWISE(_counter);
      _pin_state &= ~PIN_A_SET_BMSK;  
    }
  }

  // ISR for the change in pin A
  inline void encoder_ab :: handle_interrupt_B(void){
    if(digitalRead(_irq_pin_B)){ // Rising B
      if(_pin_state & PIN_B_SET_BMSK) return;
         
      if(_pin_state & PIN_A_SET_BMSK) ANTI_CLOCKWISE(_counter);
      else CLOCKWISE(_counter);
      
      _pin_state |= PIN_B_SET_BMSK;
    }
    else{ // Falling B
      if( !(_pin_state & PIN_B_SET_BMSK) ) return;
      if(_pin_state & PIN_A_SET_BMSK) CLOCKWISE(_counter);
      else ANTI_CLOCKWISE(_counter);
      _pin_state &= ~PIN_B_SET_BMSK;
    }      
  }
  
  long encoder_ab :: get_count(){ return _counter; }
  
  void encoder_ab :: reset_count(){ _counter = 0; }

#endif // __ENCODER_AB_H__
