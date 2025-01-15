DIFF ?= diff
MPIEXEC ?= mpiexec
CXX = mpicxx

CXXFLAGS += -Wall -std=c++11
MPIFLAGS += -np 2

EXE = fmRn
OBJS = main.o FunctionMinRn.o FunctionRn.o Monomial.o Point.o MPI_helpers.o

Point.o: Point.hh
Monomial.o: Point.hh Monomial.hh
FunctionMinRn.o: FunctionMinRn.hh Point.hh FunctionRn.hh Monomial.hh MPI_helpers.hh
FunctionRn.o: FunctionRn.hh Monomial.hh Point.hh
main.o: FunctionMinRn.hh Point.hh FunctionRn.hh Monomial.hh Point.hh
main.o MPI_helpers.o: MPI_helpers.hh

.DEFAULT_GOAL = all
all: build

.PHONY: all build clean distclean run

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

run: $(EXE)
	$(MPIEXEC) $(MPIFLAGS) ./$(EXE)

clean:
	$(RM) $(OBJS)
	$(RM) $(EXE)

distclean: clean
	$(RM) *~
