proWiringop=-lwiringPi -lm -lpthread -lcrypt -lrt
cfile=serial.c
objfile=serial.o
targetfile=serial
	
$(targetfile):$(objfile)
	gcc $(objfile) -o $(targetfilename) $(proWiringop)

$(objfile):$(cfile)
	gcc -c $(cfile)