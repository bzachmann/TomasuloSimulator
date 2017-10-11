#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "Usage: " << argv[0] << " <Input File>" << endl;
    }
    else
    {
        string line;
        ifstream inputfile (argv[1]);
        if(inputfile.is_open())
        {
            while(getline(inputfile, line))
            {
                cout << line << endl;
            }
            inputfile.close();
        }
        else
        {
            cout << "Unable to open input file" << endl;
        }
    }

    return 0;
}
