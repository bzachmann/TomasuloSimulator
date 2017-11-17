#ifndef RESERVATIONSTATIONRECORD_H
#define RESERVATIONSTATIONRECORD_H

#include "stdint.h"
#include "instructionrecord.h"
#include "robrecord.h"
#include <string>

#define PRINT_WIDTH_TAG         (5)
#define PRINT_WIDTH_BUSY        (7)
#define PRINT_WIDTH_OPCODE      (5)
#define PRINT_WIDTH_SOURCE      (12)
#define PRINT_WIDTH_DISPATCHED  (7)

class ReservationStationRecord
{
public:
    enum rsrstate_t
    {
        STATE_EMPTY,
        STATE_OPERAND_WAIT,
        STATE_READY_FOR_DISPATCH,
        STATE_DISPATCHED,
        STATE_RETIRED
    };

    enum rsrtag_t
    {
        TAG_RS1 = 1,
        TAG_RS2,
        TAG_RS3,
        TAG_RS4,
        TAG_RS5,
        TAG_UNDEF = 255
    };

    ReservationStationRecord() :
        state(STATE_EMPTY),
        opcode(InstructionRecord::OPCODE_UNDEF),
        containerTag(TAG_UNDEF),
        destTag(RobRecord::TAG_ROB_UNDEF),
        source1Tag(RobRecord::TAG_ROB_UNDEF),
        source2Tag(RobRecord::TAG_ROB_UNDEF),
        source1Value(0),
        source2Value(0){}

    void setState(rsrstate_t s);
    rsrstate_t getState();
    void setOpcode(InstructionRecord::opcode_t oc);
    InstructionRecord::opcode_t getOpcode();
    void setContainerTag(rsrtag_t tag);
    rsrtag_t getContainerTag();
    RobRecord::robtag_t getDestTag() const;
    void setDestTag(const RobRecord::robtag_t &value);
    void setSource1Tag(RobRecord::robtag_t tag);
    RobRecord::robtag_t getSource1Tag();
    void setSource2Tag(RobRecord::robtag_t tag);
    RobRecord::robtag_t getSource2Tag();
    void setSource1Value(int32_t value);
    int32_t getSource1Value();
    void setSource2Value(int32_t value);
    int32_t getSource2Value();
    void print();

    static std::string tagToString(rsrtag_t tag);

private:
    rsrstate_t state;
    InstructionRecord::opcode_t opcode;
    rsrtag_t containerTag;
    RobRecord::robtag_t destTag;
    RobRecord::robtag_t source1Tag;
    RobRecord::robtag_t source2Tag;
    int32_t source1Value;
    int32_t source2Value;
};

#endif // RESERVATIONSTATIONRECORD_H
