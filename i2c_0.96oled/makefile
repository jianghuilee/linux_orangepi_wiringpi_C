obj= main.o i2c.o i2c_096oled.o
c_file=main.c i2c.c  i2c_096oled.c
targetfilename=i2c_096oled
g_flag=-lwiringPi -lm -lpthread -lcrypt -lrt
$(targetfilename):$(obj)
	gcc $(obj) -o $(targetfilename) $(g_flag)
$(obj):$(c_file)
	gcc -c $(c_file)	
