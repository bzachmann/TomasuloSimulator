#include "functionalunitmul.h"

#define REQUIRED_CYCLES_MUL                 (10)
#define REQUIRED_CYCLES_DIV                 (40)
#define REQUIRED_CYCLES_DIV_EXCEPTION       (38)

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
            if(operand2 == 0)
            {
                requiredCycles = REQUIRED_CYCLES_DIV_EXCEPTION;
            }
            else
            {
                requiredCycles = REQUIRED_CYCLES_DIV;
            }
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
            result.setRobTag(robTag);
            result.setException(false);
            result.setResult(0);

            if(opcode == InstructionRecord::OPCODE_MUL)
            {
                result.setResult(operand1 * operand2);
            }
            else if(opcode == InstructionRecord::OPCODE_DIV)
            {
                if(operand2 == 0)
                {
                   result.setException(true);
                }
                else
                {
                   result.setResult(operand1 / operand2);
                }
            }
            else
            {
                result.setRobTag(RobRecord::TAG_ROB_UNDEF);
            }

            resultBuffer.put(result);
        }
    }

}
