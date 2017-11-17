#ifndef RFRATRECORD_H
#define RFRATRECORD_H

#include "reservationstationrecord.h"

#define PRINT_WIDTH_RF      (12)
#define PRINT_WIDTH_RAT     (12)

class RfRatRecord
{
public:
    RfRatRecord() :
        rfValue(0),
        ratTag(RobRecord::TAG_ROB_UNDEF){}

    int32_t getRfValue() const;
    void setRfValue(const int32_t &value);
    RobRecord::robtag_t getRatTag() const;
    void setRatTag(const RobRecord::robtag_t &value);
    void print();

private:
    int32_t rfValue;
    RobRecord::robtag_t ratTag;
};

#endif // RFRATRECORD_H
