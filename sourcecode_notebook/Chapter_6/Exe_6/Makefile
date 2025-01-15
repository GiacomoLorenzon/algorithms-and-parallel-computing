CXXFLAGS += -Wall -std=c++11
EXE = patients
OBJS = date.o patient.o medicine.o main.o

date.o: date.hpp
patient.o: patient.hpp
medicine.o: medicine.hpp
main.o patient.o medicine.o: date.hpp patient.hpp medicine.hpp main.cpp

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
