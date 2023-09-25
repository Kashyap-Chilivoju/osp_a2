#include "simulator.h"
#include "deque"

simulator::simulator(const std::vector <pcb> &processes) : processes(processes) {}

void simulator::fifo() {
    osp2023::time_type currentTime = 0;
    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0;
    osp2023::time_type totalResponseTime = 0;

    std::cout << "FIFO Scheduling:" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Process ID | Burst Time  | Turnaround Time | Waiting Time | Response Time   ||" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    for (auto &process: processes) {
        // If last_cpu_time is not set, it means it's the process's first time on the CPU
        if (process.last_cpu_time == osp2023::time_not_set) {
            process.last_cpu_time = currentTime;
        }

        osp2023::time_type processTime = process.total_time;
        process.useTime(processTime);  // Update the time used by the process
        currentTime += processTime;

        osp2023::time_type turnaroundTime = currentTime;  // Since all processes have an arrival time of 0 in FIFO
        osp2023::time_type waitingTime = currentTime - processTime - process.total_wait_time;
        osp2023::time_type responseTime = process.last_cpu_time;

        process.total_wait_time += waitingTime;  // Update total wait time for the process

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;
        totalResponseTime += responseTime;

        std::cout << process.id << "\t   | "
                  << processTime << " ms\t | "
                  << turnaroundTime << " ms\t   | "
                  << waitingTime << " ms\t  | "
                  << responseTime << " ms\t    ||" << std::endl;
    }

    std::cout << "------------------------------------------------------------------------------" << std::endl;

    int numProcesses = processes.size();

    std::cout << "\nFIFO Average Metrics:" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Average Turnaround Time: " << totalTurnaroundTime / numProcesses << " ms   |" << std::endl;
    std::cout << "Average Waiting Time: " << totalWaitingTime / numProcesses << " ms\t   |" << std::endl;
    std::cout << "Average Response Time: " << totalResponseTime / numProcesses << " ms\t   |" << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

bool compareTotalTime(const pcb &a, const pcb &b) {
    return a.total_time < b.total_time;
}

void simulator::sjf() {
    // Sort processes based on their total_time.
    std::sort(processes.begin(), processes.end(), compareTotalTime);

    osp2023::time_type currentTime = 0;
    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0;
    osp2023::time_type totalResponseTime = 0;

    std::cout << "SJF Scheduling:" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Process ID | Burst Time  | Turnaround Time | Waiting Time | Response Time   ||" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    for (auto &process: processes) {
        // If last_cpu_time is not set, it means it's the process's first time on the CPU.
        if (process.last_cpu_time == osp2023::time_not_set) {
            process.last_cpu_time = currentTime;
        }

        osp2023::time_type processTime = process.total_time;
        process.useTime(processTime);  // Update the time used by the process.
        currentTime += processTime;

        osp2023::time_type turnaroundTime = currentTime;
        osp2023::time_type waitingTime = currentTime - processTime - process.total_wait_time;
        osp2023::time_type responseTime = process.last_cpu_time;

        process.total_wait_time += waitingTime;  // Update total wait time for the process.

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;
        totalResponseTime += responseTime;

        std::cout << process.id << "\t   | "
                  << processTime << " ms\t | "
                  << turnaroundTime << " ms\t   | "
                  << waitingTime << " ms\t  | "
                  << responseTime << " ms\t    ||" << std::endl;
    }

    std::cout << "------------------------------------------------------------------------------" << std::endl;

    int numProcesses = processes.size();

    std::cout << "\nSJF Average Metrics:" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Average Turnaround Time: " << totalTurnaroundTime / numProcesses << " ms   |" << std::endl;
    std::cout << "Average Waiting Time: " << totalWaitingTime / numProcesses << " ms\t   |" << std::endl;
    std::cout << "Average Response Time: " << totalResponseTime / numProcesses << " ms\t   |" << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

void simulator::rr(int quantum) {
    if (quantum < pcb::MIN_DURATION || quantum > pcb::MAX_DURATION) {
        std::cerr << "Invalid quantum, please input quantum value between 10-100." << std::endl;
        exit(0);
    }

    int n = processes.size();
    osp2023::time_type currentTime = 0;
    std::deque < pcb * > readyQueue;

    for (pcb &process: processes) {
        readyQueue.push_back(&process);
    }

    std::cout << "RR Scheduling (Quantum: " << quantum << "ms):" << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << "Process ID | Burst Time  | Time Remaining | Turnaround Time  | Waiting Time | Response Time  ||"
              << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------"
              << std::endl;

    while (!readyQueue.empty()) {
        pcb *process = readyQueue.front();
        readyQueue.pop_front();

        osp2023::time_type remaining_time = process->getTimeRemaining();

        if (process->last_cpu_time == osp2023::time_not_set) {
            process->response_time = currentTime;
        }

        if (remaining_time > quantum) {
            process->useTime(quantum);
            currentTime += quantum;
            process->last_cpu_time = currentTime;
            readyQueue.push_back(process);
        } else {
            process->useTime(remaining_time);
            currentTime += remaining_time;
            process->last_cpu_time = currentTime;
        }

        process->total_wait_time = currentTime - process->time_used;

        osp2023::time_type turnaroundTime = process->time_used + process->total_wait_time;
        std::cout << process->id << "\t   | "
                  << process->total_time << " ms\t | "
                  << process->getTimeRemaining() << " ms left\t  | "
                  << turnaroundTime << " ms\t     | "
                  << process->total_wait_time << " ms\t    | "
                  << process->response_time << " ms\t     ||" << std::endl;
    }

    std::cout << "-----------------------------------------------------------------------------------------------"
              << std::endl;
    std::cout << "\nRR Average Metrics (Quantum: " << quantum << "ms):" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0;
    osp2023::time_type totalResponseTime = 0;

    for (const auto &process: processes) {
        osp2023::time_type turnaroundTime = process.total_time + process.total_wait_time;
        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += process.total_wait_time;
        totalResponseTime += process.response_time;
    }

    std::cout << "Average Turnaround Time: " << totalTurnaroundTime / n << " ms   |" << std::endl;
    std::cout << "Average Waiting Time: " << totalWaitingTime / n << " ms\t   |" << std::endl;
    std::cout << "Average Response Time: " << totalResponseTime / n << " ms\t   |" << std::endl;
    std::cout << "------------------------------------" << std::endl;
}