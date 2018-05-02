
CC=g++
CPP_FLAGS=-std=c++11 -g
LIBS=-D_GLIBCXX_USE_CXX11_ABI=0 -lm -lcurl -lcurlpp -lpthread

pi_app: httprequest_generator.o piman.o main.o chip_reader.o bme280_driver.o bme280_reader.o
	$(CC) $(CPP_FLAGS) $^ $(LIBS) -o $@

chip_test: chip_reader.o bme280_reader.o test/chip_test.cpp bme280_driver.o
	$(CC) $(CPP_FLAGS) $^ -o $@

main.o: main.cpp network/httprequest_generator.hh
	$(CC) $(CPP_FLAGS) -c main.cpp -o $@

piman.o: manager/piman.cpp manager/piman.hh debug.hh
	$(CC) $(CPP_FLAGS) -c manager/piman.cpp -o $@ $(LIBS)

httprequest_generator.o: network/httprequest_generator.cpp network/httprequest_generator.hh debug.hh
	$(CC) $(CPP_FLAGS) -c network/httprequest_generator.cpp -o $@ $(LIBS)

bme280_reader.o: chip_driver/bme280_reader.cpp chip_driver/bme280_reader.hh chip_reader.o bme280_driver.o
	$(CC) $(CPP_FLAGS) -c chip_driver/bme280_reader.cpp -o $@

bme280_driver.o: chip_driver/BME280_driver/bme280.c
	$(CC) $(CPP_FLAGS) -c chip_driver/BME280_driver/bme280.c -o $@

chip_reader.o: chip_driver/chip_reader.cpp chip_driver/chip_reader.hh
	$(CC) $(CPP_FLAGS) -c chip_driver/chip_reader.cpp -o $@

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