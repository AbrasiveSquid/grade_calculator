CC = gcc 
CFLAGS = -std=c99 -Wall -g
HEADERS = DB.h dashboard.h db_helper.h
OBJECTS = DB.o dashboard.o db_helper.o
TARGET = dashboard


all: $(TARGET)

dashboard: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

DB.o: DB.c DB.h db_helper.h
	$(CC) $(CFLAGS) $< -c

db_helper.o: db_helper.c db_helper.h DB.h
	$(CC) $(CFLAGS) $< -c

dashboard.o: dashboard.c dashboard.h db_helper.h
	$(CC) $(CFLAGS) $< -c



.PHONY:

clean:
	rm -r $(TARGETS) *.o