#include "registerfileregisterallocationtable.h"
#include <iostream>
#include <iomanip>

#define PRINT_WIDTH_RFRAT_INDEX     (4)

void RegisterFileRegisterAllocationTable::init(RegisterFileArray initialRf)
{
    int32_t tempValue = 0;
    for(uint8_t i = 0; i < RF_SIZE; i++)
    {
        if(initialRf.getValue(i, tempValue))
        {
            rfRatRecords[i].setRfValue(tempValue);
        }
        rfRatRecords[i].setRatTag(RobRecord::TAG_ROB_UNDEF);
    }
}

void RegisterFileRegisterAllocationTable::commit(uint16_t destIndex, RobRecord::robtag_t tag, int32_t value)
{
    if(destIndex < RF_SIZE)
    {
        rfRatRecords[destIndex].setRfValue(value);

        if(rfRatRecords[destIndex].getRatTag() == tag)
        {
            rfRatRecords[destIndex].setRatTag(RobRecord::TAG_ROB_UNDEF);
        }
    }
}

void RegisterFileRegisterAllocationTable::tag(uint8_t index, RobRecord::robtag_t tag)
{
    if(index < RF_SIZE)
    {
        rfRatRecords[index].setRatTag(tag);
    }
}

void RegisterFileRegisterAllocationTable::getSource(uint16_t index, RobRecord::robtag_t &tag, int32_t &value)
{
    if(index < RF_SIZE)
    {
        tag = rfRatRecords[index].getRatTag();
        if(tag == RobRecord::TAG_ROB_UNDEF)
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

void RegisterFileRegisterAllocationTable::reset()
{
    for(uint8_t i = 0; i < RF_SIZE; i++)
    {
        rfRatRecords[i].setRatTag(RobRecord::TAG_ROB_UNDEF);
    }
}
