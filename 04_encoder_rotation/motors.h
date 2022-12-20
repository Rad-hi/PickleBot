#ifndef __DRIVE_H__
  #define __DRIVE_H__

  #include "config.h"

  void setup_motors(){
    pinMode(MOTOR_1_INPUT_1, OUTPUT);
    pinMode(MOTOR_1_INPUT_2, OUTPUT);
    pinMode(MOTOR_2_INPUT_1, OUTPUT);
    pinMode(MOTOR_2_INPUT_2, OUTPUT);
    pinMode(ENABLE_1_PIN, OUTPUT);
    pinMode(ENABLE_2_PIN, OUTPUT);
  }

  void forward(uint8_t speed_l, uint8_t speed_r){
    /* The pin numbers and high, low values might be different depending on your connections */
    digitalWrite(MOTOR_1_INPUT_1, LOW);
    digitalWrite(MOTOR_1_INPUT_2, HIGH);
    digitalWrite(MOTOR_2_INPUT_1, LOW);
    digitalWrite(MOTOR_2_INPUT_2, HIGH);
    analogWrite(ENABLE_1_PIN, speed_r); 
    analogWrite(ENABLE_2_PIN, speed_l); 
  }
  
  void reverse(uint8_t speed_l, uint8_t speed_r){
    /* The pin numbers and high, low values might be different depending on your connections */
    digitalWrite(MOTOR_1_INPUT_1, HIGH);
    digitalWrite(MOTOR_1_INPUT_2, LOW);
    digitalWrite(MOTOR_2_INPUT_1, HIGH);
    digitalWrite(MOTOR_2_INPUT_2, LOW);
    analogWrite(ENABLE_1_PIN, speed_r); 
    analogWrite(ENABLE_2_PIN, speed_l);
  }
  
  void right(uint8_t speed_l, uint8_t speed_r){
    /* The pin numbers and high, low values might be different depending on your connections */
    digitalWrite(MOTOR_1_INPUT_1, LOW);
    digitalWrite(MOTOR_1_INPUT_2, HIGH);
    digitalWrite(MOTOR_2_INPUT_1, LOW);
    digitalWrite(MOTOR_2_INPUT_2, LOW);
    analogWrite(ENABLE_1_PIN, speed_r); 
    analogWrite(ENABLE_2_PIN, speed_l);
  }
  
  void left(uint8_t speed_l, uint8_t speed_r){
    /* The pin numbers and high, low values might be different depending on your connections */
    digitalWrite(MOTOR_1_INPUT_1, LOW);
    digitalWrite(MOTOR_1_INPUT_2, LOW);
    digitalWrite(MOTOR_2_INPUT_1, LOW);
    digitalWrite(MOTOR_2_INPUT_2, HIGH);
    analogWrite(ENABLE_1_PIN, speed_r); 
    analogWrite(ENABLE_2_PIN, speed_l);
  }
  
  void sharp_left(uint8_t speed_l, uint8_t speed_r){
    /* The pin numbers and high, low values might be different depending on your connections */
    digitalWrite(MOTOR_1_INPUT_1, LOW);
    digitalWrite(MOTOR_1_INPUT_2, HIGH);
    digitalWrite(MOTOR_2_INPUT_1, HIGH);
    digitalWrite(MOTOR_2_INPUT_2, LOW);
    analogWrite(ENABLE_1_PIN, speed_r); 
    analogWrite(ENABLE_2_PIN, speed_l);
  }
  
  void sharp_right(uint8_t speed_l, uint8_t speed_r){
    /* The pin numbers and high, low values might be different depending on your connections */
    digitalWrite(MOTOR_1_INPUT_1, HIGH);
    digitalWrite(MOTOR_1_INPUT_2, LOW);
    digitalWrite(MOTOR_2_INPUT_1, LOW);
    digitalWrite(MOTOR_2_INPUT_2, HIGH);
    analogWrite(ENABLE_1_PIN, speed_r); 
    analogWrite(ENABLE_2_PIN, speed_l);
  }
  
  void stop_(){
    /* The pin numbers and high, low values might be different depending on your connections */
    digitalWrite(MOTOR_1_INPUT_1, LOW);
    digitalWrite(MOTOR_1_INPUT_2, LOW);
    digitalWrite(MOTOR_2_INPUT_1, LOW);
    digitalWrite(MOTOR_2_INPUT_2, LOW);
    analogWrite(ENABLE_1_PIN, 0); 
    analogWrite(ENABLE_2_PIN, 0); 
  }
  
#endif // __DRIVE_H__
