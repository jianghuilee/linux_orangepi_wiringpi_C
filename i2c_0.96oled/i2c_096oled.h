#include "i2c.h"

//总线启用
_Bool OPEN_I2C_CMD();
_Bool OPEN_I2C_DATA();
//初始化oled屏幕
void OLED_Init(void);
//向设备写控制命令
void OLED_WR_CMD(unsigned char cmd);
//向设备写1个数据
void OLED_WR_DATA(unsigned char data);

//清屏
void OLED_Clear(void);
//清行
void OLED_Clearrow(unsigned char i);
//开启OLED显示    
void OLED_Display_On(void);
//关闭OLED显示     
void OLED_Display_Off(void);
//设置光标
void OLED_Set_Pos(unsigned char x, unsigned char y);

void OLED_On(void);
	
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size);

 //显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2);

//显示一个字符号串
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char Char_Size);

//显示汉字
//hzk 用取模软件得出的数组
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no);

