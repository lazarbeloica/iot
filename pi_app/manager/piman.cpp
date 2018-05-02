#include "piman.hh"

namespace piman{

Piman *Piman::m_Instance = nullptr;

Piman *Piman::getInstance()
{
    if (!m_Instance) {
        m_Instance = new (std::nothrow) Piman();
        m_Instance->m_HttpReqGen = new HTTPRequestGenerator(piman::DEVICE_ID, piman::DEFAULT_URL);
    }

    return m_Instance;
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

void Piman::run()
{
    m_ThreadOn = true;
    std::string test_value = "23.5";
    while(m_ThreadOn) {
        sendValueToServer(test_value);
        LOG_DEBUG("Piman: Going to sleep for %d ms.", calculateTimeout());
        std::this_thread::sleep_for(std::chrono::milliseconds(m_Timeout));
    }
}

}