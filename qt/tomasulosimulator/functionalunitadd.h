#ifndef FUNCTIONALUNITADD_H
#define FUNCTIONALUNITADD_H

#include "functionalunit.h"

class FunctionalUnitAdd : public FunctionalUnit
{
public:
    FunctionalUnitAdd() :
        FunctionalUnit(),
        requiredCycles(0xFFFF){}

    bool add(ReservationStationRecord record);
    void step() override;

private:
    uint16_t requiredCycles;
};

#endif // FUNCTIONALUNITADD_H
