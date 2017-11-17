#include "processor.h"
#include <iostream>

void Processor::init(InstructionQueue iq, RegisterFileArray rf)
{
    InstructionRecord myInstr;
    while(iq.get(myInstr))
    {
        IQ.put(myInstr);
    }

    RFRAT.init(rf);
    ROB.init();
}

void Processor::step()
{
    //commit a value if available to commit
    RobRecord commitRecord;
    bool instrReadyForCommit = ROB.getCommitInstr(commitRecord);
    if(instrReadyForCommit)
    {
        if(commitRecord.getException())
        {
#warning todo - handle exception here... reset everything print and exit out. do not allow step again
            ROB.reset();
        }
        else
        {
            RFRAT.commit(commitRecord.getRegDest(), commitRecord.getContainerTag(), commitRecord.getValue());
        }
    }

    //broadcast and update RAT, RF, and Both RSs    
    CDBObject broadcastResults;
    if(FUMul.broadcast(broadcastResults))
    {
        ROB.capture(broadcastResults);
        RSAddSub.capture(broadcastResults.getRobTag(), broadcastResults.getResult());
        RSMulDiv.capture(broadcastResults.getRobTag(), broadcastResults.getResult());
    }
    else if(FUAdd.broadcast(broadcastResults))
    {
        ROB.capture(broadcastResults);
        RSAddSub.capture(broadcastResults.getRobTag(), broadcastResults.getResult());
        RSMulDiv.capture(broadcastResults.getRobTag(), broadcastResults.getResult());
    }

    //dispatch
    ReservationStationRecord dispatchedInstr;
    if(!FUAdd.isBusy())
    {
        if(RSAddSub.dispatch(dispatchedInstr))
        {
            FUAdd.add(dispatchedInstr);
        }
    }

    if(!FUMul.isBusy())
    {
        if(RSMulDiv.dispatch(dispatchedInstr))
        {
            FUMul.add(dispatchedInstr);
        }
    }

    //issue
    InstructionRecord issuedInstr;
    if(IQ.peek(issuedInstr) && !ROB.isFull())
    {
        if( ((issuedInstr.getOpcode() == InstructionRecord::OPCODE_ADD)
              ||(issuedInstr.getOpcode() == InstructionRecord::OPCODE_SUB))
             && (RSAddSub.notFull()))
        {
            IQ.get(issuedInstr);
            ReservationStationRecord issuedRecord;
            issuedRecord.setOpcode(issuedInstr.getOpcode());

            RobRecord::robtag_t tempTag;
            int32_t tempValue;
            RFRAT.getSource(issuedInstr.getSource1(), tempTag, tempValue);
            if(tempTag != RobRecord::TAG_ROB_UNDEF)
            {
                bool robHasValue;
                ROB.getSource(tempTag, robHasValue, tempValue);
                if(robHasValue)
                {
                    tempTag = RobRecord::TAG_ROB_UNDEF;
                }
            }
            issuedRecord.setSource1Tag(tempTag);
            issuedRecord.setSource1Value(tempValue);

            RFRAT.getSource(issuedInstr.getSource2(), tempTag, tempValue);
            if(tempTag != RobRecord::TAG_ROB_UNDEF)
            {
                bool robHasValue;
                ROB.getSource(tempTag, robHasValue, tempValue);
                if(robHasValue)
                {
                    tempTag = RobRecord::TAG_ROB_UNDEF;
                }
            }
            issuedRecord.setSource2Tag(tempTag);
            issuedRecord.setSource2Value(tempValue);

            tempTag = ROB.issue(issuedInstr);
            issuedRecord.setDestTag(tempTag);
            RSAddSub.issue(issuedRecord);
            RFRAT.tag(issuedInstr.getDestination(), tempTag);
        }
        else if( ((issuedInstr.getOpcode() == InstructionRecord::OPCODE_MUL)
                   ||(issuedInstr.getOpcode() == InstructionRecord::OPCODE_DIV))
                  && (RSMulDiv.notFull()))
        {
            IQ.get(issuedInstr);
            ReservationStationRecord issuedRecord;
            issuedRecord.setOpcode(issuedInstr.getOpcode());

            RobRecord::robtag_t tempTag;
            int32_t tempValue;
            RFRAT.getSource(issuedInstr.getSource1(), tempTag, tempValue);
            if(tempTag != RobRecord::TAG_ROB_UNDEF)
            {
                bool robHasValue;
                ROB.getSource(tempTag, robHasValue, tempValue);
                if(robHasValue)
                {
                    tempTag = RobRecord::TAG_ROB_UNDEF;
                }
            }
            issuedRecord.setSource1Tag(tempTag);
            issuedRecord.setSource1Value(tempValue);

            RFRAT.getSource(issuedInstr.getSource2(), tempTag, tempValue);
            if(tempTag != RobRecord::TAG_ROB_UNDEF)
            {
                bool robHasValue;
                ROB.getSource(tempTag, robHasValue, tempValue);
                if(robHasValue)
                {
                    tempTag = RobRecord::TAG_ROB_UNDEF;
                }
            }
            issuedRecord.setSource2Tag(tempTag);
            issuedRecord.setSource2Value(tempValue);

            tempTag = ROB.issue(issuedInstr);
            issuedRecord.setDestTag(tempTag);
            RSMulDiv.issue(issuedRecord);
            RFRAT.tag(issuedInstr.getDestination(), tempTag);
        }
    }

    //step ROB, RSs, step FUs
    ROB.step();
    RSAddSub.step();
    RSMulDiv.step();
    FUAdd.step();
    FUMul.step();
}

void Processor::print()
{
#warning todo add printing of ROB
    std::cout << std::endl;
    RSAddSub.print();
    std::cout << std::endl;
    RSMulDiv.print();
    std::cout << std::endl;
    RFRAT.print();
    std::cout << std::endl;
    IQ.print();
}
