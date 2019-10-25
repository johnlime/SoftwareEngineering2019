T1 = bnlj
T2 = hash-bnlj

CC = g++
CFLAGS = -c -Wall -g -DDEBUG -O2
LDFLAGS = -Wall -L/usr/local/lib -lm -lpthread -O2

OBJ1 = bnlj.o
OBJ2 = hash-bnlj.o

#
# Rules for make
#
all: $(T1) $(T2) 

$(T1): $(OBJ1) 
	$(CC) -o $@ $^ $(LDFLAGS)

$(T2): $(OBJ2) 
	$(CC) -o $@ $^ $(LDFLAGS)

.cc.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f *~ *.o *.exe *.stackdump
