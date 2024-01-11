vpath %c ./src
vpath %h ./include

INCLUDE_MY_DIRS = ./include

EXE: object_main object_sub00 object_sub01 object_sub02 object_sub03
	$(CC) $^ -o $@

object_%:
	cp $< $@

%.o:
	$(COMPILE.c) $< -I $(INCLUDE_MY_DIRS) > $@

object_main: main.o

object_sub00: node.o

object_sub01: list.o

object_sub02: heap.o

object_sub03: test.o

include Dependency.mk

Dependency.mk: main.c node.c list.c heap.c test.c
	$(CC) -M $^ -I $(INCLUDE_MY_DIRS) > $@

.PHONY: clean cleanall
clean:
	rm EXE *.o object_* Dependency.mk

cleanall:
	rm EXE *.o object_* Dependency.mk
