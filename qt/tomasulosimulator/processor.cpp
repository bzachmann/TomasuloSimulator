#include "processor.h"

void Processor::init(InstructionQueue iq, RegisterFileArray rf)
{
    InstructionRecord myInstr;
    while(iq.get(myInstr))
    {
        IQ.put(myInstr);
    }

    RFRAT.init(rf);
}

void Processor::step()
{
    //broadcast and update RAT, RF, and Both RSs

    //dispatch

    //issue

    //step RSs, step FUs
    RSAddSub.step();
    RSMulDiv.step();
}
