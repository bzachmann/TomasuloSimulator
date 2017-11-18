#include "reservationstationrecord.h"
#include <iomanip>
#include <iostream>


void ReservationStationRecord::setState(ReservationStationRecord::rsrstate_t s)
{
    state = s;
}

ReservationStationRecord::rsrstate_t ReservationStationRecord::getState()
{
    return state;
}

void ReservationStationRecord::setOpcode(InstructionRecord::opcode_t oc)
{
    opcode = oc;
}

InstructionRecord::opcode_t ReservationStationRecord::getOpcode()
{
    return opcode;
}

void ReservationStationRecord::setContainerTag(ReservationStationRecord::rsrtag_t tag)
{
    containerTag = tag;
}

ReservationStationRecord::rsrtag_t ReservationStationRecord::getContainerTag()
{
    return containerTag;
}

RobRecord::robtag_t ReservationStationRecord::getDestTag() const
{
    return destTag;
}

void ReservationStationRecord::setDestTag(const RobRecord::robtag_t &value)
{
    destTag = value;
}

void ReservationStationRecord::setSource1Tag(RobRecord::robtag_t tag)
{
    source1Tag = tag;
}

RobRecord::robtag_t ReservationStationRecord::getSource1Tag()
{
    return source1Tag;
}

void ReservationStationRecord::setSource2Tag(RobRecord::robtag_t tag)
{
    source2Tag = tag;
}

RobRecord::robtag_t ReservationStationRecord::getSource2Tag()
{
    return source2Tag;
}

void ReservationStationRecord::setSource1Value(int32_t value)
{
    source1Value = value;
}

int32_t ReservationStationRecord::getSource1Value()
{
    return source1Value;
}

void ReservationStationRecord::setSource2Value(int32_t value)
{
    source2Value = value;
}

int32_t ReservationStationRecord::getSource2Value()
{
    return source2Value;
}

void ReservationStationRecord::print()
{
#warning todo - modify to include ROB dest tag
    std::cout << std::right << std::setw(PRINT_WIDTH_TAG) << std::setfill(' ') << tagToString(containerTag);

    uint16_t busy = 0;
    if(state != STATE_EMPTY)
    {
        busy = 1;
    }
    std::cout << std::right << std::setw(PRINT_WIDTH_BUSY) << std::setfill(' ') << busy;

    if(busy)
    {
        std::cout << std::right << std::setw(PRINT_WIDTH_DEST) << std::setfill(' ') << RobRecord::tagToString(destTag);
        std::cout << std::right << std::setw(PRINT_WIDTH_OPCODE) << std::setfill(' ') << InstructionRecord::opcodeToString(opcode);

        if(source1Tag == TAG_UNDEF)
        {
            std::cout << std::right << std::setw(PRINT_WIDTH_SOURCE) << std::setfill(' ') << source1Value;
        }
        else
        {
            std::cout << std::right << std::setw(PRINT_WIDTH_SOURCE) << std::setfill(' ') << "  ";
        }

        if(source2Tag == TAG_UNDEF)
        {
            std::cout << std::right << std::setw(PRINT_WIDTH_SOURCE) << std::setfill(' ') << source2Value;
        }
        else
        {
            std::cout << std::right << std::setw(PRINT_WIDTH_SOURCE) << std::setfill(' ') << "  ";
        }

        if(source1Tag != TAG_UNDEF)
        {
            std::cout << std::right << std::setw(PRINT_WIDTH_TAG) << std::setfill(' ') << RobRecord::tagToString(source1Tag);
        }
        else
        {
            std::cout << std::right << std::setw(PRINT_WIDTH_TAG) << std::setfill(' ') << "  ";
        }

        if(source2Tag != TAG_UNDEF)
        {
            std::cout << std::right << std::setw(PRINT_WIDTH_TAG) << std::setfill(' ') << RobRecord::tagToString(source2Tag);
        }
        else
        {
            std::cout << std::right << std::setw(PRINT_WIDTH_TAG) << std::setfill(' ') << "  ";
        }
    }
}

std::string ReservationStationRecord::tagToString(ReservationStationRecord::rsrtag_t tag)
{
    std::string retVal;
    switch(tag)
    {
    case TAG_RS1:
        retVal = "RS1";
        break;
    case TAG_RS2:
        retVal = "RS2";
        break;
    case TAG_RS3:
        retVal = "RS3";
        break;
    case TAG_RS4:
        retVal = "RS4";
        break;
    case TAG_RS5:
        retVal = "RS5";
        break;
    default:
        retVal = "   ";
        break;
    }
    return retVal;
}
