#ifndef REORDERBUFFER_H
#define REORDERBUFFER_H

#include "robrecord.h"
#include "instructionrecord.h"
#include "functionalunit.h"

#define ROB_SIZE            (6)
#define PRINT_WIDTH_PTR     (6)

class ReOrderBuffer
{
public:
    ReOrderBuffer() :
        robRecords() {}
    void init();
    void reset();
    void step();

    bool getCommitInstr(RobRecord &robRecord);
    RobRecord::robtag_t issue(InstructionRecord instrRecord);
    void capture(CDBObject cdbObject);
    void getSource(RobRecord::robtag_t tag, bool &valid, int32_t &value);
    bool isFull();
    void print();

private:
    uint8_t getIssuePtrIndex(bool &full);
    uint8_t getCommitPtrIndex();

private:
    RobRecord robRecords[ROB_SIZE];
    uint8_t commitPtrIndex;
    uint8_t robRecordsOccupied;


};

#endif // REORDERBUFFER_H
