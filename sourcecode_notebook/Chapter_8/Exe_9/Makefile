CXXFLAGS += -g -Wall -std=c++11

EXE = deque
OBJS = main.o

main.o: deque.hh

.DEFAULT_GOAL = all

all: build

.PHONY: all build clean distclean run

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

run: $(EXE) value.txt
	./$< < value.txt

clean:
	$(RM) $(EXE)
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~
