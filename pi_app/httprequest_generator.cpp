

#include "httprequest_generator.hh"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

int HTTPRequestGenerator::run() {
    	try
    	{
    		// That's all that is needed to do cleanup of used resources (RAII style).
    		curlpp::Cleanup myCleanup;

            std::cout << curlpp::options::Url("http://google.com");

    	}

    	catch(curlpp::RuntimeError & e)
    	{
    		std::cout << e.what() << std::endl;
    	}

    	catch(curlpp::LogicError & e)
    	{
    		std::cout << e.what() << std::endl;
    	}

      return 0;
    };