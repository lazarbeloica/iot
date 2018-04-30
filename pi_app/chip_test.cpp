#include <iostream>
#include "debug.hh"
#include "chip_reader.hh"
#include "bme280_reader.hh"

int main() {
    ChipReader *reader = nullptr;

    LOG_DEBUG("Starting the chip test");

    LOG_DEBUG("Creating an instance of bme280 reader");
    try {
        reader = new BME208Reader("/dev/i2c-1", 0x76);
    }catch (std::runtime_error e) {
        LOG_ERROR("Someting went wrong when creating an insrance");
        return -1;
    }
    LOG_DEBUG("Instance succesfully connected");

    LOG_DEBUG("Starting the connection test");

    if(!reader->testConnection()) {
        LOG_DEBUG("No connection");
        return -2;
    }
    LOG_DEBUG("We have connection");
    while (true) {
        reader->measure();
        reader->extractTemperature();
    }
    return 0;
}