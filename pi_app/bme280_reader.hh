#pragma once

#include "chip_reader.hh"
#include "BME280_driver/bme280.h"
#include "BME280_driver/bme280_defs.h"

#include <chrono>
#include <thread>

class BME208Reader: public ChipReader
{
private:
    const unsigned char id_reg_adr = 0xD0;
    const unsigned char ctrl_meas_adr = 0xF4;
    const unsigned char ctrl_hum_adr = 0xF2;
    unsigned char config_adr = 0xF5;
    const unsigned char data_start_adr = 0xF7;
    const unsigned char status_adr = 0xF3;
    const unsigned char reset_adr = 0xE0;


    const int DATA_BYTES_LEN = 8;       //temp, press, humidity
    const unsigned char CHIP_ID = 0x60;
    const unsigned char CONFIG = 0b00000000;      //IIR filter off; x1 sampling rate
    const unsigned char CTRL_MEAS = 0b00100101;   //work in the foreced mode
    const unsigned char CTRL_HUM = 0b00000001;    //x1 sampling rate
    const unsigned char RESET_CMD = 0xB6;
    const unsigned char STATUS_OK = 0;

    unsigned char *m_readData;

    unsigned char *m_digT;
    unsigned char *m_digP;
    unsigned char *m_digH;

    struct bme280_dev bme280_dev;
    struct bme280_data data; 
public:

    BME208Reader(std::string a_FileName, int a_SlaveAddr);
    ~BME208Reader() override;

    bool testConnection() const;

    bool measure();
    int extractTemperature() const;
    int extractHumidity() const;
    int extractPresure() const;
};