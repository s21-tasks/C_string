CC=gcc
SRC=s21_string.c s21_sscanf.c s21_sprintf.c s21_strto_.c
OBJ=s21_string.o s21_sscanf.o s21_sprintf.o s21_strto_.o
SRC2=s21_string.c s21_sscanf.c s21_sprintf.c s21_strto_.c
OBJ2=s21_string.o s21_sscanf.o s21_sprintf.o s21_strto_.o
CFLAGS=-Wall -Werror -Wextra
TESTFLAGS=-lcheck -lm -lpthread -lgcov

all: test gcov_report s21_string.a

gcov_report: test
	gcovr -r. --html --html-details -o tests/coverage_report.html

test: lib.a s21_string_test.o $(OBJ)
	$(CC) $(FLAGS) lib.a s21_string_test.o $(OBJ) $(TESTFLAGS) -o test
	./test

lib.a: $(OBJ)
	ar rcs lib.a $(OBJ)

s21_string.a: s21_string_funcs_verter.o
	ar rcs s21_string.a $(OBJ2)

s21_string_test.o: s21_string_test.c
	$(CC) $(CFLAGS) --coverage -c $^

s21_string.o: $(SRC) 
	$(CC) $(CFLAGS) --coverage -c $^

s21_string_funcs_verter.o: $(SRC2)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o 
	rm -rf *.gc*
	rm -rf *.a
	rm -f s21_test