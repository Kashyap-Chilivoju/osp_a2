#include "simulator.h"
#include <algorithm>
#include <iostream>

simulator::simulator(const std::vector<pcb>& processes) : processes(processes) {}

void simulator::fifo() {
    osp2023::time_type currentTime = 0;
    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0;
    osp2023::time_type totalResponseTime = 0;

    for (auto& process : processes) {
        osp2023::time_type processTime = process.total_time;
        currentTime += processTime;
        process.useTime(processTime);

        osp2023::time_type turnaroundTime = currentTime; // Since arrival time is 0 for all in FIFO
        osp2023::time_type waitingTime = turnaroundTime - processTime;
        osp2023::time_type responseTime = waitingTime; // In FIFO, response time is same as waiting time

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;
        totalResponseTime += responseTime;

        //std::cout << "FIFO Process " << process.id << " finished at " << currentTime << " ms.\n";
    }

    int numProcesses = processes.size();

    std::cout << "FIFO Average Turnaround Time: " << totalTurnaroundTime / numProcesses << " ms.\n";
    std::cout << "FIFO Average Waiting Time: " << totalWaitingTime / numProcesses << " ms.\n";
    std::cout << "FIFO Average Response Time: " << totalResponseTime / numProcesses << " ms.\n";
}

bool compareTotalTime(const pcb& a, const pcb& b) {
    return a.total_time < b.total_time;
}

void simulator::sjf() {
    std::sort(processes.begin(), processes.end(), compareTotalTime);

    osp2023::time_type currentTime = 0;
    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0;
    osp2023::time_type totalResponseTime = 0;

    for (const auto& process : processes) {
        osp2023::time_type processTime = process.total_time;
        currentTime += processTime;

        osp2023::time_type turnaroundTime = currentTime; // Since arrival time is 0 for all in SJF
        osp2023::time_type waitingTime = turnaroundTime - processTime;
        osp2023::time_type responseTime = waitingTime; // In SJF, response time is same as waiting time

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;
        totalResponseTime += responseTime;

        //std::cout << "SJF Process " << process.id << " finished at " << currentTime << " ms.\n";
    }

    std::cout << "SJF Average Turnaround Time: " << totalTurnaroundTime / processes.size() << " ms.\n";
    std::cout << "SJF Average Waiting Time: " << totalWaitingTime / processes.size() << " ms.\n";
    std::cout << "SJF Average Response Time: " << totalResponseTime / processes.size() << " ms.\n";
}


void simulator::rr(int quantum) {
    if(quantum<pcb::MIN_DURATION||quantum>pcb::MAX_DURATION) {
        std::cerr << "Invalid quantum, please input quantum value between 10-100." << std::endl;
        exit(0);
    }

    int n = processes.size();
    std::vector<int> remaining_time(n);
    std::vector<bool> first_response(n, true); // To track first-time execution
    std::vector<osp2023::time_type> response_times(n, 0);

    for (int i = 0; i < n; i++)
        remaining_time[i] = processes[i].total_time;

    osp2023::time_type currentTime = 0;
    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0; // Will increment later in the loop
    osp2023::time_type totalResponseTime = 0;

    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = false;

                if (first_response[i]) {
                    response_times[i] = currentTime;
                    first_response[i] = false;
                }

                if (remaining_time[i] > quantum) {
                    currentTime += quantum;
                    totalWaitingTime += (currentTime - quantum - response_times[i]);
                    remaining_time[i] -= quantum;
                    //std::cout << "RR Process " << processes[i].id << " currently " << currentTime << " ms.\n";
                } else {
                    currentTime += remaining_time[i];
                    totalTurnaroundTime += (currentTime);
                    totalWaitingTime += (currentTime - remaining_time[i] - response_times[i]);
                    //std::cout << "RR Process " << processes[i].id << " finished at " << currentTime << " ms.\n";
                    remaining_time[i] = 0;
                }
            }
        }

        if (done == true)
            break;
    }

    for (int i = 0; i < n; i++)
        totalResponseTime += response_times[i];

    std::cout << "RR Average Turnaround Time: " << totalTurnaroundTime / n << " ms.\n";
    std::cout << "RR Average Waiting Time: " << totalWaitingTime / n << " ms.\n";
    std::cout << "RR Average Response Time: " << totalResponseTime / n << " ms.\n";
}


