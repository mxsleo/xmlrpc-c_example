CC = clang
CFLAGS = -Wall -Ofast
LDFLAGS =

XMLRPC_C_CONFIG = xmlrpc-c-config

SOURCE_SERVER_ABYSS	= unix_server.c
EXECUTABLE_SERVER_ABYSS	= unix_server
OBJECTS_SERVER_ABYSS	= $(SOURCE_SERVER_ABYSS:.c=.o)
LIBS_SERVER_ABYSS	= $(shell $(XMLRPC_C_CONFIG) abyss-server --libs)
INCLUDES_SERVER_ABYSS	= $(shell $(XMLRPC_C_CONFIG) abyss-server --cflags)

SOURCE_CLIENT		= unix_client.c
EXECUTABLE_CLIENT	= unix_client
OBJECTS_CLIENT		= $(SOURCE_CLIENT:.c=.o)
LIBS_CLIENT		= $(shell $(XMLRPC_C_CONFIG) client --libs)
INCLUDES_CLIENT		= $(shell $(XMLRPC_C_CONFIG) client --cflags)


.PHONY: all server client clean

.SUFFIXES: .c .o


default: all

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES_SERVER_ABYSS) -c $< -o $@

$(EXECUTABLE_SERVER_ABYSS): $(OBJECTS_SERVER_ABYSS)
	$(CC) $(LDFLAGS) $(LIBS_SERVER_ABYSS) $(OBJECTS_SERVER_ABYSS) -o $@

server: $(EXECUTABLE_SERVER_ABYSS)

$(EXECUTABLE_CLIENT): $(OBJECTS_CLIENT)
	$(CC) $(LDFLAGS) $(LIBS_CLIENT) $(OBJECTS_CLIENT) -o $@

client: $(EXECUTABLE_CLIENT)

all: server client

clean:
	rm -f $(OBJECTS_SERVER_ABYSS) $(OBJECTS_CLIENT)
	rm -f $(EXECUTABLE_SERVER_ABYSS) $(EXECUTABLE_CLIENT)
