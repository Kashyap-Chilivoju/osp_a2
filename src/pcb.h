#include <iostream>
#include "types.h"

#pragma once  // tells the compiler to only include this file once
              /**
 * the process control block - represents a process that needs to be executed in
 * our simulator. Please note the I used some custom types of osp2023::time_type
 * and osp2023::id_type. these are just aliases to long integers but they are
 * more meaningful type names, hinting at how they will be used. Please see
 * their definitions in types.h.
 **/
class pcb {
public:
    // the unique process id
    osp2023::id_type id;
    // the total time that a process / job should run for
    osp2023::time_type total_time;
    // the time that has been used so far for this process
    osp2023::time_type time_used;
    // the priority level for this process
    // how much time has this process spent waiting for the cpu?
    osp2023::time_type total_wait_time;
    // what time was this process last on the cpu?
    osp2023::time_type last_cpu_time = osp2023::time_not_set;

    osp2023::time_type response_time = osp2023::time_not_set;

    // max and min duration for a process in our system.
    static const osp2023::time_type MAX_DURATION = 100;
    static const osp2023::time_type MIN_DURATION = 10;

    pcb(osp2023::id_type id_, osp2023::time_type total_time_)
            : id(id_), total_time(total_time_) {}

    void useTime(osp2023::time_type time);
    osp2023::time_type getTimeRemaining() const;
};
