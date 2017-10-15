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
    void capture(ReservationStationRecord::rsrtag_t tag, int32_t value);
    void tag(uint8_t index, ReservationStationRecord::rsrtag_t tag);

private:
    RfRatRecord rfRatRecords[RF_SIZE];
};

#endif // REGISTERFILEREGISTERALLOCATIONTABLE_H
