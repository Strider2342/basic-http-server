CC = gcc
CFLAGS = -Wall -Wextra -g -I./src -O0

BINARY = bin/server
SOURCES = $(wildcard src/**/*.c) src/basic-http-server.c
OBJECTS = $(SOURCES:.c=.o)
# OBJECTS = obj/os.o obj/util.o obj/http/server-config.o obj/http/http-server.o obj/http/http-request.o obj/http/http-response.o

# server: basic-http-server.o
# 	$(CC) obj/basic-http-server.o -o bin/server

# basic-http-server.o: os.o util.o http.o
# 	$(CC) obj/os.o obj/util.o obj/http.o src/basic-http-server.c -o /obj/basic-http-server.o

# http.o: os.o util.o
# 	$(CC) -I src/os -I src/util obj/os.o obj/util.o $(wildcard src/http/*.c) -o obj/http.o

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

http/%.o: http/%.c
	echo $@
	$(CC) $(CFLAGS) -c $^ -o ../obj/$@

util/%.o: util/%.c
	$(CC) $(CFLAGS) -c $^ -o ../obj/$@

os/%.o: os/%.c
	$(CC) $(CFLAGS) -c $^ -o ../obj/$@

clean:
	rm -rf $(BINARY) $(OBJECTS)
