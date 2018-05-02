#ifndef _PIMAN_HH_
#define _PIMAN_HH_

/**
 * Piman - Pi Manager
 * Singleton
 * Handels sending measured data to the server
*/

#include "../network/httprequest_generator.hh"
#include "../debug.hh"

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
    void run();

    void setTimeout(const uint32_t& a_Count);
    uint32_t getTimeout();

    void setServerURL(std::string a_Url);
    std::string getServerURL() const;

private:
    Piman():m_Timeout(DEFAULT_TIMEOUT),
            m_HttpReqGen(nullptr),
            m_BackoffFactor(START_BACKOFF_FACTOR),
            m_ThreadOn(false)
            {};

    void sendValueToServer(std::string a_Value);
    void calculateBackoff();
    void resetBackoff();

    uint32_t calculateTimeout();
    int8_t m_BackoffFactor;
    bool m_ThreadOn;

    static Piman *m_Instance;
    uint32_t m_Timeout;
    HTTPRequestGenerator *m_HttpReqGen;
};

}

#endif //_PIMAN_HH_