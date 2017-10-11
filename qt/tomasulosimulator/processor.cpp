#include "processor.h"

void Processor::init(InstructionQueue iq)
{
    InstructionRecord myInstr;
    while(iq.get(myInstr))
    {
        IQ.put(myInstr);
    }
}

void Processor::step()
{

}
