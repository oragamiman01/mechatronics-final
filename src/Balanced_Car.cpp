#include "Motor.h"
#include "Balanced.h"
#include "Obstacle.h"
#include <Arduino.h>


Timer2 Timer2;
extern Mpu6050 Mpu6050;
extern Motor Motor;
extern Balanced Balanced;
extern Ultrasonic Ultrasonic;
extern IR IR;
Function Function;
int mode = 0;
unsigned long start_time = millis();
bool obstacle_encountered = false;
bool in_startup = true;


void setup() 
{
  Motor.Pin_init();
  IR.Pin_init();
  Ultrasonic.Pin_init();
  Motor.Encoder_init();
  Timer2.init(TIMER);
  Mpu6050.init();
  Serial.begin(9600);
  delay(100);
}


void loop() 
{ 
  if (in_startup) { //Allow the robot to get balanced (2 seconds)
    Function.Obstacle_Mode();
    if (millis() - start_time > 2000) {
      in_startup = false;
    }
  } else {
    while (!obstacle_encountered) { //spiral until obstacle is encountered
      Function.Spiral_Mode(obstacle_encountered);
    }
    Function.Obstacle_Mode();
  }
}
