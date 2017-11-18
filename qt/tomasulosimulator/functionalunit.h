#ifndef FUNCTIONALUNIT_H
#define FUNCTIONALUNIT_H

#include "reservationstationrecord.h"
#include "robrecord.h"
#include "fifo.h"

#define FU_RESULT_BUFFER_SIZE       (10)

class CDBObject
{
public:
    CDBObject():
        robTag(RobRecord::TAG_ROB_UNDEF),
        result(0),
        exception(false){}

    RobRecord::robtag_t getRobTag() const;
    void setRobTag(const RobRecord::robtag_t &value);
    int32_t getResult() const;
    void setResult(const int32_t &value);
    bool getException() const;
    void setException(bool value);

private:
    RobRecord::robtag_t robTag;
    int32_t result;
    bool exception;
};

class FunctionalUnit
{
public:
    FunctionalUnit():
        robTag(RobRecord::TAG_ROB_UNDEF),
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
    void reset();


protected:
    RobRecord::robtag_t robTag;
    InstructionRecord::opcode_t opcode;
    int32_t operand1;
    int32_t operand2;
    bool busy;

    uint16_t computationCycle;

    Fifo<CDBObject, FU_RESULT_BUFFER_SIZE> resultBuffer;
};

#endif // FUNCTIONALUNIT_H
