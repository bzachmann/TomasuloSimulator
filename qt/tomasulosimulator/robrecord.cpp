#include "robrecord.h"


RobRecord::robtag_t RobRecord::getContainerTag() const
{
    return containerTag;
}

void RobRecord::setContainerTag(const robtag_t &value)
{
    containerTag = value;
}

RobRecord::robstate_t RobRecord::getState() const
{
    return state;
}

void RobRecord::setState(const robstate_t &value)
{
    state = value;
}


uint8_t RobRecord::getRegDest() const
{
    return regDest;
}

void RobRecord::setRegDest(const uint8_t &value)
{
    regDest = value;
}

int32_t RobRecord::getValue() const
{
    return value;
}

void RobRecord::setValue(const int32_t &value)
{
    this->value = value;
}

bool RobRecord::getDone() const
{
    return done;
}

void RobRecord::setDone(bool value)
{
    done = value;
}

bool RobRecord::getException() const
{
    return exception;
}

void RobRecord::setException(bool value)
{
    exception = value;
}
