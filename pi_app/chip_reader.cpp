#include "chip_reader.hh"
#include <stdexcept>

const int ChipReader::ADR_LEN = 1;

bool ChipReader::writeI2C(const unsigned char* a_Buffer, const int a_Bytes) const {

    if(!a_Bytes)
        return true;

    if(a_Buffer == nullptr)
        return false;

    int res = write(m_File_i2c, a_Buffer, a_Bytes);
    if (res != a_Bytes)
	{
		LOG_ERROR("Failed to write to the i2c bus. Error code: %d", res);
        return false;
    }

    return true;
}

bool ChipReader::readI2C(unsigned char* a_Buffer, const int a_Bytes) const {

    if(!a_Bytes)
        return true;

    if(a_Buffer == nullptr)
        return false;

    int res = read(m_File_i2c, a_Buffer, a_Bytes);
    if (res != a_Bytes)
	{
		LOG_ERROR("Failed to read from the i2c bus. Error code: %d", res);
        return false;
    }

    return true;
}

bool ChipReader::writeToAddr(const unsigned char* a_Adr, const unsigned char* a_Buffer, int a_Bytes) const {

    if(!a_Bytes)
        return true;

    if(a_Buffer == nullptr || a_Adr == nullptr)
        return false;

    unsigned char toWrite[a_Bytes + 1];
    toWrite[0] = *a_Adr;
    std::memcpy(&toWrite[1], a_Buffer, a_Bytes);
    for(int i = 0; i < a_Bytes + 1; ++i){
        LOG_DEBUG("%d. %u\n", i, toWrite[i]);
    }

    if (!writeI2C(toWrite, ADR_LEN + 1)) {
        LOG_ERROR("Not able to write to the chip");
        return false;
    }

    return true;
}

bool ChipReader::readFromAddr(const unsigned char* a_Adr, unsigned char* a_Buffer, int a_Bytes) const {

    if(!a_Bytes)
        return true;

    if(a_Buffer == nullptr || a_Adr == nullptr)
        return false;

    if (!writeI2C(a_Adr, ADR_LEN)) {
        LOG_ERROR("Not able to write to the chip");
        return false;
    }

	if (!readI2C(a_Buffer, a_Bytes)) {
        LOG_ERROR("Not able to read from the chip");
        return false;
    }
    return true;
}

ChipReader::ChipReader(std::string a_FileName, int a_SlaveAddr): m_SlaveAddr(a_SlaveAddr) {

    if ((m_File_i2c = open(a_FileName.c_str(), O_RDWR)) < 0)
	{
		LOG_ERROR("Failed to open the i2c bus\n");
		throw std::runtime_error("Failed to open the i2c bus. open error code: " + a_FileName);
	}

    int res = ioctl(m_File_i2c, I2C_SLAVE, m_SlaveAddr);
    if ( res < 0)
	{
		LOG_ERROR("Failed to acquire bus access and/or talk to slave.\n");
		throw std::runtime_error("Failed to acquire bus access and/or talk to slave. ioctrl error code: " + res);
	}
}