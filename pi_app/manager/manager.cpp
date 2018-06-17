
#include "manager.hh"

namespace piman {

const std::string FILE_DESC = "/dev/i2c-1";
const int DEFAULT_CHIP_ADDR = 0x76;
Manager* Manager::m_Instance = nullptr;

Manager* Manager::getInstance() {
    if (!m_Instance) {
        m_Instance = new Manager();
    }
    return m_Instance;
}


bool Manager::createPiman(std::string a_devName, std::string a_driverName) {

    if (m_Pimans.find(a_devName) != m_Pimans.end()) {
        LOG_ERROR("Device %s already running!", a_devName.c_str());
        return false;
    }

    std::shared_ptr<chip_driver::ChipReader> cr;

    try {
        chip_driver::ChipReaderFactory factory = chip_driver::ChipReaderFactory::getInstance();
        cr = factory.createChipReader(a_driverName, FILE_DESC, DEFAULT_CHIP_ADDR);
    }catch (std::runtime_error error) {
        LOG_WARNING("No chip reader will be attached to Piman!");
        cr.reset();
    }

    LOG_DEBUG("Creating piman...");
    std::shared_ptr<Piman> piman =
            std::make_shared<Piman>(std::make_shared<HTTPRequestGenerator> (a_devName, piman::DEFAULT_URL), cr);

    LOG_DEBUG("Starting the devices...");
    if (!piman->start()) {
        LOG_ERROR("Could not start %s!", a_devName.c_str());
        return false;
    }

    LOG_DEBUG("Adding it to the list of runnong devices...");
    m_Pimans.insert(std::make_pair(a_devName, piman));
    return true;
}

bool Manager::destoyPiman(std::string a_devName) {

    if (m_Pimans.find(a_devName) == m_Pimans.end()) {
        LOG_ERROR("No device named %s is running!", a_devName.c_str());
        return false;
    }

    LOG_DEBUG("Stopping device %s", a_devName);
    m_Pimans[a_devName]->stop();
    LOG_DEBUG("Removing it from the list of running devices.");
    m_Pimans.erase(a_devName);
    return true;
}

const std::vector<std::string> Manager::listPiman() const {

    std::vector<std::string> list;
    for(auto el: m_Pimans) {
        list.push_back(el.first);
    }
    return list;
}


} // namespace piman