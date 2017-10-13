#include "reservationstationmuldiv.h"

ReservationStationMulDiv::ReservationStationMulDiv()
{
    rsrecords[0].setContainerTag(ReservationStationRecord::TAG_RS4);
    rsrecords[1].setContainerTag(ReservationStationRecord::TAG_RS5);
}

void ReservationStationMulDiv::step()
{
    for(uint8_t i = 0; i < NUM_RS_MUL_DIV_RECORDS; i++)
    {
        if((rsrecords[i].getState() == ReservationStationRecord::STATE_OPERAND_WAIT)
                && (rsrecords[i].getSource1Tag() == ReservationStationRecord::TAG_UNDEF)
                && (rsrecords[i].getSource2Tag() == ReservationStationRecord::TAG_UNDEF))
        {
           rsrecords[i].setState(ReservationStationRecord::STATE_READY_FOR_DISPATCH);
        }
        else if(rsrecords[i].getState() == ReservationStationRecord::STATE_RETIRED)
        {
            rsrecords[i].setState(ReservationStationRecord::STATE_EMPTY);
        }
    }
}

bool ReservationStationMulDiv::notFull()
{
    bool retVal = false;
    for(uint8_t i = 0; i < NUM_RS_MUL_DIV_RECORDS; i++)
    {
        if(rsrecords[i].getState() == ReservationStationRecord::STATE_EMPTY)
        {
            retVal = true;
            break;
        }
    }
    return retVal;
}

ReservationStationRecord::rsrtag_t ReservationStationMulDiv::issue(ReservationStationRecord record)
{
    ReservationStationRecord::rsrtag_t containerTag = ReservationStationRecord::TAG_UNDEF;
    for(uint8_t i = 0; i < NUM_RS_MUL_DIV_RECORDS; i++)
    {
        if(rsrecords[i].getState() == ReservationStationRecord::STATE_EMPTY)
        {
            rsrecords[i].setOpcode(record.getOpcode());
            rsrecords[i].setSource1Tag(record.getSource1Tag());
            rsrecords[i].setSource1Value(record.getSource1Value());
            rsrecords[i].setSource2Tag(record.getSource2Tag());
            rsrecords[i].setSource2Value(record.getSource2Value());
            rsrecords[i].setState(ReservationStationRecord::STATE_OPERAND_WAIT);
            containerTag = rsrecords[i].getContainerTag();
            break;
        }
    }
    return containerTag;
}

void ReservationStationMulDiv::capture(ReservationStationRecord::rsrtag_t tag, int32_t value)
{
    for(uint8_t i = 0; i < NUM_RS_MUL_DIV_RECORDS; i++)
    {
        if(rsrecords[i].getContainerTag() == tag)
        {
            rsrecords[i].setState(ReservationStationRecord::STATE_RETIRED);
        }

        if(rsrecords[i].getSource1Tag() == tag)
        {
            rsrecords[i].setSource1Value(value);
            rsrecords[i].setSource1Tag(ReservationStationRecord::TAG_UNDEF);
        }

        if(rsrecords[i].getSource2Tag() == tag)
        {
            rsrecords[i].setSource2Value(value);
            rsrecords[i].setSource2Tag(ReservationStationRecord::TAG_UNDEF);
        }
    }
}

bool ReservationStationMulDiv::dispatch(ReservationStationRecord &record)
{
    bool retVal = false;
    for(uint8_t i = 0; i< NUM_RS_MUL_DIV_RECORDS; i++)
    {
        if(rsrecords[i].getState() == ReservationStationRecord::STATE_READY_FOR_DISPATCH)
        {
            record = rsrecords[i];
            rsrecords[i].setState(ReservationStationRecord::STATE_DISPATCHED);
            retVal = true;
            break;
        }
    }
    return retVal;
}
