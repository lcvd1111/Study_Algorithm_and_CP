vpath %c ./src
vpath %c ./include

INCLUDE_MY_DIRS = ./include

EXE: object_main object_array object_bst object_test
	$(CC) $^ -o $@

%.o:
	$(COMPILE.c) $< -I $(INCLUDE_MY_DIRS) -o $@

object_%:
	cp $< $@

object_main: main.o

object_array: array.o

object_bst: bst.o

object_test: test.o

include Dependency.mk

Dependency.mk: main.c array.c bst.c test.c
	$(CC) -M $^ -I $(INCLUDE_MY_DIRS) > $@

.PHONY: clean cleanall
clean:
	rm EXE *.o object_* Dependency.mk

cleanall:
	rm EXE *.o object_* Dependency.mk
