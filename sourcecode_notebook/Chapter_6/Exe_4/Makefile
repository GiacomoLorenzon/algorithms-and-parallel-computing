CXXFLAGS += -Wall -std=c++11
EXE = main
OBJS = main.o ContinousStream.o MicroBatch.o

.PHONY: all clean distclean

DEFAULT_GOAL: all

all: $(EXE)

main.o: ContinousStream.h MicroBatch.h
ContinousStream.o: ContinousStream.h MicroBatch.h
MicroBatch.o: MicroBatch.h

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
