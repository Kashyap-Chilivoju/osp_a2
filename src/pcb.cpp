#include "pcb.h"

void pcb::useTime(osp2023::time_type time) {
    time_used += time;
    if (time_used > total_time) {
        time_used = total_time;
    }
}

osp2023::time_type pcb::getTimeRemaining() const {
    return total_time - time_used;
}
