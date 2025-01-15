CXX = g++
CXXFLAGS += -Wall -std=c++11
M = main
OBJECTS = Box.o main.o

all: $(M)

$(M): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

Box.o: Box.cpp Box.hpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

main.o: main.cpp Box.hpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

clean:
	rm -f *.o

distclean: clean
	rm -f main
