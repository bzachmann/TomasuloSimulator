#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "fifo.h"
#include "instructionrecord.h"
#include "betterarray.h"
#include "reservationstationaddsub.h"
#include "reservationstationmuldiv.h"
#include "functionalunitadd.h"
#include "functionalunitmul.h"
#include "registerfileregisterallocationtable.h"

#define IQ_SIZE     (10)

typedef Fifo<InstructionRecord, IQ_SIZE> InstructionQueue;

class Processor
{
public:
    Processor() :
        IQ(),
        RFRAT(),
        RSAddSub(),
        RSMulDiv(),
        FUAdd(),
        FUMul(){}

    void init(InstructionQueue iq, RegisterFileArray rf);
    void step();

private:
    InstructionQueue IQ;
    RegisterFileRegisterAllocationTable RFRAT;
    ReservationStationAddSub RSAddSub;
    ReservationStationMulDiv RSMulDiv;
    FunctionalUnitAdd FUAdd;
    FunctionalUnitMul FUMul;


};

#endif // PROCESSOR_H
