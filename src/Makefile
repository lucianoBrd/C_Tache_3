CC ?= gcc

COBJS ?= client.o bmp.o couleur.o json.o validateur.o
SOBJS ?= serveur.o json.o validateur.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
	$(CC) -o $(SERVER) $(SOBJS)

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS)

.c.o:
	$(CC) -c $*.c
	
clean :
	-rm -f *.o $(SERVER) $(CLIENT)
