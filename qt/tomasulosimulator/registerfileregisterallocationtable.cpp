#include "registerfileregisterallocationtable.h"
#include <iostream>
#include <iomanip>

#define PRINT_WIDTH_RFRAT_INDEX     (4)

void RegisterFileRegisterAllocationTable::init(RegisterFileArray initialRf)
{
    int32_t tempValue = 0;
    for(uint16_t i = 0; i < RF_SIZE; i++)
    {
        if(initialRf.getValue(i, tempValue))
        {
            rfRatRecords[i].setRfValue(tempValue);
        }
        rfRatRecords[i].setRatTag(ReservationStationRecord::TAG_UNDEF);
    }
}

void RegisterFileRegisterAllocationTable::capture(ReservationStationRecord::rsrtag_t tag, int32_t value)
{
    for(uint16_t i = 0; i < RF_SIZE; i++)
    {
        if(rfRatRecords[i].getRatTag() == tag)
        {
            rfRatRecords[i].setRfValue(value);
            rfRatRecords[i].setRatTag(ReservationStationRecord::TAG_UNDEF);
        }
    }
}

void RegisterFileRegisterAllocationTable::tag(uint16_t index, ReservationStationRecord::rsrtag_t tag)
{
    if(index < RF_SIZE)
    {
        rfRatRecords[index].setRatTag(tag);
    }
}

void RegisterFileRegisterAllocationTable::getSource(uint16_t index, ReservationStationRecord::rsrtag_t &tag, int32_t &value)
{
    if(index < RF_SIZE)
    {
        tag = rfRatRecords[index].getRatTag();
        if(tag == ReservationStationRecord::TAG_UNDEF)
        {
            value = rfRatRecords[index].getRfValue();
        }
        else
        {
            value = 0;
        }

    }
}

void RegisterFileRegisterAllocationTable::print()
{
    std::cout << "Register File / Register Allocation Table" << std::endl;
    std::cout << std::right << std::setw(PRINT_WIDTH_RFRAT_INDEX) << std::setfill(' ') << " " << ' ';
    std::cout << std::right << std::setw(PRINT_WIDTH_RF) << std::setfill(' ') << "RF";
    std::cout << std::right << std::setw(PRINT_WIDTH_RAT) << std::setfill(' ') << "RAT" << std::endl;

    for(uint16_t i = 0; i < RF_SIZE; i++)
    {
        std::cout << std::right << std::setw(PRINT_WIDTH_RFRAT_INDEX) << std::setfill(' ') << i << ':';
        rfRatRecords[i].print();
        std::cout << std::endl;
    }
}
