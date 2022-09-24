#include<stdio.h>
#include<wiringPi.h>
#include<math.h>
#define RS   9 
#define RW   10
#define LCDE   11


void lcd_Init();		//??ʼ??
void lcd_write_com(char com);		//дָ??
void lcd_write_dat(char  dat);		//д????
void lcd_xy(char x,char y);  //дλ??
void lcd_read_busy();		//??????־λ
void lcd_word_define(char num);
void nextpage();


int i,a =0,j,n;
char * Data_1=
"jianghui_lee----lcd1602_test----" ; // ??һ????ʾ????ʮ?????ַ?
char * Data_2="lcd_test2-------------------------------";

int main()
{
 
 wiringPiSetup();
 pinMode(0,OUTPUT);
 pinMode(1,OUTPUT);
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
 pinMode(7,OUTPUT);
 pinMode(RS  ,OUTPUT);
 pinMode(RW  ,OUTPUT);
 pinMode(LCDE,OUTPUT);
 lcd_Init();
  while(*Data_1!='\0')
  {     if(i<32)	
    	lcd_write_dat(*Data_1++);
	else
	{
	nextpage();
        i=0;  
	}
i++; 
  }
}

void nextpage()
{

char * page_changeline1="next page!";
char * page_changeline2="----waiting----";

lcd_xy(1,1);  
while(*page_changeline1!='\0')
 {
  lcd_write_dat(*page_changeline1++);
  }
lcd_xy(2,1);  
while(*page_changeline2!='\0')
 {
  lcd_write_dat(*page_changeline2++);
  }


		lcd_word_define(2); 
		lcd_write_com(0x40);
		lcd_xy(1,1);  // 在第一行第一列显示 第一个字符
		lcd_write_dat(0x00);

		lcd_write_com(0x48);
		lcd_xy(2,1);  // 在第一行第一列显示 第一个字符
		lcd_write_dat(0x01);
		
		lcd_write_com(0x40);
		lcd_xy(1,16);  // 在第一行第一列显示 第一个字符
		lcd_write_dat(0x00);

		lcd_write_com(0x48);
		lcd_xy(2,16);  // 在第一行第一列显示 第一个字符
		lcd_write_dat(0x01);
delay(1000);
lcd_write_com(0x01);
}


//?????ƶ???ʾ**************************************************************
//void dh(){
//	lcd_Init();
//
//	lcd_write_com(0x80);  // ??һ?е?һ?е?ַ
//	for(i=0; i<16; i++){     
//		lcd_write_dat(Data_1[i]);  // ??ʾ??һ??
//	}
//	while(1){
//		lcd_read_busy();
//		lcd_write_com(0xc0);  // ?ڶ??е?һ?е?ַ
//		for(j=n; j<28+n; j++){     
//			lcd_write_dat(Data_2[j]);  // ??ʾ?ڶ???
//		}
//		n++;
//
//		if(n >= (28-15)){  // ???????ƶ???????ʱ??n ???? 0??ͣ?? 500 ms?????¿?ʼ?ƶ???ʾ
//			n = 0;
//			delay1ms(50);
//		}
//		delay1ms(20);  // ?????ƶ??ٶ?
//	}
//}

void lcd_Init()
{
	lcd_write_com(0x3c);
	lcd_write_com(0x3c);	//??????ʾģʽ
	lcd_write_com(0x3c);	//??????ʾģʽ
	lcd_write_com(0x06);	//ָ???Զ???һ
	lcd_write_com(0x01);	//????
	lcd_write_com(0x0c);	//????ʾ????ʾ????
}


void lcd_write_dat(char dat)
{//д??????
  lcd_read_busy();
  digitalWrite(	RS ,1);
  digitalWrite(	RW  ,0); 
  delayMicroseconds(1);
  digitalWriteByte((int)dat);
  digitalWrite(	LCDE ,1);//??һ????????
	delay(1);
  digitalWrite(	LCDE ,0);//??һ????????
}

    


void lcd_write_com(char com)
{//д??????
lcd_read_busy();
digitalWrite(	RS ,0);
digitalWrite(	RW  ,0); 
digitalWriteByte((int)com);
	delay(1);
digitalWrite(	LCDE ,1);//??һ????????
	delay(1);
digitalWrite(	LCDE ,0);//??һ????????
}




void lcd_xy(char x,char y)
{	if(x==1)
		lcd_write_com((int)(0x80+(y-1)));
	else
		lcd_write_com((int)(0x80+0x40+(y-1)));
}

void lcd_read_busy()
{
digitalWrite(	RS ,0);
digitalWrite(	RW  ,1); 
digitalWrite(	LCDE ,1);
pinMode(13,INPUT);
while(digitalRead(13))
{
delayMicroseconds(1);
}
pinMode(13,OUTPUT);
delayMicroseconds(1);
}

void lcd_word_define(char num)
{
char word[8][8]=
{       
	{0x1f,0x1b,0x1b,0x1b,0x0e,0x0e,0x0e,0x0e},
	{0x0e,0x0e,0x0e,0x1f,0x1b,0x1b,0x1b,0x1f},
	{},
	{},
	{},
	{},
	{},
	{}

};
char i,j;
for(i=0;i<num;i++)
	{
		lcd_write_com(0x40+i*8);
			for(j=0;j<8;j++)
			{
				lcd_write_dat(word[i][j]);  // 写入自定义字符字模
	
			}	
	}
	


}



