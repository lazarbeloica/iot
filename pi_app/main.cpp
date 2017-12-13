
#include <iostream>
#include "httprequest_generator.hh"

int main(int argc, char **argv) { 
    std::cout << "Program started" << std::endl;
    HTTPRequestGenerator::run();
    std::cout << "Program ended" << std::endl;
    return 0;
}