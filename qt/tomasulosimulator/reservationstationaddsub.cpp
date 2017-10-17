#include "reservationstationaddsub.h"
#include <iomanip>
#include <iostream>


ReservationStationAddSub::ReservationStationAddSub()
{
    rsrecords[0].setContainerTag(ReservationStationRecord::TAG_RS1);
    rsrecords[1].setContainerTag(ReservationStationRecord::TAG_RS2);
    rsrecords[2].setContainerTag(ReservationStationRecord::TAG_RS3);
}

void ReservationStationAddSub::step()
{
    for(uint8_t i = 0; i < NUM_RS_ADD_SUB_RECORDS; i++)
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

bool ReservationStationAddSub::notFull()
{
    bool retVal = false;
    for(uint8_t i = 0; i < NUM_RS_ADD_SUB_RECORDS; i++)
    {
        if(rsrecords[i].getState() == ReservationStationRecord::STATE_EMPTY)
        {
            retVal = true;
            break;
        }
    }
    return retVal;
}

ReservationStationRecord::rsrtag_t ReservationStationAddSub::issue(ReservationStationRecord record)
{
    ReservationStationRecord::rsrtag_t containerTag = ReservationStationRecord::TAG_UNDEF;
    for(uint8_t i = 0; i < NUM_RS_ADD_SUB_RECORDS; i++)
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

void ReservationStationAddSub::capture(ReservationStationRecord::rsrtag_t tag, int32_t value)
{
    for(uint8_t i = 0; i < NUM_RS_ADD_SUB_RECORDS; i++)
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

bool ReservationStationAddSub::dispatch(ReservationStationRecord &record)
{
    bool retVal = false;
    for(uint8_t i = 0; i< NUM_RS_ADD_SUB_RECORDS; i++)
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

void ReservationStationAddSub::print()
{
    std::cout << "Add/Sub Reservation Station" << std::endl;
    std::cout << std::right << std::setw(PRINT_WIDTH_TAG) << std::setfill(' ') << "  ";
    std::cout << std::right << std::setw(PRINT_WIDTH_BUSY) << std::setfill(' ') << "Busy";
    std::cout << std::right << std::setw(PRINT_WIDTH_OPCODE) << std::setfill(' ') << "Op";
    std::cout << std::right << std::setw(PRINT_WIDTH_SOURCE) << std::setfill(' ') << "Vj";
    std::cout << std::right << std::setw(PRINT_WIDTH_SOURCE) << std::setfill(' ') << "Vk";
    std::cout << std::right << std::setw(PRINT_WIDTH_TAG) << std::setfill(' ') << "Qj";
    std::cout << std::right << std::setw(PRINT_WIDTH_TAG) << std::setfill(' ') << "Qk";
    std::cout << std::right << std::setw(PRINT_WIDTH_DISPATCHED) << std::setfill(' ') << "Disp" << std::endl;

    for(uint8_t i = 0; i < NUM_RS_ADD_SUB_RECORDS; i++)
    {
        rsrecords[i].print();
        std::cout << std::endl;
    }
}
