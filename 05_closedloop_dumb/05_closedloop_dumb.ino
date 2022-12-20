#include "encoder_AB.h" 
#include "config.h"
#include "motors.h"

// Encoder objects for each wheel
encoder_ab *right_wheel_encoder;
encoder_ab *left_wheel_encoder;

void setup() {
  // Launch non-blocking tasks that listen for the firmware update requests
  setup_wifi();
  setup_OTA_firmware_update();
  
  right_wheel_encoder = new encoder_ab();
  right_wheel_encoder->begin(RIGHT_ENCODER_A_PIN, RIGHT_ENCODER_B_PIN, 
                             GET_ISR_ENC(right_wheel_encoder, handle_interrupt_A),
                             GET_ISR_ENC(right_wheel_encoder, handle_interrupt_B));

  left_wheel_encoder = new encoder_ab();
  left_wheel_encoder->begin(LEFT_ENCODER_A_PIN, LEFT_ENCODER_B_PIN, 
                            GET_ISR_ENC(left_wheel_encoder, handle_interrupt_A),
                            GET_ISR_ENC(left_wheel_encoder, handle_interrupt_B));

  setup_motors();
}

void loop() {

  uint8_t l_speed = ROBOT_SPEED;
  uint8_t r_speed = ROBOT_SPEED;

  uint32_t r_count, l_count, diff_l, diff_r;

  r_count = right_wheel_encoder->get_count();
  l_count = left_wheel_encoder->get_count();
  
  // Go 1 meter forward
  while(right_wheel_encoder->get_count() < GET_COUNT_TO_TRAVEL_DIST(1.0)
     && left_wheel_encoder->get_count() < GET_COUNT_TO_TRAVEL_DIST(1.0)){    

    forward(l_speed, r_speed);

    diff_l = left_wheel_encoder->get_count() - l_count;
    l_count = left_wheel_encoder->get_count();

    diff_r = right_wheel_encoder->get_count() - r_count;
    r_count = right_wheel_encoder->get_count();
    
    if(diff_r > diff_l){
      r_speed -= 1;
      l_speed += 1;
    }
    else{
      r_speed += 1;
      l_speed -= 1;
    }

    // Give time for the motors to respond to the changes
    delay(20);
  }

  // Stop forever
  stop_();
  while(1);
}
