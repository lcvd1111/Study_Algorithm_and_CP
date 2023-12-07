vpath %cc ./src
vpath %hh ./src

INCLUDE_MY_DIRS = ./include

EXE: object_main object_sub01 object_sub02
	$(CXX) $^ -I $(INCLUDE_MY_DIRS) -o $@

%.o:
	$(COMPILE.cc) $< -I $(INCLUDE_MY_DIRS) -o $@

object_%:
	cp $< $@

object_main: main.o

object_sub01: search.o

object_sub02: test.o

include Dependency.mk

Dependency.mk: main.cc search.cc test.cc
	$(CC) -M $^ -I $(INCLUDE_MY_DIRS) > $@

.PHONY: clean cleanall
clean:
	rm EXE *.o object_* Dependency.mk

cleanall:
	rm EXE *.o object_* Dependency.mk
