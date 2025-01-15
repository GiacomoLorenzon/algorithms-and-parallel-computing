CXXFLAGS += -Wall -std=c++11
M = main
OBJ = main.o

.PHONY: all clean distclean

.DEFAULT_GOAL= all

all: $(M)

main.o: Secretary.hpp Manager.hpp Developer.hpp Employee.hpp

$(M): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ)

distclean: clean
	$(RM) $(M)
	$(RM) *~
