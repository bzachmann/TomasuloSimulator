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

ReservationStationRecord::rsrtag_t RfRatRecord::getRatTag() const
{
    return ratTag;
}

void RfRatRecord::setRatTag(const ReservationStationRecord::rsrtag_t &value)
{
    ratTag = value;
}

void RfRatRecord::print()
{
    std::cout << std::right << std::setw(PRINT_WIDTH_RF) << std::setfill(' ') << rfValue;
    std::cout << std::right << std::setw(PRINT_WIDTH_RAT) << std::setfill(' ') << ReservationStationRecord::tagToString(ratTag);
}
