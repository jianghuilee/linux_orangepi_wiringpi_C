#include"i2c.h"
#define i2c_addr 0x38 //填写对应address
// ---------function_define--------

void aht10_init();
void startMeasure_AHT10();
void read_AHT10();
void reset_AHT10();

// ---------function_content--------
void aht10_init()
{
	i2c_start();
	i2c_WriteByte(0x70);
	// if(i2c_wait_ack()) printf("√");
	// else printf("×");
	i2c_WriteByte(0xE1);	
	// if(i2c_wait_ack()) printf("√");
	// else printf("×");
	i2c_WriteByte(0x08);
	// if(i2c_wait_ack()) printf("√");
	// else printf("×");
	i2c_WriteByte(0x00);
	// if(i2c_wait_ack()) printf("√");
	// else printf("×");
	printf("init finished!\n");
	i2c_stop();
}

void  startMeasure_AHT10(void)
{
	i2c_start();
	i2c_WriteByte(0x70);
	if(i2c_wait_ack()) printf("√");
	else printf("×");
	i2c_WriteByte(0xAC);
	if(i2c_wait_ack()) printf("√");
	else printf("×");
	i2c_WriteByte(0x33);
	if(i2c_wait_ack()) printf("√");
	else printf("×");
	i2c_WriteByte(0x00);
	if(i2c_wait_ack()) printf("√");
	else printf("×");
	printf("start Measure!\n");
	i2c_stop();
	
}

void read_AHT10()
{
	unsigned int T1,H1;
	unsigned char readByte[6];
	i2c_start();
	i2c_WriteByte(0x71);
	if(i2c_wait_ack()) printf("√");
	else printf("×");
    readByte[0]= i2c_ReadByte();
	// printf("test0:%x ",readByte[0]);
    i2c_ack(true);
	readByte[1]= i2c_ReadByte();
	// printf("test1:%x ",readByte[1]);
    i2c_ack(true);
	readByte[2]= i2c_ReadByte();
	// printf("test2:%x ",readByte[2]);
    i2c_ack(true);
	readByte[3]= i2c_ReadByte();
	// printf("test3:%x ",readByte[3]);
    i2c_ack(true);
	readByte[4]= i2c_ReadByte();
	// printf("test4:%x ",readByte[4]);
	readByte[5]= i2c_ReadByte();
	// printf("test5:%x\n ",readByte[5]);
	// printf("data:%x%x%x%x%x\n ",readByte[1],readByte[2],readByte[3],readByte[4],readByte[5]);
    i2c_ack(true);
    i2c_stop();
	unsigned int AHT10_OutData[4];
	if( (readByte[0] & 0x68) == 0x08 )
     {
         H1 = readByte[1];//最高一个字节
         H1 = (H1<<8) | readByte[2];//最高字节左移8位后拼接第二个字节
         H1 = (H1<<8) | readByte[3];//左移8位后拼接第三个字节
         H1 = H1>>4;//右移4位因为数据是2.5个字节
		
         H1 = (H1*1000)/1024/1024;// /102
 
         T1 = readByte[3];//最高一个字节
         T1 = T1 & 0x0000000F;//保留4位，因为是最高4位
         T1 = (T1<<8) | readByte[4];//左移8位后拼接第二个字节
         T1 = (T1<<8) | readByte[5];//左移8位后拼接第三个字节
         T1 = (T1*2000)/1024/1024 - 500;
		
         AHT10_OutData[0] = (H1>>8) & 0x000000FF;
         AHT10_OutData[1] = H1 & 0x000000FF;
 
         AHT10_OutData[2] = (T1>>8) & 0x000000FF;
         AHT10_OutData[3] = T1 & 0x000000FF;
         printf("成功了");
     }
     else
     {
         AHT10_OutData[0] = 0xFF;
         AHT10_OutData[1] = 0xFF;
 
         AHT10_OutData[2] = 0xFF;
         AHT10_OutData[3] = 0xFF;
         printf("失败了");
 
     }
     printf("\r\n");
     printf("温度:%d%d.%d",T1/100,(T1/10)%10,T1%10);
     printf("湿度:%d%d.%d",H1/100,(H1/10)%10,H1%10);
     printf("\r\n");
	 
}

void  reset_AHT10()
 {
 
     i2c_start();
 
     i2c_WriteByte(0x70);
     // if(i2c_wait_ack()) printf("√");
		// else printf("×");
     i2c_WriteByte(0xBA);
     // if(i2c_wait_ack()) printf("√");
		// else printf("×");
     i2c_stop();
 
     /*
     AHT10_OutData[0] = 0;
     AHT10_OutData[1] = 0;
     AHT10_OutData[2] = 0;
     AHT10_OutData[3] = 0;
     */
 }


int main()
{
	if (wiringPiSetup () == -1)
        {
	     printf ("Unable to start wiringPi:\n") ;
		 return 0;
		}	
		
	delay(10);
 
     reset_AHT10();
     delay(10);
 
     aht10_init();
     delay(10);
 
     startMeasure_AHT10();
     delay(100);

     read_AHT10();
     delay(5);
	// printf("温湿度数据：%d,%d,%d,%d,%d,%d\n",wiringPiI2CRead(fd),wiringPiI2CRead(fd),wiringPiI2CRead(fd),wiringPiI2CRead(fd),wiringPiI2CRead(fd),wiringPiI2CRead(fd));
}
