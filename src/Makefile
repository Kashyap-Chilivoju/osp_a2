# Variables
CFLAGS = -std=c++11
SOURCES = main.cpp simulator.cpp pcb.cpp loader.cpp
PROGRAMS = fifo sjf rr
DATAFILE = datafile#insert data here

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
	@./rr 100 $(DATAFILE)

clean:
	@rm -f $(PROGRAMS)

test1:
	@echo "Running FIFO with datafile_1:"
	@./fifo datafile_1
	@echo "\nRunning SJF with datafile_1:"
	@./sjf datafile_1
	@echo "\nRunning RR with datafile_1 and quantum = 10:"
	@./rr 10 datafile_1
	@echo "\nRunning RR with datafile_1 and quantum = 25:"
	@./rr 25 datafile_1
	@echo "\nRunning RR with datafile_1 and quantum = 50:"
	@./rr 50 datafile_1
	@echo "\nRunning RR with datafile_1 and quantum = 75:"
	@./rr 75 datafile_1
	@echo "\nRunning RR with datafile_1 and quantum = 100:"
	@./rr 100 datafile_1

test2:
	@echo "Running FIFO with datafile_2:"
	@./fifo datafile_2
	@echo "\nRunning SJF with datafile_2:"
	@./sjf datafile_2
	@echo "\nRunning RR with datafile_2 and quantum = 10:"
	@./rr 10 datafile_2
	@echo "\nRunning RR with datafile_2 and quantum = 25:"
	@./rr 25 datafile_2
	@echo "\nRunning RR with datafile_2 and quantum = 50:"
	@./rr 50 datafile_2
	@echo "\nRunning RR with datafile_2 and quantum = 75:"
	@./rr 75 datafile_2
	@echo "\nRunning RR with datafile_2 and quantum = 100:"
	@./rr 100 datafile_2

test3:
	@echo "Running FIFO with datafile_3:"
	@./fifo datafile_3
	@echo "\nRunning SJF with datafile_3:"
	@./sjf datafile_3
	@echo "\nRunning RR with datafile_3 and quantum = 10:"
	@./rr 10 datafile_3
	@echo "\nRunning RR with datafile_3 and quantum = 25:"
	@./rr 25 datafile_3
	@echo "\nRunning RR with datafile_3 and quantum = 50:"
	@./rr 50 datafile_3
	@echo "\nRunning RR with datafile_3 and quantum = 75:"
	@./rr 75 datafile_3
	@echo "\nRunning RR with datafile_3 and quantum = 100:"
	@./rr 100 datafile_3

test4:
	@echo "Running FIFO with datafile_4:"
	@./fifo datafile_4
	@echo "\nRunning SJF with datafile_4:"
	@./sjf datafile_4
	@echo "\nRunning RR with datafile_4 and quantum = 10:"
	@./rr 10 datafile_4
	@echo "\nRunning RR with datafile_4 and quantum = 25:"
	@./rr 25 datafile_4
	@echo "\nRunning RR with datafile_4 and quantum = 50:"
	@./rr 50 datafile_4
	@echo "\nRunning RR with datafile_4 and quantum = 75:"
	@./rr 75 datafile_4
	@echo "\nRunning RR with datafile_4 and quantum = 100:"
	@./rr 100 datafile_4

test5:
	@echo "Running FIFO with datafile_5:"
	@./fifo datafile_5
	@echo "\nRunning SJF with datafile_5:"
	@./sjf datafile_5
	@echo "\nRunning RR with datafile_5 and quantum = 10:"
	@./rr 10 datafile_5
	@echo "\nRunning RR with datafile_5 and quantum = 25:"
	@./rr 25 datafile_5
	@echo "\nRunning RR with datafile_5 and quantum = 50:"
	@./rr 50 datafile_5
	@echo "\nRunning RR with datafile_5 and quantum = 75:"
	@./rr 75 datafile_5
	@echo "\nRunning RR with datafile_5 and quantum = 100:"
	@./rr 100 datafile_5

test6:
	@echo "Running FIFO with datafile_6:"
	@./fifo datafile_6
	@echo "\nRunning SJF with datafile_6:"
	@./sjf datafile_6
	@echo "\nRunning RR with datafile_6 and quantum = 10:"
	@./rr 10 datafile_6
	@echo "\nRunning RR with datafile_6 and quantum = 25:"
	@./rr 25 datafile_6
	@echo "\nRunning RR with datafile_6 and quantum = 50:"
	@./rr 50 datafile_6
	@echo "\nRunning RR with datafile_6 and quantum = 75:"
	@./rr 75 datafile_6
	@echo "\nRunning RR with datafile_6 and quantum = 100:"
	@./rr 100 datafile_6

test7:
	@echo "Running FIFO with datafile_7:"
	@./fifo datafile_7
	@echo "\nRunning SJF with datafile_7:"
	@./sjf datafile_7
	@echo "\nRunning RR with datafile_7 and quantum = 10:"
	@./rr 10 datafile_7
	@echo "\nRunning RR with datafile_7 and quantum = 25:"
	@./rr 25 datafile_7
	@echo "\nRunning RR with datafile_7 and quantum = 50:"
	@./rr 50 datafile_7
	@echo "\nRunning RR with datafile_7 and quantum = 75:"
	@./rr 75 datafile_7
	@echo "\nRunning RR with datafile_7 and quantum = 100:"
	@./rr 100 datafile_7

test8:
	@echo "Running FIFO with datafile_8:"
	@./fifo datafile_8
	@echo "\nRunning SJF with datafile_8:"
	@./sjf datafile_8
	@echo "\nRunning RR with datafile_8 and quantum = 10:"
	@./rr 10 datafile_8
	@echo "\nRunning RR with datafile_8 and quantum = 25:"
	@./rr 25 datafile_8
	@echo "\nRunning RR with datafile_8 and quantum = 50:"
	@./rr 50 datafile_8
	@echo "\nRunning RR with datafile_8 and quantum = 75:"
	@./rr 75 datafile_8
	@echo "\nRunning RR with datafile_8 and quantum = 100:"
	@./rr 100 datafile_8

test9:
	@echo "Running FIFO with datafile_9:"
	@./fifo datafile_9
	@echo "\nRunning SJF with datafile_9:"
	@./sjf datafile_9
	@echo "\nRunning RR with datafile_9 and quantum = 10:"
	@./rr 10 datafile_9
	@echo "\nRunning RR with datafile_9 and quantum = 25:"
	@./rr 25 datafile_9
	@echo "\nRunning RR with datafile_9 and quantum = 50:"
	@./rr 50 datafile_9
	@echo "\nRunning RR with datafile_9 and quantum = 75:"
	@./rr 75 datafile_9
	@echo "\nRunning RR with datafile_9 and quantum = 100:"
	@./rr 100 datafile_9

test10:
	@echo "Running FIFO with datafile_10:"
	@./fifo datafile_10
	@echo "\nRunning SJF with datafile_10:"
	@./sjf datafile_10
	@echo "\nRunning RR with datafile_10 and quantum = 10:"
	@./rr 10 datafile_10
	@echo "\nRunning RR with datafile_10 and quantum = 25:"
	@./rr 25 datafile_10
	@echo "\nRunning RR with datafile_10 and quantum = 50:"
	@./rr 50 datafile_10
	@echo "\nRunning RR with datafile_10 and quantum = 75:"
	@./rr 75 datafile_10
	@echo "\nRunning RR with datafile_10 and quantum = 100:"
	@./rr 100 datafile_10

test: build test1 test2 test3 test4	test5 test6 test7 test8 test9 test10 clean
