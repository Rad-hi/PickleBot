#include "config.h"

/* Functions prototypes */
void forward(uint8_t speed);
void reverse(uint8_t speed);
void stop_();

void setup() {
  pinMode(MOTOR_1_INPUT_1, OUTPUT);
  pinMode(MOTOR_1_INPUT_2, OUTPUT);
  pinMode(MOTOR_2_INPUT_1, OUTPUT);
  pinMode(MOTOR_2_INPUT_2, OUTPUT);
  pinMode(ENABLE_1_PIN, OUTPUT);
  pinMode(ENABLE_2_PIN, OUTPUT);
}

void loop() {
  forward(100);
  // Estimated sleep time for the robot to go 1 meter
  // please note that this highly depends from the way the motor is constructed
  // and the battery voltage. Don't use this method ever (unless for a one time thing)
  delay(4700);
  stop_();

  delay(2000);
    
  reverse(100);
  delay(4700);
  stop_();
  
  while(1);
}

void forward(uint8_t speed){
  /* The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);
  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);
  analogWrite(ENABLE_1_PIN, speed);
  analogWrite(ENABLE_2_PIN, speed); //Right Motor Speed
}

void reverse(uint8_t speed){
  /* The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, LOW);
  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, LOW);
  analogWrite(ENABLE_1_PIN, speed); //Left Motor Speed
  analogWrite(ENABLE_2_PIN, speed); //Right Motor Speed
}

void stop_(){
  /* The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, LOW);
  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, LOW);
  analogWrite(ENABLE_1_PIN, 0); //Left Motor Speed
  analogWrite(ENABLE_2_PIN, 0); //Right Motor Speed
}
