#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>

template<class T, uint32_t usableLength> class Fifo
{  
public:
    Fifo<T, usableLength>() :
        arrayLength(usableLength + 1),
        maxUsed(0),
        head(0),
        tail(0){}

    void flush()
    {
        head = 0;
        tail = 0;
        maxUsed = 0;
    }

    bool notFull() const
    {
        return (available() != 0);
    }

    uint32_t available() const
    {
        return (usableLength - pending());
    }

    bool put(T const &entry)
    {
        uint32_t newPending = pending() + 1;
        bool success = newPending < arrayLength;

        if(success)
        {
            data[tail] = entry;

            tail++;
            tail %= arrayLength;

            if (newPending > maxUsed)
            {
                maxUsed = newPending;
            }
        }
        return success;
    }

    bool notEmpty() const
    {
        return (head != tail);
    }

    uint32_t pending() const
    {
        uint32_t tempTail = tail;
        tempTail += (head > tail) ? arrayLength : 0;
        return (tempTail - head);
    }

    bool get(T &entry)
    {
        bool success = notEmpty();
        if (success)
        {
            entry = data[head];

            head++;
            head %= arrayLength;
        }
        return success;
    }

    bool peek(T &entry)
    {
        bool success = notEmpty();
        if(success)
        {
            entry = data[head];
        }
        return success;
    }

private:
    uint32_t const arrayLength;
    T data[usableLength + 1];
    uint32_t maxUsed;
    uint32_t head;
    uint32_t tail;

};

#endif // FIFO_H
