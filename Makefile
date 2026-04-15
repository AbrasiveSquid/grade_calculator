CC = gcc 
CFLAGS = -std=c99 -Wall -g
HEADERS = DB.h dashboard.h
OBJECTS = DB.o dashboard.o
TARGET = dashboard


all: $(TARGET)

dashboard: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

DB.o: DB.c DB.h
	$(CC) $(CFLAGS) $< -c

dashboard.o: dashboard.c dashboard.h
	$(CC) $(CFLAGS) $< -c



.PHONY:

clean:
	rm -r $(TARGETS) *.o