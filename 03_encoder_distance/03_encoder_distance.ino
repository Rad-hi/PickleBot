#include "encoder_AB.h" 
#include "config.h"
#include "motors.h"

// Encoder objects for each wheel
encoder_ab *right_wheel_encoder;
encoder_ab *left_wheel_encoder;

void setup() {
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

  // Go 1 meter forward
  while(right_wheel_encoder->get_count() < GET_COUNT_TO_TRAVEL_DIST(1.0)
     && left_wheel_encoder->get_count() < GET_COUNT_TO_TRAVEL_DIST(1.0)){    
    forward(ROBOT_SPEED, ROBOT_SPEED);
  }

  stop_();
  delay(2000);

  // Go 1 meter backwards
  int32_t r_count = right_wheel_encoder->get_count();
  int32_t l_count = left_wheel_encoder->get_count();
  while(right_wheel_encoder->get_count() - r_count > GET_COUNT_TO_TRAVEL_DIST(-1.0)
     && left_wheel_encoder->get_count() - l_count > GET_COUNT_TO_TRAVEL_DIST(-1.0)){
    reverse(ROBOT_SPEED, ROBOT_SPEED);
  }

  // Stop forever
  stop_();
  while(1);
}
