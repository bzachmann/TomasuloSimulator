#include "functionalunitadd.h"

#define REQUIRED_CYCLES_ADD     (2)
#define REQUIRED_CYCLES_SUB     (2)

bool FunctionalUnitAdd::add(ReservationStationRecord record)
{
    bool retVal = FunctionalUnit::add(record);
    if(retVal)
    {
        if(opcode == InstructionRecord::OPCODE_ADD)
        {
            requiredCycles = REQUIRED_CYCLES_ADD;
        }
        else if(opcode == InstructionRecord::OPCODE_SUB)
        {
            requiredCycles = REQUIRED_CYCLES_SUB;
        }
        else
        {
            requiredCycles = 0xFFFF;
        }
    }

    return retVal;
}

void FunctionalUnitAdd::step()
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

            if(opcode == InstructionRecord::OPCODE_ADD)
            {
                result.setResult(operand1 + operand2);
            }
            else if(opcode == InstructionRecord::OPCODE_SUB)
            {
                result.setResult(operand1 - operand2);
            }
            else
            {
                result.setDestTag(ReservationStationRecord::TAG_UNDEF);
            }

            resultBuffer.put(result);
        }
    }
}
