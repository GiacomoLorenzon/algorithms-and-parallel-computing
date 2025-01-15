CXX = mpicxx
MPIEXEC = mpiexec
MPIFLAGS = -np 2
DIFF ?= diff
CXXFLAGS += -Wall -std=c++11

EXE = matrix_mult
OBJS = main.o dense_matrix.o matrix.o
TESTS = C.diff

TIC = date +%s.%N

main.o: dense_matrix.hpp
dense_matrix.o: dense_matrix.hpp matrix.hpp

.DEFAULT_GOAL = all
.PHONY: all build clean distclean check testclean

all: build

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

check: build $(TESTS)

C.diff: C_in.txt C_out.txt
	@$(DIFF) -u $^ > $@ || echo Test failed\!

C_out.txt: $(EXE) A.txt B.txt
	@$(TIC) > begin.txt
	$(MPIEXEC) $(MPIFLAGS) ./$(EXE) A.txt B.txt > C_out.txt
	@$(TIC) > end.txt
	@paste begin.txt end.txt | awk '{ print "elapsed:", $$2 - $$1, "s" }'
	@$(RM) begin.txt end.txt

clean:
	$(RM) $(OBJS)
	$(RM) $(EXE)

testclean:
	$(RM) C_out.txt $(TESTS)

distclean: clean testclean
	$(RM) *~
