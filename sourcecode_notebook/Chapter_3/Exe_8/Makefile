CXXFLAGS += -Wall -std=c++11
EXE = KMeans
OBJS = KMeans.o Clustering.o Centroid.o Point.o

.PHONY: all clean distclean

.DEFAULT_GOAL: all

all: $(EXE)

KMeans.o: Clustering.hpp Centroid.hpp Point.hpp
Clustering.o: Clustering.hpp Centroid.hpp Point.hpp
Centroid.o: Centroid.hpp Point.hpp
Point.o: Point.hpp

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
