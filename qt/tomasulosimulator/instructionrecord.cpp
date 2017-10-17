#include "instructionrecord.h"
#include <iomanip>
#include <iostream>
#include <string>

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

void InstructionRecord::print()
{
    if(opcode == OPCODE_UNDEF)
    {
        std::cout << "EMPTY";
    }
    else
    {
        std::cout << opcodeToString(opcode);
        std::cout << " R" << (char)(destination + '0') << ',';
        std::cout << " R" << (char)(source1 + '0') << ',';
        std::cout << " R" << (char)(source2 + '0');
    }
}

std::string InstructionRecord::opcodeToString(InstructionRecord::opcode_t oc)
{
    std::string retVal;
    switch(oc)
    {
    case OPCODE_ADD:
        retVal = "Add";
        break;
    case OPCODE_SUB:
        retVal = "Sub";
        break;
    case OPCODE_MUL:
        retVal = "Mul";
        break;
    case OPCODE_DIV:
        retVal = "Div";
        break;
    default:
        retVal = "   ";
        break;
    }
    return retVal;
}
