#pragma once

#include "chip_reader.hh"

#include <string>
#include <memory>

namespace chip_driver {

class ChipReaderFactory
{
public:
    static ChipReaderFactory& getInstance();

    std::shared_ptr<ChipReader> createChipReader(std::string a_ChipName, std::string a_FileName, int a_SlaveAddr);

};

} // namespace chip_driver