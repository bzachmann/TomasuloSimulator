#ifndef INSTRUCTIONQUEUE_H
#define INSTRUCTIONQUEUE_H

#include "fifo.h"
#include "instructionrecord.h"

#define IQ_SIZE     (10)

typedef Fifo<InstructionRecord, IQ_SIZE> InstructionQueueFifo;

class InstructionQueue: public InstructionQueueFifo
{
public:
    InstructionQueue() : InstructionQueueFifo() {}

    void print();
    void reset();
};

#endif // INSTRUCTIONQUEUE_H
