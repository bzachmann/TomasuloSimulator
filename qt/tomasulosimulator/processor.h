#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "fifo.h"
#include "instructionrecord.h"

#define IQ_SIZE     (10)

typedef Fifo<InstructionRecord, IQ_SIZE> InstructionQueue;

class Processor
{
public:
    Processor() :
        IQ() {}
    void init(InstructionQueue iq);
    void step();

private:
    InstructionQueue IQ;

};

#endif // PROCESSOR_H
