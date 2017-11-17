#ifndef REGISTERFILEREGISTERALLOCATIONTABLE_H
#define REGISTERFILEREGISTERALLOCATIONTABLE_H

#include "betterarray.h"
#include "rfratrecord.h"

#define RF_SIZE     (8)

typedef BetterArray<RF_SIZE> RegisterFileArray;

class RegisterFileRegisterAllocationTable
{
public:
    RegisterFileRegisterAllocationTable():
        rfRatRecords(){}
    void init(RegisterFileArray initialRf);
    void commit(uint16_t destIndex, RobRecord::robtag_t tag, int32_t value);
    void tag(uint8_t index, RobRecord::robtag_t tag);
    void getSource(uint16_t index, RobRecord::robtag_t &tag, int32_t &value);
    void print();

private:
    RfRatRecord rfRatRecords[RF_SIZE];
};

#endif // REGISTERFILEREGISTERALLOCATIONTABLE_H
