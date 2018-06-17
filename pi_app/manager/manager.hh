#pragma once

#include "piman.hh"
#include "../chip_driver/chip_reader_factory.hh"

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace piman {

class Manager
{
public:
    static Manager* getInstance();
    bool createPiman(std::string a_devName, std::string a_driverName);
    bool destoyPiman(std::string a_devName);
    const std::vector<std::string> listPiman() const;

    void operator=(Manager&) = delete;
    void operator=(Manager&&) = delete;
    Manager(Manager&) = delete;
    Manager(Manager&&) = delete;

    Manager() {}
private:
    std::map<std::string, std::shared_ptr<Piman> > m_Pimans;
    static Manager* m_Instance;
};

} // namespace piman