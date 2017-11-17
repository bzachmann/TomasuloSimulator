#include "rfratrecord.h"
#include <iomanip>
#include <iostream>


int32_t RfRatRecord::getRfValue() const
{
    return rfValue;
}

void RfRatRecord::setRfValue(const int32_t &value)
{
    rfValue = value;
}

RobRecord::robtag_t RfRatRecord::getRatTag() const
{
    return ratTag;
}

void RfRatRecord::setRatTag(const RobRecord::robtag_t &value)
{
    ratTag = value;
}

void RfRatRecord::print()
{
#warning todo - fix printing
    std::cout << std::right << std::setw(PRINT_WIDTH_RF) << std::setfill(' ') << rfValue;
    std::cout << std::right << std::setw(PRINT_WIDTH_RAT) << std::setfill(' ') << RobRecord::tagToString(ratTag);
}
