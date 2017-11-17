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
    RobRecord::robtag_t issueTag = RobRecord::TAG_ROB_UNDEF;
    if(!isFull())
    {
       bool dummy;
       issueTag = robRecords[getIssuePtrIndex(dummy)].getContainerTag();
       robRecords[getIssuePtrIndex(dummy)].setState(RobRecord::STATE_OCCUPIED);
       robRecords[getIssuePtrIndex(dummy)].setException(false);
       robRecords[getIssuePtrIndex(dummy)].setDone(false);
       robRecords[getIssuePtrIndex(dummy)].setValue(0);
       robRecords[getIssuePtrIndex(dummy)].setRegDest(instrRecord.getDestination());

       if(robRecordsOccupied != ROB_SIZE)
       {
           robRecordsOccupied = (robRecordsOccupied + 1) % ROB_SIZE;
       }
    }
    return issueTag;
}

void ReOrderBuffer::capture(CDBObject cdbObject)
{
    for(uint8_t i = 0; i < ROB_SIZE; i++)
    {
        if(cdbObject.getRobTag() == robRecords[i].getContainerTag())
        {
            robRecords[i].setValue(cdbObject.getResult());
            robRecords[i].setException(cdbObject.getException());
            robRecords[i].setDone(true);
        }
    }
}

void ReOrderBuffer::getSource(RobRecord::robtag_t tag, bool &valid, int32_t &value)
{
    for(uint8_t i = 0; i < ROB_SIZE; i++)
    {
        if(robRecords[i].getContainerTag() == tag)
        {
            valid = robRecords[i].getDone();
            value = robRecords[i].getValue();
            break;
        }
    }
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
