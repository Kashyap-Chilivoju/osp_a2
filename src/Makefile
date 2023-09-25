# Variables
CFLAGS = -std=c++11 -Wall -Wextra -Werror
SOURCES = main.cpp simulator.cpp pcb.cpp loader.cpp
PROGRAMS = fifo sjf rr
DATAFILE = datafile

all: build run clean

build: $(PROGRAMS)

fifo: $(SOURCES)
	@g++ $(CFLAGS) $^ -o fifo

sjf: $(SOURCES)
	@g++ $(CFLAGS) $^ -o sjf

rr: $(SOURCES)
	@g++ $(CFLAGS) $^ -o rr

run: $(PROGRAMS)
	@echo "Running FIFO with $(DATAFILE):"
	@./fifo $(DATAFILE)
	@echo "\nRunning SJF with $(DATAFILE):"
	@./sjf $(DATAFILE)
	@echo "\nRunning RR with $(DATAFILE) and quantum = 50:"
	@./rr 50 $(DATAFILE)

clean:
	@rm -f $(PROGRAMS)
