CXXFLAGS = -Wall -std=c++11
OBJECTS = main.o Stock_quote_archive.o Stock_quote.o

.PHONY: all clean distclean

all: main

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o main

main.o: Stock_quote_archive.h Stock_quote.h

Stock_quote.o: Stock_quote.h

Stock_quote_archive.o: Stock_quote_archive.h Stock_quote.h

clean:
	$(RM) *.o

distclean: clean
	$(RM) main
