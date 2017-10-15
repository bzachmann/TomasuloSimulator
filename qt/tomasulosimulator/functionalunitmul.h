#ifndef FUNCTIONALUNITMUL_H
#define FUNCTIONALUNITMUL_H

#include "functionalunit.h"

class FunctionalUnitMul : public FunctionalUnit
{
public:
    FunctionalUnitMul():
        FunctionalUnit(),
        requiredCycles(0xFFFF){}

    bool add(ReservationStationRecord record);
    void step() override;

private:
    uint16_t requiredCycles;
};

#endif // FUNCTIONALUNITMUL_H
