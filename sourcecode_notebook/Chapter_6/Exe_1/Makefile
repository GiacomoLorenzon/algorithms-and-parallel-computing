CXXFLAGS += -Wall -std=c++11
EXE = main
OBJS = main.o Stock_quote_archive.o Stock_quote.o

main.o Stock_quote_archive.o Stock_quote.o: Stock_quote.hpp
main.o Stock_quote_archive.o: Stock_quote_archive.hpp

.PHONY: all build run clean distclean

.DEFAULT_GOAL = all

all: build

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
