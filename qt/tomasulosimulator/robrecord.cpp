#include "robrecord.h"
#include <iomanip>
#include <iostream>


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

void RobRecord::print()
{
  //containerTag, dest, val, done, exception
    std::cout << std::right << std::setw(PRINT_WIDTH_ROB_TAG) << std::setfill(' ') << tagToString(containerTag);
    if(state != STATE_EMPTY)
    {
        std::cout << std::right << std::setw(PRINT_WIDTH_ROBDEST_REG) << std::setfill(' ') << (uint16_t)regDest;
        if(done)
        {
           std::cout << std::right << std::setw(PRINT_WIDTH_ROB_VALUE) << std::setfill(' ') << value;
        }
        else
        {
            std::cout << std::right << std::setw(PRINT_WIDTH_ROB_VALUE) << std::setfill(' ') << " ";
        }
        std::cout << std::right << std::setw(PRINT_WIDTH_ROB_DONE) << std::setfill(' ') << done;
        std::cout << std::right << std::setw(PRINT_WIDTH_ROB_EXCEP) << std::setfill(' ') << exception;
    }
}

std::string RobRecord::tagToString(RobRecord::robtag_t tag)
{
    std::string retVal;
    switch(tag)
    {
    case TAG_ROB1:
        retVal = "ROB1";
        break;
    case TAG_ROB2:
        retVal = "ROB2";
        break;
    case TAG_ROB3:
        retVal = "ROB3";
        break;
    case TAG_ROB4:
        retVal = "ROB4";
        break;
    case TAG_ROB5:
        retVal = "ROB5";
        break;
    case TAG_ROB6:
        retVal = "ROB6";
        break;
    default:
        retVal = "    ";
        break;
    }
    return retVal;
}
