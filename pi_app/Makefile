
CC=g++
CPP_FLAGS=-std=c++11 -g
CURL_LIBS=-D_GLIBCXX_USE_CXX11_ABI=0 -lm -lcurl -lcurlpp

pi_app: httprequest_generator.o piman.o main.o bme280_reader.o chip_reader.o
	$(CC) $(CPP_FLAGS) $^ $(CURL_LIBS) -o $@

chip_test: chip_reader.o bme280_reader.o chip_test.cpp bme280_driver.o
	$(CC) $(CPP_FLAGS) $^ -o $@

main.o: main.cpp httprequest_generator.hh
	$(CC) $(CPP_FLAGS) -c main.cpp

piman.o: piman.cpp piman.hh debug.hh
	$(CC) $(CPP_FLAGS) -c piman.cpp $(CURL_LIBS)

httprequest_generator.o: httprequest_generator.cpp httprequest_generator.hh debug.hh
	$(CC) $(CPP_FLAGS) -c httprequest_generator.cpp $(CURL_LIBS)

bme280_reader.o: bme280_reader.cpp bme280_reader.hh chip_reader.o bme280_driver.o
	$(CC) $(CPP_FLAGS) -c bme280_reader.cpp bme280_driver.o

bme280_driver.o: BME280_driver/bme280.c
	$(CC) $(CPP_FLAGS) -c BME280_driver/bme280.c -o $@

chip_reader.o: chip_reader.cpp chip_reader.hh
	$(CC) $(CPP_FLAGS) -c chip_reader.cpp

.PHONY: clean
.SILENT: clean
clean:
	echo "Cleaning..."
	rm *.o pi_app 2>/dev/null || :
	echo "Done cleaning."
.PHONY: run
run: pi_app
	./pi_app

.PHONY: test
test: chip_test
	./chip_test