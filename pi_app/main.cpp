
#include <iostream>
#include "debug.hh"
#include "manager/piman.hh"

using namespace piman;

int main(int argc, char **argv) {

    Piman *piman = Piman::getInstance();
    if (!piman) {
        std::cout << "main: Error: couldnot crete Pi Manager" << std::endl;
        exit(1);
    }

    LOG_DEBUG("main: Starting the process.");
    piman->start();
    LOG_DEBUG("main: The process finished.");

}