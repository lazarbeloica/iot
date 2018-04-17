import smbus
import time
DEVICE_BUS = 1
DEVICE_ADDR = 0x76
bus = smbus.SMBus(DEVICE_BUS)

print "Test started"

for x in range (0, 100):
	print "ctr old state:"
	bus.write_byte(DEVICE_ADDR, 0xF4)
	bus.read_byte(DEVICE_ADDR)
	bus.write_byte_data(DEVICE_ADDR, 0xF4,0b00100110)
	print "ctrl new state:"
	bus.write_byte(DEVICE_ADDR, 0xF4)
	bus.read_byte(DEVICE_ADDR)
	print "measured:"
	bus.write_byte(DEVICE_ADDR, 0xFA)
	bus.read_byte(DEVICE_ADDR)
	#bus.write_byte(DEVICE_ADDR, 0xFB)
	bus.read_byte(DEVICE_ADDR)
	#bus.write_byte(DEVICE_ADDR, 0xFC)
	bus.read_byte(DEVICE_ADDR)
	print "sleeping"
	time.sleep(1)

