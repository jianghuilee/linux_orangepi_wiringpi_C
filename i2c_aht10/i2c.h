#include<wiringPi.h>
#include<stdio.h>
#include<stdbool.h>
// ---------define--------
#define i2c_scl	5//填写对应的管脚
#define i2c_sda	7//填写对应的管脚
// #define i2c_addr //填写对应address
// ---------function_define--------
char i2c_serch();
void i2c_start();
void i2c_stop();
void init();
void i2c_WriteByte(char );
int i2c_wait_ack();
void i2c_ack(bool );
