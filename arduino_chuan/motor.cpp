#include "motor.h"
#include "Arduino.h"

  int motor_go=9;
  int INA=22;   //  digtial pin22
  int INB=23;   //digtial pin23
  int TURN_MOTOR=10;

void motor_init()
{
  pinMode(motor_go,OUTPUT);

  pinMode(INA,OUTPUT);
  pinMode(INB,OUTPUT);
  pinMode(TURN_MOTOR,OUTPUT);
}
void go(double val)
{
  if(val >= 0)
  {
      analogWrite(motor_go,val);
  }
  else
  {
    ;
  }
}
void turn(int val)
{
  if(val > 0){ //left
    digitalWrite(INA,HIGH);
    digitalWrite(INB,LOW);
    analogWrite(TURN_MOTOR,val);
  }
  if(val <= 0)  //right
  {
    digitalWrite(INA,LOW);
    digitalWrite(INB,HIGH);
    analogWrite(TURN_MOTOR,-val);  
  }
  
}
