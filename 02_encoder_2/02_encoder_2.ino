#include "encoder_AB.h" 
#include "config.h"

#define ENABLE_DEBUG /* <-- Commenting this line will remove any trace of debug printing */
#include <MacroDebugger.h>

// Encoder objects for each wheel
encoder_ab *right_wheel_encoder;
encoder_ab *left_wheel_encoder;

void setup() {
  DEBUG_BEGIN();
  
  left_wheel_encoder = new encoder_ab();
  left_wheel_encoder->begin(LEFT_ENCODER_A_PIN, LEFT_ENCODER_B_PIN, 
                            GET_ISR_ENC(left_wheel_encoder, handle_interrupt_A),
                            GET_ISR_ENC(left_wheel_encoder, handle_interrupt_B));
                            
  right_wheel_encoder = new encoder_ab();
  right_wheel_encoder->begin(RIGHT_ENCODER_A_PIN, RIGHT_ENCODER_B_PIN, 
                             GET_ISR_ENC(right_wheel_encoder, handle_interrupt_A),
                             GET_ISR_ENC(right_wheel_encoder, handle_interrupt_B));

}

void loop() {
  DEBUGLN("l: %d, r: %d", left_wheel_encoder->get_count(), right_wheel_encoder->get_count());
}
