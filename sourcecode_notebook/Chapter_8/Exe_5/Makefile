CXXFLAGS += -Wall  -std=c++11
EXE = social_network
OBJS = main.o user.o social_network.o

social_network.o: social_network.hpp user.hpp
user.o: user.hpp
main.o: social_network.hpp user.hpp

.DEFAULT_GOAL = all

all: build

.PHONY: all build clean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

clean:
	$(RM) *.o
	$(RM) $(EXE)

distclean: clean
	$(RM) *~
