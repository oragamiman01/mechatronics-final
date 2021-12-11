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

int mode = 0;
int temp = millis();

void loop() 
{ 

  switch (mode) { 
    case (0): Function.Spiral_Mode();
    case (1): Function.Obstacle_Mode();
  }
  
  if (millis() - temp >= 10000) {
    if (mode == 0) {
      mode = 1;
    } else {
      mode = 0;
    }
    temp = millis();
  }
}
