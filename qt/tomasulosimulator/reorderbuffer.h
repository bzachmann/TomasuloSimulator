#ifndef REORDERBUFFER_H
#define REORDERBUFFER_H

#include "robrecord.h"
#include "instructionrecord.h"
#include "functionalunit.h"

#define ROB_SIZE        (6)

class ReOrderBuffer
{
public:
    ReOrderBuffer() :
        robRecords() {}
    void init();
    void reset();//used to reset rob
    void step();//set retired records to empty, move commit pointer forward if retired

    bool getCommitInstr(RobRecord &robRecord); //return false if commit ptr pointing at not done record.  return true and set arg to commit instr otherwise.
    RobRecord::robtag_t issue(InstructionRecord instrRecord); //pass back rob containerTag to be used in rat.  pass back UNDEF if no space
    void capture(CDBObject cdbObject);

private:
    uint8_t getIssuePtrIndex(bool &full);
    uint8_t getCommitPtrIndex();
    bool isFull();

private:
    RobRecord robRecords[ROB_SIZE];
    uint8_t commitPtrIndex;
    uint8_t robRecordsOccupied;


};

#endif // REORDERBUFFER_H
