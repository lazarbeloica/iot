
CC=g++
CPP_FLAGS=-std=c++11
CURL_LIBS=-D_GLIBCXX_USE_CXX11_ABI=0 -lm -lcurl -lcurlpp

pi_app: httprequest_generator.o piman.o main.o
	$(CC) $(CPP_FLAGS) $^ $(CURL_LIBS) -o $@

main.o: main.cpp httprequest_generator.hh
	$(CC) $(CPP_FLAGS) -c main.cpp

piman.o: piman.cpp piman.hh debug.hh
	$(CC) $(CPP_FLAGS) -c piman.cpp $(CURL_LIBS)

httprequest_generator.o: httprequest_generator.cpp httprequest_generator.hh debug.hh
	$(CC) $(CPP_FLAGS) -c httprequest_generator.cpp $(CURL_LIBS)


.PHONY: clean

clean:
	echo "Cleaning..."
	rm *.o pi_app
	echo "Done cleaning."

run:
	./pi_app