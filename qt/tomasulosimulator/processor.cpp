#include "processor.h"

void Processor::init(InstructionQueue iq, RegisterFile rf)
{
    InstructionRecord myInstr;
    while(iq.get(myInstr))
    {
        IQ.put(myInstr);
    }

    for(uint16_t i = 0; i < rf.getSize(); i++)
    {
        int32_t tempValue;
        rf.getValue(i, tempValue);
        RF.setValue(i, tempValue);
    }
}

void Processor::step()
{

}
