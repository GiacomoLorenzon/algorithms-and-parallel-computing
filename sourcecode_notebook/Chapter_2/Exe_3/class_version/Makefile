CXXFLAGS += -Wall -std=c++11
M = Roots
OBJ = Roots.o Robust.o Newton.o Bisection.o Function.o

Function.o: Function.h rootfinding.h 
Newton.o: Newton.h Function.h rootfinding.h 
Bisection.o: Bisection.h Function.h rootfinding.h 
Robust.o: Robust.h Newton.h Bisection.h Function.h rootfinding.h
Roots.o: Robust.h Newton.h Bisection.h Function.h rootfinding.h

.PHONY: all clean distclean

.DEFAULT_GOAL = all

all: $(M)

$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c $< $(OUTPUT_OPTIONS)

$(M): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

clean:
	$(RM) $(OBJ)

distclean: clean
	$(RM) $(M)
	$(RM) *~
