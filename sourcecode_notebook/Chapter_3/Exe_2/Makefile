CXXFLAGS += -Wall -std=c++11
M = Roots2
OBJ = Roots2.o Robust.o Newton.o Bisection.o Function.o RootFinder.o

Function.o RootFinder.o Newton.o Bisection.o Robust.o Roots2.o: Function.hpp rootfinding.hpp
RootFinder.o Newton.o Bisection.o Robust.o Roots2.o: RootFinder.hpp
Newton.o Robust.o Roots2.o: Newton.hpp 
Bisection.o Robust.o Roots2.o: Bisection.hpp 
Robust.o Roots2.o: Robust.hpp

.DEFAULT_GOAL = all

all: $(M)

.PHONY: all clean distclean

$(M): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

clean:
	$(RM) $(OBJ)

distclean: clean
	$(RM) $(M)
	$(RM) *~
