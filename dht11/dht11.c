#include<stdio.h>
#include<wiringPi.h>

#define data 5
int main()
{
wiringPiSetup();

pinMode(data,OUTPUT);
delay(1000);
digitalWrite(data,0);
delayMicroseconds(30);
pinMode(data,INPUT);

return 0;

}