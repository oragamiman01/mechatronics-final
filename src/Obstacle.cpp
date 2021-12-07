#include "Obstacle.h"
#include "KalmanFilter.h"


IR IR;
Ultrasonic Ultrasonic;
extern Balanced Balanced;
extern Mpu6050 Mpu6050;
KalmanFilter kalman;

#define abs(x) ((x)>0?(x):-(x))

void Ultrasonic::Pin_init()
{
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}


char Ultrasonic ::measure_flag = 0;
unsigned long Ultrasonic ::measure_prev_time = 0;
double Ultrasonic::distance_value;

void Function::Obstacle_Mode()
{
  IR.Send();
  Ultrasonic.Get_Distance();

  if (millis() - follow_prev_time >= 100)
  {
    follow_prev_time = millis();
    Balanced.Motion_Control(FORWARD);

    if (OBSTACLE_JUDAGEMENT && If_IR_TRIGGERED && Ultrasonic::distance_value < 10)
    {
      float angle = kalman.Gyro_z;
      while (abs(angle - kalman.Gyro_z) < 90) {
        Balanced.Motion_Control(LEFT);
      }
    }

  }
    Obstacle_time = millis();
}

void IR::Check()
{
  int motion = left_is_obstacle + right_is_obstacle;
  switch (motion)
  {
    case Meet_OBSTACLE: Balanced.Motion_Control(LEFT);
      left_is_obstacle = 0; break;

    case FOLLOW_RIGHT:
      Balanced.Motion_Control(RIGHT);
      left_is_obstacle = 0; break;

    case FOLLOW_LEFT:
      Balanced.Motion_Control(LEFT);
      right_is_obstacle = 0; break;

    case FOLLOW_BACK:
      Balanced.Motion_Control(LEFT);
      right_is_obstacle = 0;
      left_is_obstacle = 0; break;
  }

}

void IR::Send()
{
  static unsigned long ir_send_time;

  if (millis() - ir_send_time > 15)
  {
    for (int i = 0; i < 39; i++)
    {
      digitalWrite(IR_SEND_PIN, LOW);
      delayMicroseconds(9);
      digitalWrite(IR_SEND_PIN, HIGH);
      delayMicroseconds(9);
    }
    ir_send_time = millis();
  }
}
