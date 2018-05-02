#include "debug.hh"
#include "chip_reader.hh"
#include "bme280_reader.hh"
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace chip_driver;

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
        std::this_thread::sleep_for(std::chrono::milliseconds(5*1000));
        reader->measure();
        LOG_DEBUG("Tmp: %f\nPress: %f\nHum: %f",reader->extractTemperature(),
                                            reader->extractPresure(),
                                            reader->extractHumidity());
    }
    return 0;
}