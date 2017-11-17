#include "reorderbuffer.h"

void ReOrderBuffer::init()
{
    for(uint8_t i = 0; i < ROB_SIZE; i++)
    {
        robRecords[i].setContainerTag((RobRecord::robtag_t)(i+1));
    }
}

void ReOrderBuffer::reset()
{
    for(uint8_t i = 0; i < ROB_SIZE; i++)
    {
       robRecords[i].setState(RobRecord::STATE_EMPTY);
       robRecords[i].setDone(false);
       robRecords[i].setException(false);
       robRecords[i].setRegDest(0xFF);
       robRecords[i].setValue(0);
    }

    commitPtrIndex = 0;
    robRecordsOccupied = 0;
}

void ReOrderBuffer::step()
{
    if(robRecords[getCommitPtrIndex()].getState() == RobRecord::STATE_RETIRED)
    {
        robRecords[getCommitPtrIndex()].setState(RobRecord::STATE_EMPTY);
        commitPtrIndex = (commitPtrIndex + 1) % ROB_SIZE;
        if(robRecordsOccupied > 0)
        {
            robRecordsOccupied = robRecordsOccupied - 1;
        }
    }
}

bool ReOrderBuffer::getCommitInstr(RobRecord &robRecord)
{
    bool retVal = false;
    if(robRecords[getCommitPtrIndex()].getDone())
    {
        robRecord = robRecords[getCommitPtrIndex()];
        robRecords[getCommitPtrIndex()].setState(RobRecord::STATE_RETIRED);
    }
    return retVal;
}

RobRecord::robtag_t ReOrderBuffer::issue(InstructionRecord instrRecord)
{
#warning todo - implement this
}

void ReOrderBuffer::capture(CDBObject cdbObject)
{
#warning todo - implement this
    //set state to done
    //update value
    //
}

uint8_t ReOrderBuffer::getIssuePtrIndex(bool &full)
{
    full = isFull();
    return (commitPtrIndex + robRecordsOccupied) % ROB_SIZE;
}

uint8_t ReOrderBuffer::getCommitPtrIndex()
{
    return commitPtrIndex;
}

bool ReOrderBuffer::isFull()
{
   return robRecordsOccupied == ROB_SIZE;
}
