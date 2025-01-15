CXXFLAGS += -Wall -std=c++11
M = main_user
OBJ = main_user.o Date.o

.PHONY: all clean distclean

.DEFAULT_GOAL: all

all: $(M)

main_user.o: Date.hpp
Date.o: Date.hpp

$(M): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^  $(OUTPUT_OPTION)

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(M)
	$(RM) ~*
