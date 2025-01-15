CXXFLAGS += -Wall -std=c++11 \
   -Werror \
   -Wextra \
   -Wconversion \
   -Wno-deprecated \
   -Winit-self \
   -Wsign-conversion \
   -Wredundant-decls \
   -Wvla -Wshadow -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual \
   -Winit-self \
   -Wpointer-arith \
   -Wcast-qual \
   -Wcast-align \
   -Wdouble-promotion \
   -Wold-style-cast -Wno-error=old-style-cast \
   -Wsign-promo \
   -Wswitch-enum \
   -Wswitch-default \
   -Wundef

EXE = matrices
OBJS = main.o block.o matrix.o dense_matrix.o block_matrix.o

.DEFAULT_GOAL = all

block.o: block.hpp dense_matrix.hpp matrix.hpp
block_matrix.o: block_matrix.hpp block.hpp dense_matrix.hpp matrix.hpp
dense_matrix.o: dense_matrix.hpp matrix.hpp
matrix.o: matrix.hpp
main.o: block.hpp dense_matrix.hpp matrix.hpp block_matrix.hpp

all: build

.PHONY: all build clean distclean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
