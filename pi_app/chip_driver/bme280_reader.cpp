#include "bme280_reader.hh"
#include "chip_reader.hh"
#include "BME280_driver/bme280.h"
#include "BME280_driver/bme280_defs.h"

#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std::placeholders;

//used for an ugly workaround
namespace {
    static chip_driver::BME208Reader *g_BME280Reader = nullptr;
}

using namespace chip_driver;
/*
*
* \brief Function needed in order to use the Bosch API and I2C
*
*/

/*
 * Return control or wait,
 * for a period amount of milliseconds
 */
void delay(uint32_t period) {
    std::this_thread::sleep_for(std::chrono::milliseconds(period));
}

/*
* \brief The parameter dev_id can be used as a variable to store the I2C address of the device
*
*           Data on the bus should be like
*           |------------+---------------------|
*           | I2C action | Data                |
*           |------------+---------------------|
*           | Start      | -                   |
*           | Write      | (reg_addr)          |
*           | Stop       | -                   |
*           | Start      | -                   |
*           | Read       | (reg_data[0])       |
*           | Read       | (....)              |
*           | Read       | (reg_data[len - 1]) |
*           | Stop       | -                   |
*           |------------+---------------------|
*
*   \returns 0 for Success, non-zero for failure
*
*/
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    if (!::g_BME280Reader) {
        LOG_ERROR("No reader class!");
        return -1;
    }
    if(::g_BME280Reader->readFromAddr(&reg_addr, reg_data, len)) {
        return 0;
    }
    LOG_ERROR("Couuld not read!");
    return -1;
}

/*
 * brief\ The parameter dev_id can be used as a variable to store the I2C address of the device
 *
 *          Data on the bus should be like
 *          |------------+---------------------|
 *          | I2C action | Data                |
 *          |------------+---------------------|
 *          | Start      | -                   |
 *          | Write      | (reg_addr)          |
 *          | Write      | (reg_data[0])       |
 *          | Write      | (....)              |
 *          | Write      | (reg_data[len - 1]) |
 *          | Stop       | -                   |
 *          |------------+---------------------|
 *
 * \returns 0 for Success, non-zero for failure
 */
int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    if (!::g_BME280Reader) {
        LOG_ERROR("No reader class!");
        return -1;
    }
    if(::g_BME280Reader->writeToAddr(&reg_addr, reg_data, len)) {
        return 0;
    }
    LOG_ERROR("Couuld not read!");
    return -1;
}

//TODO: Check word length on the raspberry pi
//TODO: Decide wether to use a flotingpoint or not

BME208Reader::BME208Reader(std::string a_FileName, int a_SlaveAddr):ChipReader(a_FileName, a_SlaveAddr) {

    uint8_t res;

    ::g_BME280Reader = this;
    bme280_dev.dev_id = BME280_I2C_ADDR_PRIM;
    bme280_dev.intf = BME280_I2C_INTF;
    bme280_dev.read = user_i2c_read;
    bme280_dev.write = user_i2c_write;
    bme280_dev.delay_ms = delay;

    if(res = bme280_init(&bme280_dev)) {
        LOG_ERROR("Could not INIT reg! code: %u", res);
        throw std::runtime_error("Could not INIT reg!");
    }

    if(res = bme280_soft_reset(&bme280_dev)) {
        LOG_ERROR("Could not write to make soft reset! code: %u", res);
        throw std::runtime_error("Could not write to make soft reset!");
    }
    LOG_DEBUG("Reset done!");

    uint8_t settings_sel;

    bme280_dev.settings.osr_h = BME280_OVERSAMPLING_1X;
    bme280_dev.settings.osr_p = BME280_OVERSAMPLING_16X;
    bme280_dev.settings.osr_t = BME280_OVERSAMPLING_2X;
    bme280_dev.settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    if (bme280_set_sensor_settings(settings_sel, &bme280_dev)) {
        LOG_ERROR("Couldn't set sensor settings!");
        throw std::runtime_error("Couldn't set sensor settings!");
    }
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

bool BME208Reader::measure() {

    if (bme280_set_sensor_mode(BME280_FORCED_MODE, &bme280_dev)) {
        LOG_ERROR("Couldn't set sensor operation mode!");
        return false;
    }

    /* Wait for the measurement to complete and print data @25Hz */
    bme280_dev.delay_ms(40);
    if (bme280_get_sensor_data(BME280_ALL, &rawData, &bme280_dev)) {
        LOG_ERROR("Couldn't performe measuring!");
        return false;
    }
    return true;
}

double BME208Reader::extractTemperature() const {
    // unit are degerees C
    return rawData.temperature / 100.0;
}

double BME208Reader::extractHumidity() const {
    // unit are % of relative humidity
    return rawData.humidity / 1024.0;
}

double BME208Reader::extractPresure() const {
    // unit are Pa
    return rawData.pressure;
}
