
#ifndef _HTTPREQ_GEN_
#define _HTTPREQ_GEN_

#include "../debug.hh"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <iostream>

namespace net {
using namespace curlpp::options;

const std::string CONTENT_TYPE_BASE = "Content-Type: application/";
const std::string CONTENT_TYPE_URLENC = "x-www-form-urlencoded";
/*
// FORAMTS NOT SUPPORTED
const std::string CONTENT_TYPE_FORM_DATA = "form-data";
const std::string CONTENT_TYPE_RAW = "raw";
const std::string CONTENT_TYPE_BINARY = "binary";
*/
const int HTTP_GEN_SUCCESS = 1;
const int HTTP_GEN_LOGICAL_ERROR = -1;
const int HTTP_GEN_RUNTIME_ERROR = -2;

class HTTPRequestGenerator {
public:

    HTTPRequestGenerator(std::string devID,
                        std::string url,
                        std::string conType = CONTENT_TYPE_URLENC):
                                        m_DevId(devID),
                                        m_Url(url),
                                        m_ContentType(CONTENT_TYPE_BASE + conType) {}

    /*Sends request to the registerd URL with a given value*/
    int sendRequest(std::string value);

    std::string getDevID();

    void setContentType(std::string contType);
    std::string getContentType();

    void setUrl(std::string url);
    std::string getUrl();

private:
    /* Content type of the HTTP POST message */
    std::string m_ContentType;
    /* Server RESTful API */
    std::string m_Url;
    /* ID of the measureing device */
    std::string m_DevId;
};

}
#endif //_HTTPREQ_GEN_