#include "instructionrecord.h"

InstructionRecord::opcode_t InstructionRecord::getOpcode() const
{
    return opcode;
}

void InstructionRecord::setOpcode(const opcode_t &value)
{
    opcode = value;
}

uint8_t InstructionRecord::getDestination() const
{
    return destination;
}

void InstructionRecord::setDestination(const uint8_t &value)
{
    destination = value;
}

uint8_t InstructionRecord::getSource1() const
{
    return source1;
}

void InstructionRecord::setSource1(const uint8_t &value)
{
    source1 = value;
}

uint8_t InstructionRecord::getSource2() const
{
    return source2;
}

void InstructionRecord::setSource2(const uint8_t &value)
{
    source2 = value;
}
