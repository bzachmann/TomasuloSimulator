#ifndef INSTRUCTIONRECORD_H
#define INSTRUCTIONRECORD_H

#include <stdint.h>
#include <string>

#define DEFAULT_DEST        (0)
#define DEFAULT_SOURCE      (0)

class InstructionRecord
{
public:
    enum opcode_t {
        OPCODE_ADD = 0,
        OPCODE_SUB,
        OPCODE_MUL,
        OPCODE_DIV,
        OPCODE_UNDEF = 255,
    };

    InstructionRecord() :
        opcode(OPCODE_UNDEF),
        destination(DEFAULT_DEST),
        source1(DEFAULT_SOURCE),
        source2(DEFAULT_SOURCE) {}

    InstructionRecord(opcode_t oc, uint8_t d, uint8_t s1, uint8_t s2) :
        opcode(oc),
        destination(d),
        source1(s1),
        source2(s2) {}

    opcode_t getOpcode() const;
    void setOpcode(const opcode_t &value);
    uint8_t getDestination() const;
    void setDestination(const uint8_t &value);
    uint8_t getSource1() const;
    void setSource1(const uint8_t &value);
    uint8_t getSource2() const;
    void setSource2(const uint8_t &value);
    void print();

    static std::string opcodeToString(opcode_t oc);

private:
    opcode_t opcode;
    uint8_t destination;
    uint8_t source1;
    uint8_t source2;
};

#endif // INSTRUCTIONRECORD_H
