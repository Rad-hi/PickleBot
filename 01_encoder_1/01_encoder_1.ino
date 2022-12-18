#include "config.h"

#define ENABLE_DEBUG /* <-- Commenting this line will remove any trace of debug printing */
#include <MacroDebugger.h>
#include <MyCountingButton.h>

MyCountingButton isr_counting_btn_left, isr_counting_btn_right;

void setup() {
  
  DEBUG_BEGIN();

  // Begin the counting objects
  isr_counting_btn_left.beginCountingInterrupter(LEFT_ENCODER_PIN, 
                                                 GET_ISR(isr_counting_btn_left, countingInterruption), 
                                                 ASCENDING, 
                                                 RISING);

  isr_counting_btn_right.beginCountingInterrupter(RIGHT_ENCODER_PIN, 
                                                  GET_ISR(isr_counting_btn_right, countingInterruption), 
                                                  ASCENDING, 
                                                  RISING);
  }

void loop() {
  // The loopCounter function must be called as frequently as possible
  isr_counting_btn_left.loopCounter();
  isr_counting_btn_right.loopCounter();
  
  DEBUG_I("l: %d, r: %d", isr_counting_btn_left.getCount(), isr_counting_btn_right.getCount());
}
