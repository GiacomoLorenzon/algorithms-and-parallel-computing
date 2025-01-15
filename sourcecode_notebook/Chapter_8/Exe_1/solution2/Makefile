CXXFLAGS += -Wall -std=c++11

EXE = dataframe
OBJS = main.o

main.o: DataFrame.h

.DEFAULT_GOAL = all

all: build

.PHONY: all build clean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

clean:
	$(RM) $(EXE)
	$(RM) $(OBJS)
	$(RM) *~
