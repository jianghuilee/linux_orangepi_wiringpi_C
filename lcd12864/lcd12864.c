#include<stdio.h>
#include<wiringPi.h>

#define RS   9 
#define RW   10
#define EN   11
void ClearGDRAM();
void LCD12864_word();
void LCD12864_WriteCmd(char cmd);
void LCD12864_Init();
void LCD12864_WriteData(char data);
void LCD12864_Busy();
void LCD12864_SetWindow(char x, char y);
void LCD12864_pic();


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
 pinMode(EN,OUTPUT);
 LCD12864_Init();
//char  word[]=	
//	{
//	0xD6,0xD0, 0xCE,0xC4, 0xB2,0xE2, 0xCA,0xD4,0xD2,0xBA, 0xBE,0xA7, 0xCF,0xD4 ,0xCA,0xBE  
//	
//	};
//
//while(word[i]!='\0')	
//     {	if(i<16)
//	     {
//     		LCD12864_WriteData(word[i]);
//    		i++;
//	     }
//
//     }

//LCD12864_word();
LCD12864_pic();

}





void LCD12864_Init()
{

LCD12864_WriteCmd(0x30);
LCD12864_WriteCmd(0x30);  //ѡ??????ָ??????
LCD12864_WriteCmd(0x30);  //ѡ??????ָ??????
LCD12864_WriteCmd(0x08);  //ѡ??????ָ??????
LCD12864_WriteCmd(0x10);  //ѡ??????ָ??????
  LCD12864_WriteCmd(0x0c);  //??ʾ?????ع???
  LCD12864_WriteCmd(0x01);  //ѡ??????ָ??????
  LCD12864_WriteCmd(0x06);  //??ʾ?????ع???
 

}

void LCD12864_WriteCmd(char cmd)
{
 LCD12864_Busy(); 
digitalWrite(	RS ,0);
digitalWrite(	RW ,0); 
digitalWrite(	EN ,0);
 digitalWriteByte((int)cmd); 
    //????????
digitalWrite(	EN ,1);       //дʱ??
digitalWrite(	EN ,0);            
}


void LCD12864_WriteData(char data)
{
 LCD12864_Busy();
  digitalWrite(	RS ,1);    //ѡ??????
  digitalWrite(	RW ,0);     //ѡ??д??
  digitalWrite(	EN ,0);    //??ʼ??ʹ?ܶ?
 digitalWriteByte((int)data);   //????????
  digitalWrite(	EN ,1);     //дʱ??
   digitalWrite(	EN ,0);   
                    
}


void LCD12864_Busy()
{
  digitalWrite(	RS ,0);    //ѡ??????
  digitalWrite(	RW ,1);     //ѡ??д??
  digitalWrite(	EN ,1);    //??ʼ??ʹ?ܶ?
  pinMode(13,INPUT);
  while(digitalRead(13))
  {
  }
  pinMode(13,OUTPUT);
  digitalWrite(	EN ,0); 
}

void LCD12864_SetWindow(char x, char y)
{
  char pos;
  if(x == 1)     // ???????80H
    x = 0x80;   
  else if(x == 2)  //???????90H
    x = 0x90;  
  else if(x == 3)  //???????88H
    x = 0x88; 
  else if(x == 4)  //???????98H
    x = 0x98;

  pos = x + (y-1);
 
  LCD12864_WriteCmd(pos);  
   
}

void LCD12864_word()
{
int i;
char word_1[32]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x40,0x08,0x10,0x00,0x00,0x10,0x08,0x00,0x00,0x10,0x08,0x00,0x00,0x08,0x10,0x02,0x40,0x00,0x00,0x00,0x00,0x00,0x00

};
char word_2[32]=
{
0x00,0x00,0x00,0x00,0x03,0x80,0x02,0x40,0x02,0x20,0x02,0x10,0x02,0x10,0x02,0x10,0x02,0x10,0x02,0x10,0x02,0x10,0x02,0x20,0x02,0x40,0x03,0x80,0x00,0x00,0x00,0x00
};
char word_3[32]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x80,0x00,0x00,0x54,0x54,0x20,0x08,0x08,0x20,0x02,0x80,0x12,0x90,0x08,0x20,0x20,0x08,0x00,0x00,0x00,0x00
};
char word_4[32]=
{
0x07,0xE0,0x08,0x10,0x12,0x48,0x10,0x08,0x1F,0xF8,0x10,0x08,0x30,0x0C,0x50,0x0A,0x50,0x0A,0x50,0x0A,0x50,0x0A,0x5F,0xFA,0x04,0x20,0x04,0x20,0x04,0x20,0x0E,0x70


};
LCD12864_WriteCmd(0x30);
LCD12864_WriteCmd(0x40);
for(i=0;i<32;i++)
{
	 LCD12864_WriteData(word_1[i]);
	}	
LCD12864_SetWindow(1,1);
LCD12864_WriteData(0x00);
LCD12864_WriteData(0x00);//映射内部0x40内部数据的地址


LCD12864_WriteCmd(0x50);
for(i=0;i<32;i++)

	{                                   
	 LCD12864_WriteData(word_2[i]);
	}

LCD12864_SetWindow(2,1);
LCD12864_WriteData(0x00);
LCD12864_WriteData(0x02);//映射内部0x50数据的地址


LCD12864_WriteCmd(0x60);
for(i=0;i<32;i++)
        {
         LCD12864_WriteData(word_3[i]);
	}

LCD12864_SetWindow(3,1);
LCD12864_WriteData(0x00);//映射0x60内部数据的地址
LCD12864_WriteData(0x04);//

LCD12864_WriteCmd(0x70);
for(i=0;i<32;i++)
        {
         LCD12864_WriteData(word_4[i]);
	}

LCD12864_SetWindow(4,1);
LCD12864_WriteData(0x00);//映射0x70内部数据的地址
LCD12864_WriteData(0x06);

}



  void ClearGDRAM()//清空GDAM内存地址上内容的函数
{
   char i,j,k;
   char LCD12864_X=0x80;//设置水平坐标（列地址或水平地址X）从LCD12864点阵型液晶显示器第1行第一个位置开始，GDRAM（Graphic Display RAM：图形显示随机存储器）的地址计数器（即AC）只会对水平坐标（列地址或水平地址X）自动加1，垂直坐标（行地址或垂直地址Y）要用数据循环写入。  
   char LCD12864_Y=0x80;//设置垂直坐标（行地址或垂直地址Y）从LCD12864点阵型液晶显示器第1行第一个位置开始  
   LCD12864_WriteCmd(0x34);//设置LCD12864点阵型液晶显示器数据端口D0-D7为8位控制接口，且这8位控制接口接收扩展指令操作。
   LCD12864_WriteCmd(0x34);//设置关LCD12864点阵型液晶显示器绘图功能，与上面的0x34不冲突，在此表示关LCD12864点阵型液晶显示器绘图功能。
   for(i=0;i<2;i++)//LCD12864点阵型液晶显示器分为上下两屏
 {
    for(j=0;j<32;j++)//32表示LCD12864点阵型液晶显示器上半屏或下半屏32行
  {
     LCD12864_WriteCmd(LCD12864_Y+j);//设置垂直坐标（行地址或垂直地址Y）从LCD12864点阵型液晶显示器第1行第一个位置开始  
     LCD12864_WriteCmd(LCD12864_X);//设置水平坐标（列地址或水平地址X）从LCD12864点阵型液晶显示器第1行第一个位置开始，GDRAM（Graphic Display RAM：图形显示随机存储器）的地址计数器（即AC）只会对水平坐标（列地址或水平地址X）自动加1，垂直坐标（行地址或垂直地址Y）要用数据循环写入。
     for(k=0;k<16;k++)//一个完整图案占用LCD12864点阵型液晶显示器32（行）x128（列）显示界面，上半屏每一行占用16个字节（即128列）才显示该行某些图案，要写完该行某些图案占用的16个字节，必须分16次来写，这就是循环16次的原由。
   {
      LCD12864_WriteData(0x00);//清空GDAM内存地址上的内容
     }
   }
    LCD12864_X=0x88;//设置水平坐标（列地址或水平地址X）从LCD12864点阵型液晶显示器下半屏第1行第一个位置开始
  }
   LCD12864_WriteCmd(0x36);//设置开LCD12864点阵型液晶显示器绘图功能
   LCD12864_WriteCmd(0x30);//设置LCD12864点阵型液晶显示器数据端口D0-D7为8位控制接口，且这8位控制接口接收基本指令操作。 
  }

void LCD12864_pic()
{
ClearGDRAM();
char  image[]=
 {
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFE,0x00,0x00,0x00,
     0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFC,0x00,0x00,0x00,
     0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xF8,0x00,0x00,0x00,
     0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xE0,0x00,0x00,0x00,
     0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0x80,0x00,0x00,0x00,
     0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,
     0x00,0x00,0x01,0xF8,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xF8,0x00,0x00,0x00,0x00,
     0x00,0x00,0x03,0xF8,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xE0,0x00,0x00,0x00,0x00,
     0x00,0x00,0x07,0xF8,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,
     0x00,0x00,0x0F,0xF8,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x1F,0xF8,0x00,0x00,0x00,0x00,0x7F,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x03,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFC,0x00,0x00,0x00,0x1F,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFE,0x00,0x00,0x00,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0x00,0x00,0x07,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0x80,0x00,0x3F,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xC0,0x01,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xE0,0x0F,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xF0,0x7F,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x1F,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x0F,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x07,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x03,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x01,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x3F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    };
char i,j,k;
int p=0;
char   LCD12864_X=0x80;//设置水平坐标（列地址或水平地址X）从LCD12864点阵型液晶显示器第1行第一个位置开始，GDRAM（Graphic Display RAM：图形显示随机存储器）的地址计数器（即AC）只会对水平坐标（列地址或水平地址X）自动加1，垂直坐标（行地址或垂直地址Y）要用数据循环写入。  
char    LCD12864_Y=0x80;//设置垂直坐标（行地址或垂直地址Y）从LCD12864点阵型液晶显示器第1行第一个位置开始  
   LCD12864_WriteCmd(0x34);//设置LCD12864点阵型液晶显示器数据端口D0-D7为8位控制接口，且这8位控制接口接收扩展指令操作。
   LCD12864_WriteCmd(0x34);//设置关LCD12864点阵型液晶显示器绘图功能，与上面的0x34不冲突，在此表示关LCD12864点阵型液晶显示器绘图功能。
   for(i=0;i<2;i++)//LCD12864点阵型液晶显示器分为上下两屏
 {
    for(j=0;j<32;j++)//32表示LCD12864点阵型液晶显示器上半屏或下半屏32行
  {
     LCD12864_WriteCmd(LCD12864_Y+j);//设置垂直坐标（行地址或垂直地址Y）从LCD12864点阵型液晶显示器第1行第一个位置开始 
     LCD12864_WriteCmd(LCD12864_X);//设置水平坐标（列地址或水平地址X）从LCD12864点阵型液晶显示器第1行第一个位置开始，GDRAM（Graphic Display RAM：图形显示随机存储器）的地址计数器（即AC）只会对水平坐标（列地址或水平地址X）自动加1，垂直坐标（行地址或垂直地址Y）要用数据循环写入。
     for(k=0;k<16;k++)//一个完整图案占用LCD12864点阵型液晶显示器32（行）x128（列）显示界面，上半屏每一行占用16个字节（即128列）才显示该行某些图案，要写完该行某些图案占用的16个字节，必须分16次来写，这就是循环16次的原由。
   {
      LCD12864_WriteData(image[p++]);//*p对应数组image[]中的某位数值,而p++对应image[]中的序列。
 	delay(2);  
   }

   }
    LCD12864_X=0x88;//设置水平坐标（列地址或水平地址X）从LCD12864点阵型液晶显示器下半屏第1行第一个位置开始
  }
   LCD12864_WriteCmd(0x36);//设置开LCD12864点阵型液晶显示器绘图功能
   LCD12864_WriteCmd(0x30);//设置开LCD12864点阵型液晶显示器绘图功能
 }







