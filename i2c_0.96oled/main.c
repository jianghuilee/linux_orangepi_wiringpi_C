#include"i2c_096oled.h"
#include"i2c.h"
#include<wiringPi.h>
#include<stdio.h>
#include<stdbool.h>
//---------main--------
int main()
{
	if (wiringPiSetup()== -1)
    {
	 printf ("Unable to start wiringPi\n") ;
	 return 0;
	}	
	else 
	{
		init();
		i2c_serch();
		OLED_Init();
		OLED_Clear(); 
		delay(100);
		OLED_ShowChar(12,40,'A',12);//显示ASCII字符
	}
		
	
	
}