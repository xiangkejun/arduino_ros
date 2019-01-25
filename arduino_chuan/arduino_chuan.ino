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
//float getdegree();
float get_true_degree();


ros::NodeHandle  nh;

double vx,vw;
//float cur_angle = 0.0;
float now_angle;
int guizheng_flag = 0;

void chuan_go()
{
   if(guizheng_flag == 1)   //归正
  {
    Serial.print("guizheng!!");
    if(now_angle > -5 && now_angle <5)
    {
      guizheng_flag = 0;
      turn(0);
    }
    else
    {
      turn( -now_angle);
    } 
  }
  else   //正常运行
  {
        // turn(100*vw);   //0-125    255

    if(now_angle >= -60 && now_angle <= 60)
    {
      go(600*vx);   // 0-100    255
      turn(100*vw);   //0-125    255
    }
    else 
    {
      ;
    }

  }
}

void vel_back( const geometry_msgs::Twist& msg){
  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led  13
  vx = msg.linear.x;
  vw = msg.angular.z;
//Serial.print("vx= ");
//Serial.print(vx);
//Serial.print("vw= ");
//Serial.print(vw);
//  Serial.print("cur_angle= ");
//  Serial.print(cur_angle);

  if(vx == 0.25 && vw == 1.25) //guizheng
  {
    guizheng_flag = 1;
  }

    // turn(100);
   // turn(100*vw);   //0-125    255
  chuan_go();
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel_mux/input/teleop", &vel_back );


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
 // cur_angle = getdegree();
  now_angle = get_true_degree();

  
  Serial.print("now_angle= ");
  Serial.print(now_angle);

 // chuan_go();
  
  delay(1);  //ms
}
