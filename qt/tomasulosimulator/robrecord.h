#ifndef ROBRECORD_H
#define ROBRECORD_H

#include <stdint.h>
#include <string>

//containerTag, dest, val, done, exceptio
#define PRINT_WIDTH_ROB_TAG         (6)
#define PRINT_WIDTH_ROBDEST_REG     (5)
#define PRINT_WIDTH_ROB_VALUE       (12)
#define PRINT_WIDTH_ROB_DONE        (5)
#define PRINT_WIDTH_ROB_EXCEP       (7)

class RobRecord
{
public:
    enum robtag_t
    {
        TAG_ROB1 = 0,
        TAG_ROB2,
        TAG_ROB3,
        TAG_ROB4,
        TAG_ROB5,
        TAG_ROB6,
        TAG_ROB_UNDEF = 255,
    };

    enum robstate_t
    {
        STATE_EMPTY = 0,
        STATE_OCCUPIED,
        STATE_RETIRED,
    };

    RobRecord() :
        containerTag(TAG_ROB_UNDEF),
        state(STATE_EMPTY),
        regDest(0xFF),
        value(0),
        done(false),
        exception(false) {}

    robtag_t getContainerTag() const;
    void setContainerTag(const robtag_t &value);
    robstate_t getState() const;
    void setState(const robstate_t &value);
    uint8_t getRegDest() const;
    void setRegDest(const uint8_t &value);
    int32_t getValue() const;
    void setValue(const int32_t &value);
    bool getDone() const;
    void setDone(bool value);
    bool getException() const;
    void setException(bool value);
    void print();

    static std::string tagToString(robtag_t tag);

private:
    robtag_t containerTag;
    robstate_t state;
    uint8_t regDest;
    int32_t value;
    bool done;
    bool exception;
};

#endif // ROBRECORD_H
