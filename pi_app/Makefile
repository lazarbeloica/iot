
CC=g++
CPP_FLAGS=-std=c++11
CURL_LIBS=-D_GLIBCXX_USE_CXX11_ABI=0 -lm -lcurl -lcurlpp 

pi_app: main.o httprequest_generator.o
	$(CC) $(CPP_FLAGS) $^ $(CURL_LIBS) -o $@

main.o: main.cpp
	$(CC) $(CPP_FLAGS) -c $<

httprequest_generator.o: httprequest_generator.cpp httprequest_generator.hh 
	$(CC) $(CPP_FLAGS) -c $< $(CURL_LIBS) 


.PHONY: clean

clean:
	echo "Cleaning..."
	rm *.o pi_app
	echo "Done cleaning."

run:
	./pi_app