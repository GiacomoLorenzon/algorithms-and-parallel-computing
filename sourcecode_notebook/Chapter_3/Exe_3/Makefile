CXXFLAGS += -Wall -std=c++11

EXE = interp
OBJS = main.o Point.o Interpolation.o LinearInterpolation.o \
       StepwiseInterpolation.o NearestNeighborInterpolation.o

NearestNeighborInterpolation.o : NearestNeighborInterpolation.hpp Point.hpp \
                                 Interpolation.hpp
StepwiseInterpolation.o : StepwiseInterpolation.hpp Point.hpp Interpolation.hpp
LinearInterpolation.o : LinearInterpolation.hpp Point.hpp Interpolation.hpp
Interpolation.o : Point.hpp Interpolation.hpp
Point.o : Point.hpp
main.o : LinearInterpolation.hpp Point.hpp Interpolation.hpp \
         StepwiseInterpolation.hpp NearestNeighborInterpolation.hpp

.DEFAULT_GOAL = all

.PHONY : all clean distclean run build

all : build

build : $(EXE)

$(EXE) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

run : $(EXE)
	./$< < value.txt

clean :
	$(RM) $(OBJS)
	$(RM) $(EXE)

distclean : clean
	$(RM) *~
