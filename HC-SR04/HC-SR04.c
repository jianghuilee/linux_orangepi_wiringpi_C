#include<wiringPi.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<wiringSerial.h>
#define triger 5
#define echo 7


void scan();

 int fd ;
float begin_time,end_time,continus_time;

int main()
{
wiringPiSetup () ;
 int count ;
  unsigned int nextTime ;

   if ((fd = serialOpen ("/dev/ttyS4",460800 )) < 0)
	    {
		       fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		          return 1 ;
			   }

    if (wiringPiSetup () == -1)
	     {
		     fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		        return 1 ;
			 }



pinMode(triger,OUTPUT); 
delay(1);
pinMode(echo,INPUT); 
delay(1);

scan();

 return 0;
}

void scan()
{
	digitalWrite(triger,0);
	delayMicroseconds (9);
	digitalWrite(triger,1);
	delayMicroseconds (10);
	digitalWrite(triger,0);

  	continus_time=micros();
	while(digitalRead(echo)==0)
	{
	printf("time_now:%d\n",micros());
	delayMicroseconds(1);
	if((micros()-continus_time)>38000)
		{
		printf("time_out\n");	
		break;
		}

    if(serialGetchar(fd))
    {
    printf("%c:\n",serialGetchar(fd));
    } 
     
   
	}
	begin_time=micros();
      printf("begin time：%.3f\n",begin_time);
      printf("end time：%.3f\n",end_time);
	printf("the distence is:%.3f(cm)\n",0.017*(end_time-begin_time));	       
	       
	       
}	       
	       
	       
	       
	       
	       
	       
	       
	       
	       
	       
	       
	       
