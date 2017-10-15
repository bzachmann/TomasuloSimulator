#include "functionalunit.h"

ReservationStationRecord::rsrtag_t CDBObject::getDestTag() const
{
    return destTag;
}

void CDBObject::setDestTag(const ReservationStationRecord::rsrtag_t &value)
{
    destTag = value;
}

int32_t CDBObject::getResult() const
{
    return result;
}

void CDBObject::setResult(const int32_t &value)
{
    result = value;
}

bool FunctionalUnit::isBusy()
{
    return busy;
}

bool FunctionalUnit::add(ReservationStationRecord record)
{
    bool retVal = false;
    if(!busy)
    {
        busy = true;
        computationCycle = 0;

        destTag = record.getContainerTag();
        opcode = record.getOpcode();
        operand1 = record.getSource1Value();
        operand2 = record.getSource2Value();

        retVal = true;
    }

    return retVal;
}

bool FunctionalUnit::broadcast(CDBObject &result)
{
    return resultBuffer.get(result);
}
