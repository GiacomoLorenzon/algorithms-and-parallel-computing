CXXFLAGS += -Wall -std=c++11 \
   -Werror \
   -Wextra \
   -Wconversion \
   -Wno-deprecated \
   -Winit-self \
   -Wsign-conversion \
   -Wredundant-decls \
   -Wvla -Wshadow -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual \
   -Winit-self \
   -Wpointer-arith \
   -Wcast-qual \
   -Wcast-align \
   -Wdouble-promotion \
   -Wold-style-cast -Wno-error=old-style-cast \
   -Wsign-promo \
   -Wswitch-enum \
   -Wswitch-default \
   -Wundef
OBJS = erdos_calculator.o

.PHONY: all build run clean distclean

.DEFAULT_GOAL: all

all: build

build: $(OBJS)

erdos_calculator.o: erdos_calculator.hh author.hh

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~
