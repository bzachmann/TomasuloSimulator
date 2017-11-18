#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "instructionrecord.h"
#include "betterarray.h"
#include "reservationstationaddsub.h"
#include "reservationstationmuldiv.h"
#include "functionalunitadd.h"
#include "functionalunitmul.h"
#include "registerfileregisterallocationtable.h"
#include "instructionqueue.h"
#include "reorderbuffer.h"

class Processor
{
public:
    Processor() :
        IQ(),
        RFRAT(),
        ROB(),
        RSAddSub(),
        RSMulDiv(),
        FUAdd(),
        FUMul(){}

    void init(InstructionQueue iq, RegisterFileArray rf);
    bool step();
    void reset();
    void print();

private:
    InstructionQueue IQ;
    RegisterFileRegisterAllocationTable RFRAT;
    ReOrderBuffer ROB;
    ReservationStationAddSub RSAddSub;
    ReservationStationMulDiv RSMulDiv;
    FunctionalUnitAdd FUAdd;
    FunctionalUnitMul FUMul;
};

#endif // PROCESSOR_H
