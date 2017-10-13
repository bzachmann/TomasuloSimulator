#include "reservationstationrecord.h"


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

void ReservationStationRecord::setSource1Tag(ReservationStationRecord::rsrtag_t tag)
{
    source1Tag = tag;
}

ReservationStationRecord::rsrtag_t ReservationStationRecord::getSource1Tag()
{
    return source1Tag;
}

void ReservationStationRecord::setSource2Tag(ReservationStationRecord::rsrtag_t tag)
{
    source2Tag = tag;
}

ReservationStationRecord::rsrtag_t ReservationStationRecord::getSource2Tag()
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
