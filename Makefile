CC = gcc 
CFLAGS = -std=c99 -Wall -g
HEADERS = DB.h dashboard.h db_helper.h
OBJECTS = DB.o dashboard.o db_helper.o
TARGET = dashboard
TESTS = test_db_helper test_freeDB


all: $(TARGET)

dashboard: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

DB.o: DB.c DB.h db_helper.h
	$(CC) $(CFLAGS) $< -c

db_helper.o: db_helper.c db_helper.h DB.h
	$(CC) $(CFLAGS) $< -c

dashboard.o: dashboard.c dashboard.h db_helper.h
	$(CC) $(CFLAGS) $< -c



# tests

test_db_helper: test_db_helper.o db_helper.o DB.o
	$(CC) $(CFLAGS) $^ -o $@

test_db_helper.o: testing/test_db_helper.c db_helper.h DB.h
	$(CC) $(CFLAGS) $< -c

test_freeDB: test_freeDB.o DB.o db_helper.o
	$(CC) $(CFLAGS) $^ -o $@

test_freeDB.o: testing/test_freeDB.c DB.h db_helper.h
	$(CC) $(CFLAGS) $< -c

.PHONY: all clean tests run_test_db_helper


tests: run_test_db_helper run_test_free_db

run_test_db_helper: test_db_helper
	./test_db_helper

run_test_free_db: test_freeDB
	gcc -std=c99 -Wall -g -fsanitize=address testing/test_freeDB.c db_helper.c DB.c -o test_freeDB
	./test_freeDB


clean:
	rm -rf $(TARGET) $(TESTS) *.o