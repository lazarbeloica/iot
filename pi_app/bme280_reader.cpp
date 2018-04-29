#include "bme280_reader.hh"
#include <iostream>
#include "chip_reader.hh"

#include  <functional>
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std::placeholders;

//used for an ugly workaround
namespace {
    static BME208Reader *g_BME280Reader = nullptr;
}
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
    usleep(period);
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
        LOG_DEBUG("=======================");
        LOG_DEBUG("Writing %d bytes to %02x", len, reg_addr);
        for (int i = 0; i < len; ++i) {
            LOG_DEBUG("%2x", reg_data[i]);
        }
        LOG_DEBUG("=======================");
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
        LOG_DEBUG("=======================");
        LOG_DEBUG("Writing %d bytes to %02x", len, reg_addr);
        for (int i = 0; i < len; ++i) {
            LOG_DEBUG("%2x", reg_data[i]);
        }
        LOG_DEBUG("=======================");
        return 0;
    }
    LOG_ERROR("Couuld not read!");
    return -1;
}


BME208Reader::BME208Reader(std::string a_FileName, int a_SlaveAddr):ChipReader(a_FileName, a_SlaveAddr) {

    uint8_t res;

    ::g_BME280Reader = this;
    bme280_dev.dev_id = BME280_I2C_ADDR_PRIM;
    bme280_dev.intf = BME280_I2C_INTF;
    bme280_dev.read = user_i2c_read;
    bme280_dev.write = user_i2c_write;
    bme280_dev.delay_ms = delay;
    bme280_settings settings;
    settings.osr_p = 0;
    settings.osr_t = 0;
    settings.osr_h = 0;
    settings.filter = 0;
    settings.standby_time = 0;
    bme280_dev.settings = settings;

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

    int res;
    res = bme280_set_sensor_settings(BME280_ALL_SETTINGS_SEL, &bme280_dev);
    if (res) {
        LOG_ERROR("Could not write to ctrl reg! err_code: %d", res);
        return false;
    }
    res = bme280_set_sensor_mode(BME280_FORCED_MODE, &bme280_dev);
    if (res) {
        LOG_ERROR("Could not write to mode reg! err_code = %d", res);
        return false;
    }

//    if (!writeToAddr(&ctrl_hum_adr ,&CTRL_HUM)) {
//        LOG_ERROR("Could not write to ctrl_hum reg!");
//        return false;
//    }
//
//    if (!writeToAddr(&ctrl_hum_adr ,&CTRL_HUM)) {
//        LOG_ERROR("Could not write to ctrl_hum reg!");
//        return false;
//    }
//
//    if (!writeToAddr(&ctrl_meas_adr ,&CTRL_MEAS)) {
//        LOG_ERROR("Could not write to ctrl_meas reg!");
//        return false;
//    }
//
    LOG_DEBUG("Configured the measurement");

//    unsigned char status;
//    do {
//        if (!readFromAddr(&status_adr, &status)) {
//            LOG_ERROR("Could not read the status!");
//            return false;
//        }
//        LOG_DEBUG("The status is %u", status);
//    } while(status != STATUS_OK);

//    if (!readFromAddr(&data_start_adr, m_readData, DATA_BYTES_LEN)) {
//        LOG_ERROR("Could not read the measured data!");
//        return false;
//    }
//
//    for(int i = 0; i < 8; printf("%d. %u\n", i, m_readData[i++]));

    if (bme280_get_sensor_data(BME280_ALL, &data, &bme280_dev)) {
        LOG_ERROR("Could not get the data!");
        return false;
    }

    return true;
}

int BME208Reader::extractTemperature() const {
    printf("%ld, %ld, %ld\n", data.temperature, data.pressure, data.humidity);
    return 0;
}

int BME208Reader::extractHumidity() const {
    return 0;
}

int BME208Reader::extractPresure() const {
    return 0;
}
