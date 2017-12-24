#include "httprequest_generator.hh"

namespace net {

std::string HTTPRequestGenerator::getDevID()
{
	return m_DevId;
}

void HTTPRequestGenerator::setContentType(std::string contType)
{
	m_ContentType = CONTENT_TYPE_BASE + contType;
}

std::string HTTPRequestGenerator::getContentType()
{
	return m_ContentType.substr(CONTENT_TYPE_BASE.size() + 1);
}

void HTTPRequestGenerator::setUrl(std::string url)
{
	m_Url = url;
}

std::string HTTPRequestGenerator::getUrl()
{
	return m_Url;
}

int HTTPRequestGenerator::sendRequest(std::string value)
{
	LOG_DEBUG("HTTPRequestGenerator: sendRequest invoked...");
	try {
	    curlpp::Cleanup cleaner;
	    curlpp::Easy request;

	    request.setOpt(new curlpp::options::Url(m_Url));
	    request.setOpt(new curlpp::options::Verbose(true));

	    std::list<std::string> header;
	    header.push_back(m_ContentType);

	    request.setOpt(new curlpp::options::HttpHeader(header));

		std::string req = "devId=" + m_DevId + "&value=" + value;
	    request.setOpt(new curlpp::options::PostFields(req));
	    request.setOpt(new curlpp::options::PostFieldSize(req.size()));

	    request.perform();
			LOG_DEBUG("HTTPRequestGenerator: sendRequest sucessfull.");
	  }
	  catch ( curlpp::LogicError & e ) {
			LOG_DEBUG("HTTPRequestGenerator: sendRequest failed (logical error).");
	    std::cout << e.what() << std::endl;
		return HTTP_GEN_LOGICAL_ERROR;
	  }
	  catch ( curlpp::RuntimeError & e ) {
			LOG_DEBUG("HTTPRequestGenerator: sendRequest failed (runtime error).");
	    std::cout << e.what() << std::endl;
		return HTTP_GEN_RUNTIME_ERROR;
	  }

	return HTTP_GEN_SUCCESS;
}

}