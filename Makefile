all: serverA serverB serverC serverD client

client: client.o 
	gcc -o client -g client.o  
	
serverA: serverA.o
	gcc -o serverA -g serverA.o  
	
serverA.o: serverA.c server450.h util.h
	gcc -g -c serverA.c  
	
serverB: serverB.o 
	gcc -o serverB -g serverB.o 
	
serverB.o: serverB.c server450.h util.h
	gcc -g -c serverB.c 
	
serverC: serverC.o
	gcc -o serverC -g serverC.o 
	
serverC.o: serverC.c server450.h util.h
	gcc -g -c serverC.c 

serverD: serverD.o
	gcc -o serverD -g serverD.o 
	
serverD.o: serverD.c server450.h util.h
	gcc -g -c serverD.c  
	
client.o: client.c 
	gcc -g -c client.c 
	
clean:
	rm -f *.o serverA serverB serverC serverD client
