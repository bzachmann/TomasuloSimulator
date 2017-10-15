#include "rfratrecord.h"

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
