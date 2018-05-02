#ifndef _PIMAN_HH_
#define _PIMAN_HH_

/**
 * Piman - Pi Manager
 * Singleton
 * Handels sending measured data to the server
*/

#include "../network/httprequest_generator.hh"
#include "../debug.hh"
#include "../chip_driver/chip_reader.hh"

#include <iostream>
#include <stdint.h>
#include <string>
#include <chrono>
#include <thread>

namespace piman {

using namespace net;

const std::string TEST_URL_LOCAL = "http://localhost:3000/measurements";
const std::string DEFAULT_URL = "http://checkmytemp.fr.openode.io/measurements";
const std::string DEVICE_ID = "devTest0";
const uint32_t DEFAULT_TIMEOUT = 6000; //60s
const int8_t MAX_BACKOFF_FACTOR = 8;
const int8_t START_BACKOFF_FACTOR = 1;
const int8_t BACKOFF_FACTOR_MUL = 2;


class Piman {
public:
    Piman(Piman const&) = delete;
    void operator=(Piman const&) = delete;

    static Piman *getInstance();
    bool start();
    void stop();

    void setTimeout(const uint32_t& a_Count);
    uint32_t getTimeout();

    void setServerURL(std::string a_Url);
    std::string getServerURL() const;

    void setChipReader(chip_driver::ChipReader*);
    chip_driver::ChipReader* getChipReader() const;

private:
    Piman(chip_driver::ChipReader *a_ChipReader = nullptr) :
            m_Timeout(DEFAULT_TIMEOUT),
            m_HttpReqGen(nullptr),
            m_BackoffFactor(START_BACKOFF_FACTOR),
            m_ThreadOn(false),
            m_ChipReader(a_ChipReader)
            {};

    ~Piman();

    void body();
    void sendValueToServer(std::string a_Value);
    void calculateBackoff();
    void resetBackoff();
    static void shutdown();

    uint32_t calculateTimeout();
    int8_t m_BackoffFactor;
    bool m_ThreadOn;
    std::thread m_Thread;
    uint32_t m_Timeout;

    HTTPRequestGenerator *m_HttpReqGen;
    chip_driver::ChipReader *m_ChipReader;

    static Piman *m_Instance;
};

}

#endif //_PIMAN_HH_