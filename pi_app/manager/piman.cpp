#include "piman.hh"
#include "../chip_driver/chip_reader.hh"
#include "../chip_driver/bme280_reader.hh"
#include <thread>

namespace piman {

const int MAX_CHIP_ERRORS = 10;

Piman::~Piman()
{
    stop();
}

void Piman::setTimeout(const uint32_t& a_Count)
{
    m_Timeout = a_Count;
}

uint32_t Piman::getTimeout()
{
    return m_Timeout;
}

void Piman::setServerURL(std::string a_Url)
{
    if(m_HttpReqGen) {
        m_HttpReqGen->setUrl(a_Url);
    }
}

std::string Piman::getServerURL() const
{
    if(m_HttpReqGen) {
        return m_HttpReqGen->getUrl();
    }

    return "";
}

void Piman::setChipReader(std::shared_ptr<chip_driver::ChipReader> a_ChipReader)
{
    m_ChipReader = a_ChipReader;
}

std::shared_ptr<chip_driver::ChipReader> Piman::getChipReader() const
{
    return  m_ChipReader;
}

void Piman::calculateBackoff()
{
    if (m_BackoffFactor > MAX_BACKOFF_FACTOR) {
        LOG_WARNING("Piman: Server is unavailable. Killing the run thread.");
        m_BackoffFactor = START_BACKOFF_FACTOR;
        m_ThreadOn = false;
    }
    LOG_DEBUG("Piman: Calculating backoff.");
    m_BackoffFactor *= BACKOFF_FACTOR_MUL;
}

void Piman::resetBackoff()
{
    m_BackoffFactor = START_BACKOFF_FACTOR;
}

uint32_t Piman::calculateTimeout()
{
    return m_Timeout * m_BackoffFactor;
}

void Piman::sendValueToServer(std::string a_Value)
{
    LOG_DEBUG("Piman: Sending value %s to the Server.", a_Value.c_str());
    if (m_HttpReqGen->sendRequest(a_Value) < 0) {
        calculateBackoff();
    }
    else {
        resetBackoff();
    }

}

bool Piman::start()
{
    if(!m_HttpReqGen) {
        LOG_ERROR("No request generator specified! Thread not started.");
        return false;
    }

    if(!m_ChipReader) {
        LOG_ERROR("No chip reader specified! Thread not started.");
        return false;
    }

    m_Thread = std::thread(&Piman::body, this);
    return true;
}

void Piman::body()
{
    m_ThreadOn = true;
    int chipError = 0;

    while(m_ThreadOn) {
        if (m_ChipReader && m_HttpReqGen) {
            if (m_ChipReader->measure()) {
                std::string value = std::to_string(m_ChipReader->extractTemperature());
                sendValueToServer(value);
                chipError = 0;
            }
            else {
                //chip error
                chipError++;
                if (chipError > MAX_CHIP_ERRORS) {
                    shutdown();
                }
            }
        }
        LOG_DEBUG("Piman: Going to sleep for %d ms.", calculateTimeout());
        std::this_thread::sleep_for(std::chrono::milliseconds(m_Timeout));
    }
    LOG_DEBUG("Thread done");
}

void Piman::stop()
{
    m_ThreadOn = false;
    m_Thread.join();
}

void Piman::shutdown()
{
    LOG_ERROR("FATAL: Couln't revover from error! Shutdown initated!");
    stop();
}

} // namespace piman