#include "cmd_client.hh"


namespace cmd_client {

CmdClient& CmdClient::getInstance() {
    static CmdClient m_Instance;
    return m_Instance;
}

void CmdClient::goToWork() {
    m_Working = true;
    std::string cmd;
    while (m_Working) {
        std::getline(std::cin, cmd);
        parseCmd(cmd);
    }
}

void CmdClient::parseCmd(std::string a_Cmd) {
    std::vector<std::string> cmd;
    boost::split(cmd, a_Cmd, boost::is_any_of("\t "));
    if (cmd.empty()) {
        return;
    }

    boost::algorithm::to_lower(cmd[0]);
    if (cmd[0].compare("start") == 0) {
        if (cmd.size() != 3) {
            LOG_ERROR("Start command takes 2 arguments!");
            return;
        }
        startDevice(cmd[1], cmd[2]);
    }
    else if (cmd[0].compare("stop") == 0){
        if (cmd.size() != 2) {
            LOG_ERROR("Stop command takes 1 argument!");
            return;
        }
        stopDevice(cmd[1]);
    }
    else if (cmd[0].compare("listrunning") == 0) {
        if (cmd.size() != 1) {
            LOG_ERROR("listRunning command takes no arguments!");
            return;
        }
        listRunningDevices();
    }
    else if (cmd[0].compare("listsupportedchips") == 0) {
        if (cmd.size() != 1) {
            LOG_ERROR("listSupportedChips command takes no arguments!");
            return;
        }
        listSupportedChips();
    }
    else if (cmd[0].compare("exit") == 0) {
        if (cmd.size() != 1) {
            LOG_ERROR("exit command takes no arguments!");
            return;
        }
        this->exit();
    }
    else if (cmd[0].compare("help") == 0) {
        if (cmd.size() != 1) {
            LOG_ERROR("help command takes no arguments!");
            return;
        }
        help();
    }
    else{
        LOG_ERROR("Command %s is not supported!", cmd[0].c_str());
    }
}

void CmdClient::help() const{
    std::string help;
    help = "Available commands:\n\n"
            "start: \n"
            "Usage:\tstart deviceName chipModel\n"
            "Brief: Creates and starts a device with a given name, using a given ship attached to the RPi\n"
            "Params:\n\tdeviceName - How you wish to name the device\n\tchipModel - Chip model you wish to use\n\n";

    help += "stop: \n"
            "Usage:\tstop deviceName\n"
            "Brief: Stops a /home/aviator/projects/iot/server_app/dash/index.html with a given name. The device must be running.\n"
            "Params:\n\tdeviceName - Name of the device you wish to stop\n\n";

    help += "listRunning: \n"
            "Usage:\tlistRunning\n"
            "Brief: Lists the running devices.\n\n";

    help += "listSupportedChips: \n"
            "Usage:\tlistSupportedChips\n"
            "Brief: Lists supported chipes attached to the RPi.\n\n";

    help += "exit: \n"
            "Brief: Stops the program.\n\n";

    help += "The commands are case insensitive.";

    std::cout << help << std::endl;
}

void CmdClient::startDevice(std::string devName, std::string driverName) const {
    piman::Manager* man = piman::Manager::getInstance();
    man->createPiman(devName, driverName);
}

void CmdClient::stopDevice(std::string devName) const {
    piman::Manager* man = piman::Manager::getInstance();
    man->destoyPiman(devName);
}
void CmdClient::listRunningDevices() const {
    piman::Manager* man = piman::Manager::getInstance();
    std::vector<std::string> list = man->listPiman();

    std::string msg;
    if (list.empty()) {
        msg = "There are no devices running!\n";

    }
    else {
        msg = "The running devices are:\n";
        for(auto el: list) {
            msg += "\t" + el + "\n";
        }
    }

    std::cout << msg << std::endl;
}

void CmdClient::listSupportedChips() const {
    std::vector<std::string> list = chip_driver::getSupported();
    std::string msg;
    if (list.empty()) {
        msg = "There are no supported chips!\n";

    }
    else {
        msg = "The running devices are:\n";
        for(auto el: list) {
            msg += "\t" + el + "\n";
        }
    }

    std::cout << msg << std::endl;
}

void CmdClient::exit() {
    m_Working = false;
}

} // namespace cmd_client