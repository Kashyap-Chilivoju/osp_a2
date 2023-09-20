#include "simulator.h"
#include "loader.h"
#include <iostream>
int main(int argc, char* argv[]) {
    std::cout << "\n";
    if (argc < 2 || argc>4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <quantum if rr>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string algorithm = argv[0];
    if (algorithm.substr(0, 2) == "./")
        algorithm = algorithm.substr(2);

    int quantum = 0;

    if (algorithm == "rr" && argc != 3) {
        std::cerr << "For RR algorithm, you need to provide the quantum value." << std::endl;
        return 1;
    } else if (algorithm == "rr") {
        quantum = std::stoi(argv[2]);
    }

    loader dataLoader;
    std::vector<pcb> processes = dataLoader.loadData(filename);
    simulator sim(processes);
    if (algorithm == "fifo"&& argc == 2) {
        sim.fifo();
    } else if (algorithm == "sjf"&& argc == 2) {
        sim.sjf();
    } else if (algorithm == "rr") {
        sim.rr(quantum);
    } else {
        std::cerr << "Invalid arguments, Usage: " << argv[0] << "<filename> <quantum if rr>" << std::endl;
        return 1;
    }

    return 0;
}
