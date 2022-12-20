#include "encoder_AB.h" 
#include "config.h"
#include "motors.h"
#include "pickle_wifi.h"
#include "ota.h"

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
  // Make a 90° turn
  while(right_wheel_encoder->get_count() < GET_COUNT_TO_TURN_ALPHA_DEG(45.0)
     && left_wheel_encoder->get_count() > GET_COUNT_TO_TURN_ALPHA_DEG(-45.0)){    
    sharp_left(ROBOT_SPEED, ROBOT_SPEED);
  }

  // Make another 90° turn
  int32_t r_count = right_wheel_encoder->get_count();
  int32_t l_count = left_wheel_encoder->get_count();
  while(right_wheel_encoder->get_count() - r_count < GET_COUNT_TO_TURN_ALPHA_DEG(45.0)
     && left_wheel_encoder->get_count() - l_count > GET_COUNT_TO_TURN_ALPHA_DEG(-45.0)){    
    sharp_left(ROBOT_SPEED, ROBOT_SPEED);
  }

  //Go back 180°
  r_count = right_wheel_encoder->get_count();
  l_count = left_wheel_encoder->get_count();
  while(right_wheel_encoder->get_count() - r_count > GET_COUNT_TO_TURN_ALPHA_DEG(-90.0)
     && left_wheel_encoder->get_count() - l_count < GET_COUNT_TO_TURN_ALPHA_DEG(90.0)){
    sharp_right(ROBOT_SPEED, ROBOT_SPEED);
  }

  // Stop forever
  stop_();
  while(1);
}
