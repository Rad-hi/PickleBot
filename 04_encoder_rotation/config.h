#ifndef __CONFIG_H__
  #define __CONFIG_H__

  #define ROBOT_SPEED                         140
    
  // Pins
  #define ENABLE_1_PIN                        14
  #define MOTOR_1_INPUT_1                     27
  #define MOTOR_1_INPUT_2                     26
  #define MOTOR_2_INPUT_1                     25
  #define MOTOR_2_INPUT_2                     33
  #define ENABLE_2_PIN                        32
  #define LEFT_ENCODER_A_PIN                  18
  #define LEFT_ENCODER_B_PIN                  19
  #define RIGHT_ENCODER_A_PIN                 34
  #define RIGHT_ENCODER_B_PIN                 35

  // Vehicle's config
  #define WHEEL_RADIUS                        0.0325f // in meters
  #define WHEEL_CIRCUMFERENCE                 ((PI) * 2 * (WHEEL_RADIUS))
  #define BASELINE_DISTANCE                   0.350f // Distance between the two wheels in meters

  // Kinematics parameters
  #define TICKS_PER_ROTATION                  80

  #define GET_COUNT_TO_TRAVEL_DIST(DIST)      (int32_t)(((float)(DIST)/(float)(WHEEL_CIRCUMFERENCE))*(TICKS_PER_ROTATION))
  #define GET_COUNT_TO_TURN_ALPHA_DEG(ALPHA)  ( GET_COUNT_TO_TRAVEL_DIST((ALPHA)*(PI/180)*(BASELINE_DISTANCE/2)) )
  #define GET_COUNT_TO_TURN_ALPHA_RAD(ALPHA)  ( GET_COUNT_TO_TRAVEL_DIST((ALPHA)*(BASELINE_DISTANCE/2)) )

  /* OTA params */
  #define WIFI_SSID                           "tsyp"
  #define WIFI_PASSWORD                       "66669420"
  #define OTA_IP                              192,168,103,69

#endif // __CONFIG_H__
