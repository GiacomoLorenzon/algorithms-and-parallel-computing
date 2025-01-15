CXX = g++ -std=c++11
CXXFLAGS += -Wall
M = FunctionMin3
OBJECTS = FunctionMin3.o FunctionMinRn.o FunctionRn.o Monomial.o Point.o

all: $(M)

$(M): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

Point.o: Point.cpp Point.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

Monomial.o: Monomial.cpp Monomial.h Point.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

FunctionRn.o: FunctionRn.cpp FunctionRn.h Monomial.h Point.h
	$(CXX) $(CXXFLAGS) $< -c -o $@	

FunctionMinRn.o: FunctionMinRn.cpp FunctionMinRn.h FunctionRn.h Point.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

FunctionMin3.o: FunctionMin3.cpp FunctionMinRn.h
	$(CXX) $(CXXFLAGS) $< -c -o $@

clean:
	rm -f *.o

distclean: clean
	rm -f FunctionMin3



