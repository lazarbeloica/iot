#include "chip_reader_factory.hh"
#include "chip_driver_models.hh"
#include "chip_reader.hh"
#include "bme280_reader.hh"

#include "../debug.hh"
#include <memory>
#include <string>

namespace chip_driver {

ChipReaderFactory& ChipReaderFactory::getInstance() {
    static ChipReaderFactory m_Factory;
    return m_Factory;
}

std::shared_ptr<ChipReader> ChipReaderFactory::createChipReader(std::string a_ChipName, std::string a_FileName, int a_SlaveAddr) {
    if (a_ChipName.compare(BME280) == 0) {
        return std::make_shared<BME280Reader>(a_FileName, a_SlaveAddr);
    }

    LOG_ERROR("Chip driver for %s not supported", a_ChipName.c_str());
    return nullptr;
}

} // namespace chip_driver