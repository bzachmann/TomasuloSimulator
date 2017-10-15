#ifndef RFRATRECORD_H
#define RFRATRECORD_H

#include "reservationstationrecord.h"

class RfRatRecord
{
public:
    RfRatRecord() :
        rfValue(0),
        ratTag(ReservationStationRecord::TAG_UNDEF){}

    int32_t getRfValue() const;
    void setRfValue(const int32_t &value);
    ReservationStationRecord::rsrtag_t getRatTag() const;
    void setRatTag(const ReservationStationRecord::rsrtag_t &value);

private:
    int32_t rfValue;
    ReservationStationRecord::rsrtag_t ratTag;
};

#endif // RFRATRECORD_H
