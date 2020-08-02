# this will compile countprimes.c file and create an executible called countprimes. 
#It also has the option to clean the executable and object files.

countprimes:	countprimes.c
		/usr/lib64/openmpi/bin/mpicc -O -o countprimes countprimes.c

clean:
	rm -f *.exe *.o *~ countprimes