DIFF ?= diff
CXXFLAGS += -Wall -std=c++11

EXE = sparse
OBJS = main.o 
TESTS = test_3x3.diff test_5x8.diff

main.o: lil_sparse.hh

.DEFAULT_GOAL = all

all: build

.PHONY: all build clean distclean check testclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

check: build $(TESTS)

test_%.diff: stdout_%.txt expected_%.txt
	@echo "Performing test $*"
	@$(DIFF) -u $^ > $@ || echo Test $* failed\!

.PRECIOUS: stdout_%.txt stderr_%.txt
stdout_%.txt stderr_%.txt: stdin_%.txt $(EXE)
	./$(EXE) < $< > stdout_$*.txt 2> stderr_$*.txt

clean:
	$(RM) $(OBJS)

testclean:
	$(RM) stdout_*.txt stderr_*.txt
	$(RM) $(TESTS)

distclean: clean testclean
	$(RM) $(EXE)
	$(RM) *~
