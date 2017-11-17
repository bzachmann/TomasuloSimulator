#ifndef RESERVATIONSTATIONMULDIV_H
#define RESERVATIONSTATIONMULDIV_H

#include "reservationstationrecord.h"

#define NUM_RS_MUL_DIV_RECORDS          (2)

class ReservationStationMulDiv
{
public:
    ReservationStationMulDiv();

    void step();
    bool notFull();
    bool issue(ReservationStationRecord record);
    void capture(RobRecord::robtag_t tag, int32_t value);
    bool dispatch(ReservationStationRecord &record);

    void print();

private:
    ReservationStationRecord rsrecords[NUM_RS_MUL_DIV_RECORDS];
};

#endif // RESERVATIONSTATIONMULDIV_H
