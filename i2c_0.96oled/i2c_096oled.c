#include "i2c_096oled.h"
#include "oled_front.h"
#include <stdio.h>
#include<stdbool.h>
#include<wiringPi.h>
unsigned char  CMD_Data[]={
0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6, 0xA8, 0x3F,
					
0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1, 0xDA, 0x12,
					
0xD8, 0x30, 0x8D, 0x14, 0xAF};

void OLED_Init()
{
	if(!OPEN_I2C_CMD())
		printf("命令总线启动失败！\n");
	else
	{
		for(int i=0; i<27;i++)
		{		
			i2c_WriteByte(CMD_Data[i]);	
			i2c_wait_ack_check();		
		}
	}		
	printf("oled 初始化完毕！\n");
	i2c_stop();
}
//命令总线启用
_Bool OPEN_I2C_CMD()
{
	i2c_start();
	i2c_WriteByte(0x3c<<1);//0x3c是地址
	if(!i2c_wait_ack())
		return false;	
	i2c_WriteByte(0x00);
	if(!i2c_wait_ack())
		return false;;
	return true;
	 
		
}

_Bool OPEN_I2C_DATA()
{
	i2c_start();
	i2c_WriteByte(0x3c<<1);//0x3c是地址
	if(!i2c_wait_ack())
		return false;	
	i2c_WriteByte(0x40);
	if(!i2c_wait_ack())
		return false;;
	return true;	
}

//向设备写控制命令,单次数据/命令传输用完需要停止
void OLED_WR_CMD(unsigned char cmd)
{
	if(!OPEN_I2C_CMD())
	printf("命令总线启动失败！\n");		
		i2c_WriteByte(cmd);	
			if(!i2c_wait_ack())
			printf("oled 传输无应答 错误！\n");
	i2c_stop();
}

//向设备写数据,单次数据/命令传输用完需要停止
void OLED_WR_DATA(unsigned char data)
{
	if(!OPEN_I2C_DATA())
	printf("数据总线启动失败！\n");	
		i2c_WriteByte(data);
			if(!i2c_wait_ack())
			printf("oled 传输无应答 错误！\n");
	i2c_stop();	
}

//关闭显示
void OLED_Display_Off()
{
	if(!OPEN_I2C_CMD())
		printf("命令总线启动失败！\n");
	else
	{
		OLED_WR_CMD(0X8D);  //SET DCDC命令
		OLED_WR_CMD(0X10);  //DCDC OFF
		OLED_WR_CMD(0XAE);  //DISPLAY OFF
	}
	i2c_stop();	
}

//开启OLED显示    
void OLED_Display_On()
{
	if(!OPEN_I2C_CMD())
		printf("命令总线启动失败！\n");
	else
	{
		OLED_WR_CMD(0X8D);  //SET DCDC命令
		OLED_WR_CMD(0X14);  //DCDC ON
		OLED_WR_CMD(0XAF);  //DISPLAY ON
	}
	i2c_stop();	
}
//设置OLED位置  
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	if(!OPEN_I2C_CMD())
		printf("命令总线启动失败！\n");
	else
	{
		OLED_WR_CMD(0xb0+y);
		OLED_WR_CMD(((x&0xf0)>>4)|0x10);
		OLED_WR_CMD(x&0x0f);
	}
	i2c_stop();
}


//清行
void OLED_Clearrow(unsigned char i)
{
	unsigned char n;
	if(!OPEN_I2C_CMD())
		printf("命令总线启动失败！\n");	
	else
	{
		i2c_WriteByte(0xb0+i);
		i2c_WriteByte (0x00); 
		i2c_WriteByte (0x10);
		i2c_stop(); 
		if(!OPEN_I2C_DATA())
			printf("数据总线启动失败！\n");
		else
		{
			for(n=0;n<128;n++)
			{
				i2c_WriteByte(0x00);
			}	
			i2c_stop(); 
		}
	}
	
		
}

//清屏size12 size16要清两行，其他函数有类似情况
void OLED_Clear()
{
	unsigned char  i,n;	
	for(i=0;i<8;i++)  
		{  
		if(!OPEN_I2C_CMD())
			printf("命令总线启动失败！\n");
		else
		{	
			i2c_WriteByte(0xb0+i);	
			i2c_WriteByte(0x00);	
			i2c_WriteByte(0x10);	 
			i2c_stop();	//命令传输完成，此处需要切换成数据传输模式
		}	
		if(!OPEN_I2C_DATA())
			printf("数据总线启动失败！\n");
		else
		{	
			for(int n=0; n<128;n++)
			{		
				i2c_WriteByte(0x00);	
				if(!i2c_wait_ack())
				{
					printf("oled 传输无应答 错误！\n");
					break;
				}
				
			}
			i2c_stop();//数据传输完成，此处需要切换成命令传输模式
		}	
									
	} 	


printf("oled 清屏完毕！\n");	
i2c_stop();	
}

void OLED_On()
{
	
	unsigned char  i,n;	
	for(i=0;i<8;i++)  
		{  
		if(!OPEN_I2C_CMD())
			printf("命令总线启动失败！\n");
		else
		{	
			i2c_WriteByte(0xb0+i);	
			i2c_WriteByte(0x00);	
			i2c_WriteByte(0x10);	 
			i2c_stop();	//命令传输完成，此处需要切换成数据传输模式
		}	
		if(!OPEN_I2C_DATA())
			printf("数据总线启动失败！\n");
		else
		{	
			for(int n=0; n<128;n++)
			{		
				i2c_WriteByte(0xff);	
				if(!i2c_wait_ack())
				{
					printf("oled 传输无应答 错误！\n");
					break;
				}
				
			}
			i2c_stop();//数据传输完成，此处需要切换成命令传输模式
		}	
									
	} 
	
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>128-1){x=0;y=y+2;}
		if(Char_Size ==16)
		{
			OLED_Set_Pos(x,y);
			OPEN_I2C_DATA();	
			for(i=0;i<8;i++)
				OLED_WR_DATA(F8x16[c*16+i]);
				i2c_stop();
				OLED_Set_Pos(x,y+1);
					OPEN_I2C_DATA();	
						for(i=0;i<8;i++)
							OLED_WR_DATA(F8x16[c*16+i+8]);
						i2c_stop();
		}
		else 
		{	
			OLED_Set_Pos(x,y);
			OPEN_I2C_DATA();	
			for(i=0;i<6;i++)
				OLED_WR_DATA(F6x8[c][i]);
			i2c_stop();	
		}
}