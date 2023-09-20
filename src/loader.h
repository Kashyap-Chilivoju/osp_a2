#include "pcb.h"
#include <vector>

class loader {
public:
    static std::vector<pcb> loadData(const std::string& filename);
};
