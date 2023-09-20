#include "simulator.h"
#include <algorithm>
#include <iostream>

simulator::simulator(const std::vector<pcb>& processes) : processes(processes) {}

void simulator::fifo() {
    osp2023::time_type currentTime = 0;
    for (auto& process : processes) {
        osp2023::time_type processTime = process.total_time;
        currentTime += processTime;
        process.useTime(processTime);
        std::cout << "FIFO Process " << process.id << " finished at " << currentTime << " ms.\n";
    }
    // Average turnaround time – this is the time from when a process is enqueued until the process completes.
    // Average waiting time – how long on average each process spends waiting in the ready queue.
    // Average response time – how long on average each process spends waiting in the ready queue until the first response is produced.
}
bool compareTotalTime(const pcb& a, const pcb& b) {
    return a.total_time < b.total_time;
}

void simulator::sjf() {
    std::sort(processes.begin(), processes.end(), compareTotalTime);

    osp2023::time_type currentTime = 0;
    for (const auto& process : processes) {
        currentTime += process.total_time;
        std::cout << "SJF Process " << process.id << " finished at " << currentTime << " ms.\n";
    }
    // Average turnaround time – this is the time from when a process is enqueued until the process completes.
    // Average waiting time – how long on average each process spends waiting in the ready queue.
    // Average response time – how long on average each process spends waiting in the ready queue until the first response is produced.
}

void simulator::rr(int quantum) {
    if(quantum<pcb::MIN_DURATION||quantum>pcb::MAX_DURATION) {
        std::cerr << "Invalid quantum, please input quantum value between 10-100." << std::endl;
        exit(0);
    }
    int n = processes.size();
    std::vector<int> remaining_time(n);
    for (int i = 0; i < n; i++)
        remaining_time[i] = processes[i].total_time;

    osp2023::time_type currentTime = 0;

    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = false;

                if (remaining_time[i] > quantum) {
                    currentTime += quantum;
                    remaining_time[i] -= quantum;
                    std::cout << "RR Process " << processes[i].id << " currently " << currentTime << " ms.\n";
                } else {
                    currentTime += remaining_time[i];
                    std::cout << "RR Process " << processes[i].id << " finished at " << currentTime << " ms.\n";
                    remaining_time[i] = 0;
                }
            }
        }

        if (done == true)
            break;
    }
    // Average turnaround time – this is the time from when a process is enqueued until the process completes.
    // Average waiting time – how long on average each process spends waiting in the ready queue.
    // Average response time – how long on average each process spends waiting in the ready queue until the first response is produced.
}

