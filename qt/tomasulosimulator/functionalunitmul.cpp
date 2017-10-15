#include "functionalunitmul.h"

#define REQUIRED_CYCLES_MUL     (10)
#define REQUIRED_CYCLES_DIV     (40)

bool FunctionalUnitMul::add(ReservationStationRecord record)
{
    bool retVal = FunctionalUnit::add(record);
    if(retVal)
    {
        if(opcode == InstructionRecord::OPCODE_MUL)
        {
            requiredCycles = REQUIRED_CYCLES_MUL;
        }
        else if(opcode == InstructionRecord::OPCODE_DIV)
        {
            requiredCycles = REQUIRED_CYCLES_DIV;
        }
        else
        {
            requiredCycles = 0xFFFF;
        }
    }

    return retVal;
}

void FunctionalUnitMul::step()
{
    if(busy == true)
    {
        computationCycle++;
        if(computationCycle == requiredCycles)
        {
            busy = false;
            computationCycle = 0;

            CDBObject result;
            result.setDestTag(destTag);
            result.setResult(0);

            if(opcode == InstructionRecord::OPCODE_MUL)
            {
                result.setResult(operand1 * operand2);
            }
            else if(opcode == InstructionRecord::OPCODE_DIV)
            {
                result.setResult(operand1 / operand2);
            }
            else
            {
                result.setDestTag(ReservationStationRecord::TAG_UNDEF);
            }

            resultBuffer.put(result);
        }
    }

}
