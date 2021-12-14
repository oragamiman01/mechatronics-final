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
unsigned long temp = millis();
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
  
while (millis() - temp < 5000) {
  Function.Spiral_Mode(obstacle_encountered, in_startup);
}
in_startup = false;
obstacle_encountered = false;
}


void loop() 
{ 
  if (millis() - temp >= 100) {
    temp = millis();
    while (!obstacle_encountered) {
      Function.Spiral_Mode(obstacle_encountered, in_startup);
    }
    Function.Obstacle_Mode();
  }

  /*
  switch (mode) { 
    case (0): Function.Follow_Mode();
    case (1): Function.Obstacle_Mode();
    case (2): Function.Spiral_Mode();
  }
  
  if (millis() - temp >= 10000) {
    if (mode == 0) {
      mode = 1;
    } else {
      mode = 0;
    }
    temp = millis();
  }
  */
}
