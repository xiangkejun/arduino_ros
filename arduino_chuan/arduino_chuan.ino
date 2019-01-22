//xx

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include "motor.h"
void  motor_init();
void turn(int val);
void go(double val);

ros::NodeHandle  nh;
double vx,vw;

void vel_back( const geometry_msgs::Twist& msg){
  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led  13
  vx = msg.linear.x;
  vw = msg.angular.z;
Serial.print("vx= ");
Serial.print(vx);
Serial.print("vw= ");
Serial.print(vw);
  go(1000*vx);
  turn(200*vw);
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel_mux/input/teleop", &vel_back );



void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  motor_init();
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}

