#pragma once

#include <string>
#include <vector>

namespace chip_driver {

const std::string BME280 = "bme280";

const std::vector<std::string> getSupported();
} // namespace chip_driver