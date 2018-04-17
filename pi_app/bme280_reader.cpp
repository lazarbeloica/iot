#include "bme280_reader.hh"
#include <iostream>
#include "chip_reader.hh"

//TODO: make async
//TODO: UnitTest

BME208Reader::BME208Reader(std::string a_FileName, int a_SlaveAddr):ChipReader(a_FileName, a_SlaveAddr) {

    uint8_t res;
    if(res = bme280_init(&bme280_dev)) {
        LOG_ERROR("Could not INIT reg! code: %u", res);
        throw std::runtime_error("Could not INIT reg!");
    }

    if(res = bme280_soft_reset(&bme280_dev)) {
        LOG_ERROR("Could not write to make soft reset! code: %u", res);
        throw std::runtime_error("Could not write to make soft reset!");
    }
    LOG_DEBUG("Reset done!");

    if(res = bme280_set_regs(&config_adr, &CONFIG, 1, &bme280_dev)) {
        LOG_ERROR("Could not write to config reg! code: %u", res);
        throw std::runtime_error("Could not write to config reg!");
    }
    LOG_DEBUG("Configured reg!");

    // if (!writeToAddr(&config_adr ,&CONFIG)) {
    //     LOG_ERROR("Could not write to config reg!");
    //     throw std::runtime_error("Could not write  to config reg!");
    // }
    // LOG_DEBUG("Configured the chip");

    // if (!writeToAddr(&reset_adr ,&RESET_CMD)) {
    //     LOG_ERROR("Could not write to reset reg!");
    //     throw std::runtime_error("Could not write  to reset reg!");
    // }

    // LOG_DEBUG("Reset the chip");
    // m_readData = new unsigned char[DATA_BYTES_LEN];
}

BME208Reader::~BME208Reader() {
    delete m_readData;
}

bool BME208Reader::testConnection() const {

    unsigned char id = 0;
    if(!readFromAddr(&id_reg_adr, &id)) {
        LOG_ERROR("Not able to read form the chip");
        return false;
    }
    if(id != CHIP_ID) {
        LOG_ERROR("The chip id does not match to the default 0x60");
        return false;
    }

	return true;
}

bool BME208Reader::measure() const {
    //TODO: Incorpotate the syncronisation


    if (!writeToAddr(&ctrl_hum_adr ,&CTRL_HUM)) {
        LOG_ERROR("Could not write to ctrl_hum reg!");
        return false;


    if (!writeToAddr(&ctrl_hum_adr ,&CTRL_HUM)) {
        LOG_ERROR("Could not write to ctrl_hum reg!");
        return false;
    }

    if (!writeToAddr(&ctrl_meas_adr ,&CTRL_MEAS)) {
        LOG_ERROR("Could not write to ctrl_meas reg!");
        return false;
    }

    LOG_DEBUG("Configured the measurement");

    unsigned char status;
    do {
        if (!readFromAddr(&status_adr, &status)) {
            LOG_ERROR("Could not read the status!");
            return false;
        }
        LOG_DEBUG("The status is %u", status);
    } while(status != STATUS_OK);

    if (!readFromAddr(&data_start_adr, m_readData, DATA_BYTES_LEN)) {
        LOG_ERROR("Could not read the measured data!");
        return false;
    }

    for(int i = 0; i < 8; printf("%d. %u\n", i, m_readData[i++]));
    return true;
}

const int BME208Reader::extractTemperature() const {
    return 0;
}

const int BME208Reader::extractHumidity() const {
    return 0;
}

const int BME208Reader::extractPresure() const {
    return 0;
}
