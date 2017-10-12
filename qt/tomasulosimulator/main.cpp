#include <iostream>
#include <fstream>
#include <string>
#include "processor.h"

using namespace std;

Processor processor;
InstructionQueue initialIQ;
RegisterFile initialRF;
uint16_t numCycles = 0;

bool parseInputFile(char* file);

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
        while(getline(inputfile, line))
        {
            cout << line << endl;
        }
        inputfile.close();
        retVal = true;
    }
    else
    {
        cout << "Unable to open input file" << endl;
    }
    return retVal;
}

