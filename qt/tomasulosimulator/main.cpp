#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "processor.h"

using namespace std;

Processor processor;
InstructionQueue initialIQ;
RegisterFileArray initialRF;
uint16_t numCycles = 0;

bool parseInputFile(char* file);
bool parseUint16(string line, uint16_t &num);
bool parseInt32(string line, int32_t &num);
bool parseInstruction(string line, InstructionRecord &instr);

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "Usage: " << argv[0] << " <Input File>" << endl;
    }
    else if (parseInputFile(argv[1]))
    {
        processor.init(initialIQ, initialRF);
        for(uint16_t i = 0; i < numCycles; i++)
        {
            processor.step();
        }

        //processor print information here
    }
    else
    {
        cout << "Execution terminated due to error with input file" << endl;
    }
    return 0;
}

bool parseInputFile(char* file)
{
    bool retVal = false;

    string line;
    ifstream inputfile(file);
    if(inputfile.is_open())
    {
        uint16_t numInstr = 0;
        if(!getline(inputfile, line)) return false;
        if(!parseUint16(line, numInstr)) return false;

        if(!getline(inputfile, line)) return false;
        if(!parseUint16(line, numCycles)) return false;

        InstructionRecord tempInstr;
        for(uint16_t i = 0; i < numInstr; i++)
        {
            if(!getline(inputfile, line)) return false;
            if(!parseInstruction(line, tempInstr)) return false;
            initialIQ.put(tempInstr);
        }

        for(uint16_t i = 0; i < RF_SIZE; i++)
        {
            int32_t tempValue = 0;
            if(!getline(inputfile, line)) return false;
            if(!parseInt32(line, tempValue)) return false;
            if(!initialRF.setValue(i,tempValue)) return false;
        }

        inputfile.close();
        retVal = true;
    }
    else
    {
        cout << "Unable to locate or open input file" << endl;
    }
    return retVal;
}

bool parseUint16(string line, uint16_t &num)
{
    bool retVal = false;
    try
    {
        num = std::stoi(line);
        retVal = true;
    }
    catch(...)
    {
        retVal = false;
    }
    return retVal;
}

bool parseInt32(string line, int32_t &num)
{
    bool retVal = false;
    try
    {
        num = std::stoi(line);
        retVal = true;
    }
    catch(...)
    {
        retVal = false;
    }
    return retVal;
}

bool parseInstruction(string line, InstructionRecord &instr)
{
    std::istringstream iss(line);
    int32_t tempValue = 0;

    if(!(iss >> tempValue)) return false;
    if(!((tempValue >= 0) && (tempValue <= 3))) return false;
    instr.setOpcode((InstructionRecord::opcode_t)tempValue);

    if(!(iss >> tempValue)) return false;
    if(!((tempValue >= 0) && (tempValue <= RF_SIZE))) return false;
    instr.setDestination((uint8_t)tempValue);

    if(!(iss >> tempValue)) return false;
    if(!((tempValue >= 0) && (tempValue <= RF_SIZE))) return false;
    instr.setSource1((uint8_t)tempValue);

    if(!(iss >> tempValue)) return false;
    if(!((tempValue >= 0) && (tempValue <= RF_SIZE))) return false;
    instr.setSource2((uint8_t)tempValue);

    return true;
}



