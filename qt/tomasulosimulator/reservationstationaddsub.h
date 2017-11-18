#ifndef RESERVATIONSTATIONADDSUB_H
#define RESERVATIONSTATIONADDSUB_H

#include "reservationstationrecord.h"

#define NUM_RS_ADD_SUB_RECORDS          (3)

class ReservationStationAddSub
{
public:
    ReservationStationAddSub();

    void step();
    bool notFull();
    bool issue(ReservationStationRecord record);
    void capture(RobRecord::robtag_t tag, int32_t value);
    bool dispatch(ReservationStationRecord &record);
    void reset();
    void print();

private:
    ReservationStationRecord rsrecords[NUM_RS_ADD_SUB_RECORDS];

};

#endif // RESERVATIONSTATIONADDSUB_H
