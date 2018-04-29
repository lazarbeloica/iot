#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <string>
#include <cstring>
#include "debug.hh"

class ChipReader
{
private:
    static const int ADR_LEN;   //address lenth in bytes

    int m_SlaveAddr;
    int m_File_i2c;

protected:
    bool writeI2C(const unsigned char* a_Buffer, const int a_Bytes) const;
    bool readI2C(unsigned char* a_Buffer, const int a_Bytes) const;

public:
    bool writeToAddr(const unsigned char* a_Adr, const unsigned char* a_Buffer, int a_Bytes = 1) const;
    bool readFromAddr(const unsigned char* a_Adr, unsigned char* a_Buffer, int a_Bytes = 1) const;

    ChipReader(std::string a_FileName, int a_SlaveAddr);
    virtual ~ChipReader() {};

    virtual bool testConnection() const = 0;
    virtual bool measure() = 0;
    virtual int extractTemperature() const = 0;
    virtual int extractHumidity() const = 0;
    virtual int extractPresure() const = 0;
};