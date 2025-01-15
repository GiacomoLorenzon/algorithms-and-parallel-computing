ifeq "$(origin CXX)" "default"
  CXX = mpicxx
endif

CXXFLAGS += -Wall -std=c++11
MPIEXEC ?= mpiexec
MPIFLAGS ?= -np 4

LINK = $(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

BASE = norm

main.o get.o : get.hh
calculate.o mpi_assembling.o : mpi_assembling.hh
main.o calculate.o : calculate.hh
operation.o calculate.o : operation.hh

$(BASE) : main.o calculate.o mpi_assembling.o operation.o get.o
	$(LINK)


.DEFAULT_GOAL = all

all : build

.PHONY : all build clean distclean run

build : $(BASE)

clean :
	$(RM) *.o
	$(RM) $(BASE) $(UNEVEN)

distclean : clean
	$(RM) *~
