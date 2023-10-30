CC = gcc
CFLAGS = -Wall

CLIENT_SRC = client.c
SERVER_SRC = server.c
CLIENT_EXE = client
SERVER_EXE = server

all: $(CLIENT_EXE) $(SERVER_EXE)

$(CLIENT_EXE): $(CLIENT_SRC) 
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_EXE): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(CLIENT_EXE) $(SERVER_EXE)