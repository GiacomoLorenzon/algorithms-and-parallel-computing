ifeq "$(origin CXX)" "default"
  CXX = mpicxx
endif
CXXFLAGS += -Wall -std=c++11

EXE = gradient
OBJS = main.o nd_vector.o gradient.o mpi_helpers.o

main.o: nd_vector.hh gradient.hh mpi_helpers.hh
nd_vector.o: nd_vector.hh
gradient.o: gradient.hh nd_vector.hh mpi_helpers.hh
mpi_helpers.o: mpi_helpers.hh

.DEFAULT_GOAL = all

all: build

.PHONY: all build clean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

clean:
	$(RM) *.o
	$(RM) $(EXE)

distclean: clean
	$(RM) *~
