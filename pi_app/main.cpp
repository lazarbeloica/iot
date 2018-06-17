
#include <iostream>
#include "debug.hh"
#include "cmd_client/cmd_client.hh"

int main(int argc, char **argv) {

    cmd_client::CmdClient cli = cmd_client::CmdClient::getInstance();

    LOG_DEBUG("main: Starting the process.");
    cli.goToWork();
    LOG_DEBUG("main: The process finished.");

}