#include "simulator.h"

simulator::simulator(const std::vector<pcb>& processes) : processes(processes) {}

void simulator::fifo() {
    osp2023::time_type currentTime = 0;
    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0;
    osp2023::time_type totalResponseTime = 0;

    std::cout << "FIFO Scheduling:" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Process ID | Burst Time  | Turnaround Time | Waiting Time | Response Time    |" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

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

        std::cout << process.id << "\t   | "
                  << processTime << " ms\t | "
                  << turnaroundTime << " ms\t   | "
                  << waitingTime << " ms\t  | "
                  << responseTime << " ms\t    ||" << std::endl;
    }

    std::cout << "------------------------------------------------------------------------------" << std::endl;

    int numProcesses = processes.size();

    std::cout << "\nFIFO Average Metrics:" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "Average Turnaround Time: " << totalTurnaroundTime / numProcesses << " ms" << std::endl;
    std::cout << "Average Waiting Time: " << totalWaitingTime / numProcesses << " ms" << std::endl;
    std::cout << "Average Response Time: " << totalResponseTime / numProcesses << " ms" << std::endl<< std::endl;
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

    std::cout << "SJF Scheduling:" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Process ID | Burst Time  | Turnaround Time | Waiting Time | Response Time    |" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    for (const auto& process : processes) {
        osp2023::time_type processTime = process.total_time;
        currentTime += processTime;

        osp2023::time_type turnaroundTime = currentTime; // Since arrival time is 0 for all in SJF
        osp2023::time_type waitingTime = turnaroundTime - processTime;
        osp2023::time_type responseTime = waitingTime; // In SJF, response time is same as waiting time

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
    std::cout << "---------------------" << std::endl;
    std::cout << "Average Turnaround Time: " << totalTurnaroundTime / numProcesses << " ms" << std::endl;
    std::cout << "Average Waiting Time: " << totalWaitingTime / numProcesses << " ms" << std::endl;
    std::cout << "Average Response Time: " << totalResponseTime / numProcesses << " ms" << std::endl << std::endl;
}


void simulator::rr(int quantum) {
    if (quantum < pcb::MIN_DURATION || quantum > pcb::MAX_DURATION) {
        std::cerr << "Invalid quantum, please input quantum value between 10-100." << std::endl;
        exit(0);
    }

    int n = processes.size();
    std::vector<int> remaining_time(n);
    std::vector<bool> first_response(n, true); // To track first-time execution
    std::vector<osp2023::time_type> response_times(n, 0);
    std::vector<osp2023::time_type> waiting_times(n, 0);
    std::vector<osp2023::time_type> turnaround_times(n, 0);

    for (int i = 0; i < n; i++)
        remaining_time[i] = processes[i].total_time;

    osp2023::time_type currentTime = 0;

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
                    waiting_times[i] += (currentTime - quantum - response_times[i]);
                    remaining_time[i] -= quantum;
                } else {
                    currentTime += remaining_time[i];
                    turnaround_times[i] = currentTime;
                    waiting_times[i] += (currentTime - remaining_time[i] - response_times[i]);
                    remaining_time[i] = 0;
                }
            }
        }

        if (done == true)
            break;
    }

    std::cout << "RR Scheduling (Quantum: " << quantum << "ms):" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Process ID | Burst Time  | Turnaround Time | Waiting Time | Response Time    |" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0;
    osp2023::time_type totalResponseTime = 0;

    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += turnaround_times[i];
        totalWaitingTime += waiting_times[i];
        totalResponseTime += response_times[i];

        std::cout << processes[i].id << "\t   | "
                  << processes[i].total_time << " ms\t | "
                  << turnaround_times[i] << " ms\t   | "
                  << waiting_times[i] << " ms\t  | "
                  << response_times[i] << " ms\t    ||" << std::endl;
    }

    std::cout << "------------------------------------------------------------------------------" << std::endl;

    std::cout << "\nRR Average Metrics (Quantum: " << quantum << "ms):" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "Average Turnaround Time: " << totalTurnaroundTime / n << " ms" << std::endl;
    std::cout << "Average Waiting Time: " << totalWaitingTime / n << " ms" << std::endl;
    std::cout << "Average Response Time: " << totalResponseTime / n << " ms" << std::endl << std::endl;
}



