
CC    = g++
CFLAGS= -std=c++11 -I. -I/usr/include
LIBS  = -L/usr/lib

OBJ   = main.o NNeighbor.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

nneighbor: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core
