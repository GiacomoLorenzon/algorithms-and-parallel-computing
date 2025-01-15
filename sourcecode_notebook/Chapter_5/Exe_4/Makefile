CXXFLAGS += -Wall -std=c++11

EXE = main
OBJS =  date_util.o csv_manager.o tax_payer.o credit_card.o
OBJS += declaration.o credit_transaction.o main.o

all: build

.PHONY: all build clean

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(OUTPUT_OPTION)

main.o date_util.o: date_util.hpp
main.o declaration.o: declaration.hpp
main.o credit_transaction.o:credit_transaction.hpp
main.o tax_payer.o: tax_payer.hpp credit_card.hpp
main.o credit_card.o: credit_card.hpp credit_transaction.hpp
main.o csv_manager.o: csv_manager.hpp credit_transaction.hpp tax_payer.hpp

clean:
	$(RM) $(OBJS) $(EXE)
