#pragma once

#include "../manager/manager.hh"
#include "../chip_driver/chip_driver_models.hh"

#include <string>
#include <boost/algorithm/string.hpp>

#include <chrono>
#include <thread>

namespace cmd_client {

class CmdClient
{
public:
    static CmdClient& getInstance();

    void parseCmd(std::string);
    void help() const;
    void goToWork();
    void goToWork(std::string a_Cmd);

private:
    CmdClient(): m_Working(false) {}
    void startDevice(std::string devName, std::string driverName) const;
    void stopDevice(std::string devName) const;
    void listRunningDevices() const;
    void listSupportedChips() const;
    void exit();

    bool m_Working;
};

} // namespace cmd_client