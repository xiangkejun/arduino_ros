//xx

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include "motor.h"
#include "encoder.h"

void  motor_init();
void turn(int val);
void go(double val);

void encoder_init();
unsigned int data_read();
float getdegree();


ros::NodeHandle  nh;

double vx,vw;
float cur_angle = 0.0;
int guizheng_flag = 0;

void vel_back( const geometry_msgs::Twist& msg){
  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led  13
  vx = msg.linear.x;
  vw = msg.angular.z;
Serial.print("vx= ");
Serial.print(vx);
Serial.print("vw= ");
Serial.print(vw);
  if(vx == 0.25 && vw == 1.25) //guizheng
  {
    guizheng_flag = 1;
  }
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel_mux/input/teleop", &vel_back );

void chuan_go()
{
   if(guizheng_flag == 1)   //归正
  {
    Serial.print("guizheng!!");
    if(cur_angle > -5 && cur_angle <5)
    {
      guizheng_flag = 0;
      turn(0);
    }
    else
    {
      turn( -cur_angle);
    } 
  }
  else   //正常运行
  {
    if(cur_angle >= -60 && cur_angle < 60)
    {
      go(1000*vx);   // 0-200    255
      turn(200*vw);   //0-200    255
    }
    else 
    {
      ;
    }

  }
}

void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  motor_init();
  encoder_init();
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  cur_angle = getdegree();

  chuan_go();
  
  delay(1);  //ms
}
