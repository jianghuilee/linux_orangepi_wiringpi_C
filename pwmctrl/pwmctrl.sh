#!/bin/bash 
echo "||^^^^^^^^^^^^^^^||"
echo "||输入参数控制pwm||"
echo "||_参数1：pwm周期||"
echo "||_参数2：低电平_||"
echo "||_______________||"
    FILE=/sys/class/pwm/pwmchip1/pwm0
if [ -d "$FILE" ];
then
    echo "pwm is enable!"
    	
else 
	echo 0 > /sys/class/pwm/pwmchip1/export	
fi
echo $1 > /sys/class/pwm/pwmchip1/pwm0/period
echo $2 > /sys/class/pwm/pwmchip1/pwm0/duty_cycle
        echo 1 > /sys/class/pwm/pwmchip1/pwm0/enable

