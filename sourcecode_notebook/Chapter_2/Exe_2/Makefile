CXXFLAGS += -Wall -std=c++11
EXE = main
OBJS = main.o Sales_archive.o Sales_data.o

main.o Sales_archive.o Sales_data.o: Sales_data.h
main.o Sales_archive.o: Sales_data.h

.DEFAULT_GOAL = all

all: build

.PHONY: all build run clean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run:
	./$(EXE)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
