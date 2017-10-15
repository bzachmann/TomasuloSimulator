#ifndef FUNCTIONALUNIT_H
#define FUNCTIONALUNIT_H

#include "reservationstationrecord.h"
#include "fifo.h"

#define FU_RESULT_BUFFER_SIZE       (10)

class CDBObject
{
public:
    CDBObject():
        destTag(ReservationStationRecord::TAG_UNDEF),
        result(0){}

    ReservationStationRecord::rsrtag_t getDestTag() const;
    void setDestTag(const ReservationStationRecord::rsrtag_t &value);
    int32_t getResult() const;
    void setResult(const int32_t &value);

private:
    ReservationStationRecord::rsrtag_t destTag;
    int32_t result;
};

class FunctionalUnit
{
public:
    FunctionalUnit():
        destTag(ReservationStationRecord::TAG_UNDEF),
        opcode(InstructionRecord::OPCODE_UNDEF),
        operand1(0),
        operand2(0),
        busy(false),
        computationCycle(0),
        resultBuffer(){}

    bool isBusy();
    bool add(ReservationStationRecord record);
    virtual void step(){}
    bool broadcast(CDBObject &result);


protected:
    ReservationStationRecord::rsrtag_t destTag;
    InstructionRecord::opcode_t opcode;
    int32_t operand1;
    int32_t operand2;
    bool busy;

    uint16_t computationCycle;

    Fifo<CDBObject, FU_RESULT_BUFFER_SIZE> resultBuffer;
};

#endif // FUNCTIONALUNIT_H
