//xx
//as5045b
#include "Arduino.h"

int CLK = 24;  //clk
//const int DIO = A0;
int DIO = 25;
int CSN = 26;
//int PROG = 27;
void encoder_init()
{
  pinMode(CLK, OUTPUT);
  pinMode(DIO, INPUT);
  pinMode(CSN, OUTPUT);
//  pinMode(PROG,OUTPUT);
}


#define CSN_H digitalWrite(CSN,HIGH)
#define CLK_H digitalWrite(CLK,HIGH)
#define CSN_L digitalWrite(CSN,LOW)
#define CLK_L digitalWrite(CLK,LOW)
#define DIO_in   digitalRead(DIO)   //HIGH=1 /LOW=0

unsigned int data_p = 0;
unsigned int out = 0;
unsigned int data_read()
{
  unsigned char i;
  data_p = 0;
  CSN_H;
  CLK_H;
  delayMicroseconds(100);  //us
  CSN_L;
  delayMicroseconds(100);
  CLK_L;
  delayMicroseconds(100);
  for(i=0;i<12;i++)
  {
    CLK_H;
    delayMicroseconds(100);
    if(DIO_in)
    {
      data_p = data_p << 1;
      data_p |= 0x0001;
    }
    else
    {
      data_p = data_p <<1;
      data_p &= 0xfffe;
    }
    CLK_L;
    delayMicroseconds(100);
  }
  out = data_p;
  delayMicroseconds(100);
  CSN_H;
  CLK_H;
  delayMicroseconds(100);
  return out;
}

float getdegree()  //当前绝对角度
{
  float angle;
  angle = data_read();
  return angle*360.0/4096.0;
}



static int num_of_turn = 0;  //编码器圈数
float  zero_angle = 180;   //零位初始值
float get_true_degree()
{
  float cur_angle = 0.0,pre_angle = 0.0,incr_angle;
  
  cur_angle = getdegree();
  incr_angle = cur_angle - pre_angle;
  pre_angle = cur_angle;
  if(incr_angle < -300)  //跳变
  {
    num_of_turn++;
  }
  else if(incr_angle > 300) //跳变
  {
    num_of_turn--;
  }
  return ((cur_angle + 360.0*num_of_turn)-zero_angle)*0.5;
}

