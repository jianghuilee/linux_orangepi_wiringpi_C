#include<wiringPi.h>
#include<stdio.h>
#include<stdbool.h>
#include"i2c.h"

unsigned char addr;
//---------define--------
#define i2c_scl	5//填写对应的管脚
#define i2c_sda	7//填写对应的管脚
#define i2c_addr  //填写对应address
//---------function_content--------

void init()//总线初始化 将总线都拉高一释放总线  发送启动信号前，要先初始化总线。即总有检测到总线空闲才开始发送启动信号  
{  
    pinMode(i2c_scl,OUTPUT); 
	pinMode(i2c_sda,OUTPUT); 
	digitalWrite(i2c_sda,1);
	digitalWrite(i2c_scl,1); 
}//i2c_scl:1  i2c_sda:1 处于空闲状态


 unsigned  char i2c_serch()
{
	i2c_start();
	printf("-------------------查找i2c设备---------------------\n");
	printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");

	int line=0;
	for(addr=0x00;addr<0x7F;addr++)
	{
		char addr_cmd=addr<<1;
		
		if(!line)
		{
				printf("00: ");
				line++;
		}
		else if(!(line%16))
		{
			printf("\n%x: ",line);
			line++;
		}
		else 
		{
			line++;
		}
	
		i2c_WriteByte(addr_cmd);
		if(i2c_wait_ack())
		{
			printf("%x ",addr);
			i2c_stop();
			i2c_start();
			
		}
		else
		{
			
			printf("-- ");
			
		}
	}
	printf("\n");
	i2c_stop();
	return addr;
}


void i2c_start()
{
	pinMode(i2c_sda,OUTPUT); 
	digitalWrite(i2c_scl,1);
	delayMicroseconds(1);
	digitalWrite(i2c_sda,1);
	delayMicroseconds(1);
	digitalWrite(i2c_sda,0);
	delayMicroseconds(1);
	// printf("i2c has started!\n");
}
//i2c_scl:--------------  
//i2c_sda:------_____ 

void i2c_stop()
{
	
	pinMode(i2c_sda,OUTPUT); 
	digitalWrite(i2c_scl,0);
	delayMicroseconds(1);
	digitalWrite(i2c_sda,0);

	digitalWrite(i2c_scl,1);
	delayMicroseconds(1);
	digitalWrite(i2c_sda,1);
	delayMicroseconds(1);
	// printf("i2c has stoped!\n");
	
}


void i2c_WriteByte(unsigned char data)
{
	
	pinMode(i2c_sda,OUTPUT);    //只有时钟线拉低，SDA上的数据才允许写入
	digitalWrite(i2c_scl,0);
	delayMicroseconds(1);
	//将数据一位一位的发出去
	for(int i =0;i<8;i++)
	{
	
		if(data&(0x1<<(7-i)))               //高位先入
			{
					digitalWrite(i2c_sda,1);
					delayMicroseconds(1);
			}
			else
			{
					digitalWrite(i2c_sda,0);
					delayMicroseconds(1);
			}
			
			 digitalWrite(i2c_scl,1);               //让外设读取数据
			delayMicroseconds(1);
		
			 digitalWrite(i2c_scl,0);                 //重新拉低，准备写入下一位数据
			 delayMicroseconds(1);
	}
}

unsigned char i2c_ReadByte()
{

	
	unsigned char data = 0;
	pinMode(i2c_sda,INPUT);
	digitalWrite(i2c_scl,0);                  //先拉低，为读取数据做准备
	delayMicroseconds(1);
	for(int i=0;i<8;i++)
	{
	
			digitalWrite(i2c_scl,1);         // SCL为高期间才可以读取数据
			delayMicroseconds(5);
		
		if(digitalRead(i2c_sda))
		{
				data|=(0x01<<(7-i));
			
		}else{
			data &= ~(0x1<<(7-i));
		}	
		digitalWrite(i2c_scl,0);
		delayMicroseconds(1);
	}
	return data;


}
void i2c_wait_ack_check()
{
	if(!i2c_wait_ack())
		printf("no ack!\n");
	
	
}
int i2c_wait_ack()
{

	pinMode(i2c_sda,INPUT);
	digitalWrite(i2c_scl,0);
	delayMicroseconds(1);
	digitalWrite(i2c_scl,1);
	if(digitalRead(i2c_sda))
	{
		// printf("no ack!\n");
		return 0;
	}
	else
	{
		return 1;	
	}
	delayMicroseconds(1);
}


void i2c_ack(bool ack_en)
{
	pinMode(i2c_sda,OUTPUT);
	digitalWrite(i2c_scl,0);
	delayMicroseconds(1);
	if(ack_en)
	{
		digitalWrite(i2c_sda,1);
	}
  else
	{
	
		digitalWrite(i2c_sda,0);
	}
	
	
	digitalWrite(i2c_scl,1);
	delayMicroseconds(1);
	
	digitalWrite(i2c_scl,0);
	delayMicroseconds(1);
}
