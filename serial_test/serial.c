#include <stdio.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int fd ;
  int count ;
  unsigned int nextTime ;

  if ((fd = serialOpen ("/dev/ttyS4",9600 )) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)
  {
 fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
 
 int i ;
//while(1)
// {
//	 i++;
//serialPrintf(fd,"the data is :%d\n",i) ;
//	delay(100);
//}  
delay(3);
while(1)
{	
while (serialDataAvail (fd))
    {
      printf ( "%c", serialGetchar (fd)) ;
     fflush(stdout);	

    }


} 
return 0 ;
}

