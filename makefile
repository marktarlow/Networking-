all : bankingClient.o bankingServer.o

bankingClient.o : interface.h bankingClient.c
	gcc -pthread -o bankingClient bankingClient.c
bankingServer.o : interface.h bankingServer.c
	gcc -pthread -o bankingServer bankingServer.c
	
.PHONY : clean
clean :
	-rm bankingClient bankingServer
