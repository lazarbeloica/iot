
#include "chip_driver_models.hh"

namespace chip_driver {

const std::vector<std::string> getSupported() {
    std::vector<std::string> list;
    list.push_back(BME280);

    return list;
}


} // namespace chip_driver