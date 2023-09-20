#include "loader.h"
#include <fstream>
#include <sstream>

std::vector<pcb> loader::loadData(const std::string& filename) {
    std::vector<pcb> processes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return processes;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        osp2023::id_type id;
        osp2023::time_type total_time;
        char comma;
        if (!(iss >> id >> comma >> total_time) || comma != ',') {
            std::cerr << "Error: Malformed line in datafile: " << line << std::endl;
            continue;
        }

        processes.emplace_back(id, total_time);
    }

    return processes;
}
