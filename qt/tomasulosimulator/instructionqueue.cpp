#include "instructionqueue.h"
#include <iostream>

void InstructionQueue::print()
{
    InstructionRecord iqArray[IQ_SIZE];
    InstructionQueue queueCopy = *this;

    for(int16_t i = (IQ_SIZE - 1); i >= 0; i--)
    {
        InstructionRecord record;
        if(queueCopy.get(record))
        {
            iqArray[i] = record;
        }
        else
        {
            record.setOpcode(InstructionRecord::OPCODE_UNDEF);
            iqArray[i] = record;
        }
    }

    std::cout << "Instruction Queue" << std::endl;
    for(uint8_t i = 0; i < IQ_SIZE; i++)
    {
        iqArray[i].print();
        std::cout << std::endl;
    }
}
