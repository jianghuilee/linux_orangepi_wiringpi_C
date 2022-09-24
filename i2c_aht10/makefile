obj=i2c.o main.o 
c_file=i2c.c main.c
targetfilename=aht10
g_flag=-lwiringPi -lm -lpthread -lcrypt -lrt
$(targetfilename):$(obj)
	gcc $(obj) -o $(targetfilename) $(g_flag)
$(obj):$(c_file)
	gcc -c $(c_file)	

