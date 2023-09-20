#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "pcb.h"
#include <vector>

class simulator {
private:
    std::vector<pcb> processes;

public:
    // Constructor that initializes the simulator with a list of processes
    simulator(const std::vector<pcb>& processes);

    // Simulate First-In First-Out (FIFO) scheduling algorithm
    void fifo();

    // Simulate Shortest Job First (SJF) scheduling algorithm
    void sjf();

    // Simulate Round Robin (RR) scheduling algorithm with a given quantum
    void rr(int quantum);
};

#endif // SIMULATOR_H
