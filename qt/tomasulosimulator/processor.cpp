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
}

void Processor::step()
{
    //broadcast and update RAT, RF, and Both RSs
    CDBObject broadcastResults;
    if(FUMul.broadcast(broadcastResults))
    {
        RSAddSub.capture(broadcastResults.getDestTag(), broadcastResults.getResult());
        RSMulDiv.capture(broadcastResults.getDestTag(), broadcastResults.getResult());
        RFRAT.capture(broadcastResults.getDestTag(), broadcastResults.getResult());
    }
    else if(FUAdd.broadcast(broadcastResults))
    {
        RSAddSub.capture(broadcastResults.getDestTag(), broadcastResults.getResult());
        RSMulDiv.capture(broadcastResults.getDestTag(), broadcastResults.getResult());
        RFRAT.capture(broadcastResults.getDestTag(), broadcastResults.getResult());
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
    if(IQ.peek(issuedInstr))
    {
        if( ((issuedInstr.getOpcode() == InstructionRecord::OPCODE_ADD)
              ||(issuedInstr.getOpcode() == InstructionRecord::OPCODE_SUB))
             && (RSAddSub.notFull()))
        {
            IQ.get(issuedInstr);
            ReservationStationRecord issuedRecord;
            issuedRecord.setOpcode(issuedInstr.getOpcode());

            ReservationStationRecord::rsrtag_t tempTag;
            int32_t tempValue;
            RFRAT.getSource(issuedInstr.getSource1(), tempTag, tempValue);
            issuedRecord.setSource1Tag(tempTag);
            issuedRecord.setSource1Value(tempValue);

            RFRAT.getSource(issuedInstr.getSource2(), tempTag, tempValue);
            issuedRecord.setSource2Tag(tempTag);
            issuedRecord.setSource2Value(tempValue);

            tempTag = RSAddSub.issue(issuedRecord);
            RFRAT.tag(issuedInstr.getDestination(), tempTag);
        }
        else if( ((issuedInstr.getOpcode() == InstructionRecord::OPCODE_MUL)
                   ||(issuedInstr.getOpcode() == InstructionRecord::OPCODE_DIV))
                  && (RSMulDiv.notFull()))
        {
            IQ.get(issuedInstr);
            ReservationStationRecord issuedRecord;
            issuedRecord.setOpcode(issuedInstr.getOpcode());

            ReservationStationRecord::rsrtag_t tempTag;
            int32_t tempValue;
            RFRAT.getSource(issuedInstr.getSource1(), tempTag, tempValue);
            issuedRecord.setSource1Tag(tempTag);
            issuedRecord.setSource1Value(tempValue);

            RFRAT.getSource(issuedInstr.getSource2(), tempTag, tempValue);
            issuedRecord.setSource2Tag(tempTag);
            issuedRecord.setSource2Value(tempValue);

            tempTag = RSMulDiv.issue(issuedRecord);
            RFRAT.tag(issuedInstr.getDestination(), tempTag);
        }
    }

    //step RSs, step FUs
    RSAddSub.step();
    RSMulDiv.step();
    FUAdd.step();
    FUMul.step();
}

void Processor::print()
{
#warning todo add printing of other processor parts
    std::cout << std::endl;
    RSAddSub.print();
    std::cout << std::endl;
    RSMulDiv.print();
    std::cout << std::endl;
    RFRAT.print();
    std::cout << std::endl;
    IQ.print();
}
