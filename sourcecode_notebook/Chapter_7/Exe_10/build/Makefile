DIFF ?= diff
CXXFLAGS += -Wall -std=c++11
CXX = mpicxx
MPIEXEC ?= mpiexec
MPIFLAGS ?= -np 2
SORT ?= sort
MV ?= mv

EXE = wordcount
OBJS = main.o word_counter.o MPI_helpers.o
TESTS = test_capitalization.diff test_punctuation.diff test_page.diff test_large.diff

main.o word_counter.o: word_counter.hh
main.o MPI_helpers.o: MPI_helpers.hh

CPPFLAGS += -I../src
VPATH = ../src ../test
.DEFAULT_GOAL = all

all: build

.PHONY: all build check clean checkclean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

check: build $(TESTS)

.PRECIOUS: stdout_%.txt stderr_%.txt
stdout_%.txt stderr_%.txt: input_%.txt $(EXE)
	$(MPIEXEC) $(MPIFLAGS) $(EXE) < $< > stdout_$*.txt 2> stderr_$*.txt
	@$(SORT) stdout_$*.txt > aux.txt
	@$(MV) aux.txt stdout_$*.txt

test_%.diff: expected_%.txt stdout_%.txt
	@$(DIFF) -u $^ > $@ 2> /dev/null || echo Test failed: $*

clean:
	$(RM) *.o

checkclean:
	$(RM) stdout*.txt stderr*.txt test*.diff

distclean: clean checkclean
	$(RM) $(EXE)
	$(RM) *~ ../src/*~ ../test/*~
