
#include "debug.hh"
#include "cmd_client/cmd_client.hh"

#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

int main(int argc, char **argv) {

    LOG_DEBUG("main: Starting the process.");
    cmd_client::CmdClient cli = cmd_client::CmdClient::getInstance();
    if (argc != 1) {
        std::string cmd = argv[1];
        for (int i = 2; i < argc; cmd += " " + static_cast<std::string>(argv[i++]));
        cli.goToWork(cmd);
    }
    else {
        cli.goToWork();
    }

    LOG_DEBUG("main: The process finished.");
}