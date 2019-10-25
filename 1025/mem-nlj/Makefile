T1 = memjoin

CC = g++
CFLAGS = -c -Wall -g -DDEBUG -O0
LDFLAGS = -Wall -L/usr/local/lib -lm -lpthread -O2

OBJ1 = memjoin.o

#
# Rules for make
#
all: $(T1) 

$(T1): $(OBJ1) 
	$(CC) -o $@ $^ $(LDFLAGS)

.cc.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f *~ *.o *.exe *.stackdump
