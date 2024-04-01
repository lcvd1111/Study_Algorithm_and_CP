vpath %c ./src
vpath %h ./include

INCLUDE_MY_DIRS = ./include

EXE: object_main object_list object_bst object_test
	$(CC) $^ -o EXE

%.o:
	$(COMPILE.c) $< -I $(INCLUDE_MY_DIRS) -o $@

object_%:
	cp $< $@

object_main: main.o

object_list: list.o

object_bst: bst.o

object_test: test.o

include Dependency.mk

Dependency.mk: main.c list.c bst.c test.c
	$(CC) -M $^ -I $(INCLUDE_MY_DIRS) > $@

.PHONY: clean cleanall
clean:
	rm EXE *.o object_* Dependency.mk

cleanall:
	rm EXE *.o object_* Dependency.mk
