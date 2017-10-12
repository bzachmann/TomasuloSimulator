#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "fifo.h"
#include "instructionrecord.h"
#include "betterarray.h"

#define IQ_SIZE     (10)
#define RF_SIZE     (8)

typedef Fifo<InstructionRecord, IQ_SIZE> InstructionQueue;
typedef BetterArray<RF_SIZE> RegisterFile;

class Processor
{
public:
    Processor() :
        IQ(),
        RF() {}
    void init(InstructionQueue iq, RegisterFile rf);
    void step();

private:
    InstructionQueue IQ;
    RegisterFile RF;

};

#endif // PROCESSOR_H
