#include "simulator.h"

simulator::simulator(const std::vector<pcb>& processes) : processes(processes) {}

void simulator::fifo() {
    osp2023::time_type currentTime = 0;
    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0;
    osp2023::time_type totalResponseTime = 0;

    std::cout << "FIFO Scheduling:" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Process ID | Burst Time  | Turnaround Time | Waiting Time | Response Time   ||" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    for (auto& process : processes) {
        osp2023::time_type processTime = process.total_time;
        process.useTime(processTime); // using the time for the process
        currentTime += processTime;


        osp2023::time_type turnaroundTime = currentTime; // Since arrival time is 0 for all in FIFO
        osp2023::time_type waitingTime = turnaroundTime - processTime;
        osp2023::time_type responseTime = waitingTime; // In FIFO, response time is same as waiting time

        process.total_wait_time += waitingTime; // updating total wait time for the process

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
    std::cout << "Average Turnaround Time: " << totalTurnaroundTime/numProcesses << " ms   |" << std::endl;
    std::cout << "Average Waiting Time: " << totalWaitingTime/numProcesses<< " ms\t   |" << std::endl;
    std::cout << "Average Response Time: " << totalResponseTime/numProcesses << " ms\t   |" << std::endl;
    std::cout << "------------------------------------" << std::endl;
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
    std::cout << "Process ID | Burst Time  | Turnaround Time | Waiting Time | Response Time   ||" << std::endl;
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

    std::cout << "------------------------------------------------------------------------------" << std::endl;

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
    std::vector<bool> first_response(n, true); // To track first-time execution

    osp2023::time_type currentTime = 0;

    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            pcb& process = processes[i];
            osp2023::time_type remaining_time = process.getTimeRemaining();

            if (remaining_time > 0) {
                done = false;

                if (first_response[i]) {
                    process.last_cpu_time = currentTime; // Assuming this is when it first responded
                    first_response[i] = false;
                }

                if (remaining_time > quantum) {
                    currentTime += quantum;
                    process.total_wait_time += (currentTime - quantum - process.last_cpu_time);
                    process.useTime(quantum);
                } else {
                    currentTime += remaining_time;
                    process.total_wait_time += (currentTime - remaining_time - process.last_cpu_time);
                    process.useTime(remaining_time);
                }
            }
        }

        if (done == true)
            break;
    }

    std::cout << "RR Scheduling (Quantum: " << quantum << "ms):" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "Process ID | Burst Time  | Turnaround Time | Waiting Time | Response Time   ||" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    osp2023::time_type totalTurnaroundTime = 0;
    osp2023::time_type totalWaitingTime = 0;
    osp2023::time_type totalResponseTime = 0;

    for (const auto& process : processes) {
        osp2023::time_type turnaroundTime = process.total_time + process.total_wait_time;
        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += process.total_wait_time;
        totalResponseTime += process.last_cpu_time; // Assuming last_cpu_time is the response time

        std::cout << process.id << "\t   | "
                  << process.total_time << " ms\t | "
                  << turnaroundTime << " ms\t   | "
                  << process.total_wait_time << " ms\t  | "
                  << process.last_cpu_time << " ms\t    ||" << std::endl;
    }

    std::cout << "------------------------------------------------------------------------------" << std::endl;
    std::cout << "\nRR Average Metrics (Quantum: " << quantum << "ms):" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Average Turnaround Time: " << totalTurnaroundTime / n << " ms   |" << std::endl;
    std::cout << "Average Waiting Time: " << totalWaitingTime / n << " ms\t   |" << std::endl;
    std::cout << "Average Response Time: " << totalResponseTime / n << " ms\t   |" << std::endl;
    std::cout << "------------------------------------" << std::endl;
}




