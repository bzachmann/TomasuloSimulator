#include "functionalunit.h"

RobRecord::robtag_t CDBObject::getRobTag() const
{
    return robTag;
}

void CDBObject::setRobTag(const RobRecord::robtag_t &value)
{
    robTag = value;
}

int32_t CDBObject::getResult() const
{
    return result;
}

void CDBObject::setResult(const int32_t &value)
{
    result = value;
}

bool CDBObject::getException() const
{
    return exception;
}

void CDBObject::setException(bool value)
{
    exception = value;
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

        robTag = record.getDestTag();
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

void FunctionalUnit::reset()
{
    busy = false;
    computationCycle = 0;
}
