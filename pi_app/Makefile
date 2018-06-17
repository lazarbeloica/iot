
CC=g++
CPP_FLAGS=-std=c++11 -g
#############################################################
# NOTE: -D_GLIBCXX_USE_CXX11_ABI=0 needs to be removed when
#		 		running this on a raspberry pi
#############################################################
LIBS=-lm -lcurl -lcurlpp -lpthread

pi_app: httprequest_generator.o chip_reader.o bme280_reader.o bme280_driver.o piman.o cmd_client.o chip_reader_factory.o manager.o chip_driver_models.o main.o
	$(CC) $(CPP_FLAGS) $^ -o $@ $(LIBS)

chip_test: chip_reader.o bme280_reader.o test/chip_test.cpp bme280_driver.o
	$(CC) $(CPP_FLAGS) $^ -o $@ $(LIBS)

main.o: main.cpp network/httprequest_generator.hh
	$(CC) $(CPP_FLAGS) -c main.cpp -o $@ $(LIBS)

cmd_client.o: cmd_client/cmd_client.cpp cmd_client/cmd_client.hh debug.hh
	$(CC) $(CPP_FLAGS) -c cmd_client/cmd_client.cpp -o $@ $(LIBS)

manager.o: manager/manager.cpp manager/manager.hh debug.hh
	$(CC) $(CPP_FLAGS) -c manager/manager.cpp -o $@ $(LIBS)

piman.o: manager/piman.cpp manager/piman.hh debug.hh
	$(CC) $(CPP_FLAGS) -c manager/piman.cpp -o $@ $(LIBS)

httprequest_generator.o: network/httprequest_generator.cpp network/httprequest_generator.hh debug.hh
	$(CC) $(CPP_FLAGS) -c network/httprequest_generator.cpp -o $@ $(LIBS)

bme280_reader.o: chip_driver/bme280_reader.cpp chip_driver/bme280_reader.hh chip_reader.o bme280_driver.o
	$(CC) $(CPP_FLAGS) -c chip_driver/bme280_reader.cpp -o $@ $(LIBS)

bme280_driver.o: chip_driver/BME280_driver/bme280.c
	$(CC) $(CPP_FLAGS) -c chip_driver/BME280_driver/bme280.c -o $@ $(LIBS)

chip_driver_models.o: chip_driver/chip_driver_models.cpp chip_driver/chip_driver_models.hh
	$(CC) $(CPP_FLAGS) -c chip_driver/chip_driver_models.cpp -o $@ $(LIBS)

chip_reader_factory.o: chip_driver/chip_reader_factory.cpp chip_driver/chip_reader_factory.hh
	$(CC) $(CPP_FLAGS) -c chip_driver/chip_reader_factory.cpp -o $@ $(LIBS)

chip_reader.o: chip_driver/chip_reader.cpp chip_driver/chip_reader.hh
	$(CC) $(CPP_FLAGS) -c chip_driver/chip_reader.cpp -o $@ $(LIBS)

.PHONY: clean
.SILENT: clean
clean:
	echo "Cleaning..."
	rm *.o pi_app 2>/dev/null || :
	echo "Done cleaning."
.PHONY: run
run: pi_app
	./pi_app

.PHONY: install
install: pi_app
	cp scripts/piapponboot.sh /etc/init.d/	#requires super-user prem

.PHONY: test
test: chip_test
	./chip_test