#include "encoder_AB.h" 
#include "config.h"
#include "motors.h"
#include "pickle_wifi.h"
#include "ota.h"
#include "rpm_controller.h"
#define ENABLE_DEBUG /* <-- Commenting this line will remove any trace of debug printing */
#include <MacroDebugger.h>


// Encoder objects for each wheel
encoder_ab *right_wheel_encoder;
encoder_ab *left_wheel_encoder;

rpm_controller *l_rpm_cntrl = new rpm_controller(8, 0.01, 0.2, 50);
rpm_controller *r_rpm_cntrl = new rpm_controller(8, 0.01, 0.2, 50);

void setup() {
  DEBUG_BEGIN();
  
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

  // Go 1 meter forward
  while(right_wheel_encoder->get_count() < GET_COUNT_TO_TRAVEL_DIST(5.0)
     && left_wheel_encoder->get_count() < GET_COUNT_TO_TRAVEL_DIST(5.0)){

    DEBUGLN("%-3d", l_rpm_cntrl->get_pwm()); // Open the Serial plotter to see the pwm in real time

    l_rpm_cntrl->step(ROBOT_SPEED);
    r_rpm_cntrl->step(ROBOT_SPEED);

    forward(l_rpm_cntrl->get_pwm(), r_rpm_cntrl->get_pwm());
  }

  // Stop forever
  stop_();
  while(1);
}
