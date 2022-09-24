obj=i2c.o
c_file=i2c.c 
targetfilename=i2c
g_flag=-lwiringPi -lm -lpthread -lcrypt -lrt
$(targetfilename):$(obj)
	gcc $(obj) -o $(targetfilename) $(g_flag)
$(obj):$(c_file)
	gcc -c $(c_file)	

