#ifndef BETTERARRAY_H
#define BETTERARRAY_H

#include <stdint.h>

template <uint16_t length> class BetterArray
{
public:
    BetterArray() :
        size(length) {}

    bool getValue(uint16_t index, int32_t &value)
    {
        bool retVal = false;
        if(index < size)
        {
            value = rf[index];
            retVal = true;
        }
        return retVal;
    }

    bool setValue(uint16_t index, int32_t const &value)
    {
        bool retVal = false;
        if(index < size)
        {
            rf[index] = value;
            retVal = true;
        }
        return retVal;
    }

    uint16_t getSize()
    {
        return size;
    }

private:
    uint16_t const size;
    int32_t rf[length];
};

#endif // BETTERARRAY_H
