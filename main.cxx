#include <iostream>
#include <fstream>
#include <sstream>
#include "sample.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argv[1] == nullptr)
    {
        cerr << "Please provide input file" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream datafile(filename);
    cout << "Reading file: " << filename << endl;

    int row{0};
    vector<int> tmpVec(N, -1);

    string line;
    vector<sample> samplesVector;
    sample s{""}; // temporary sample
    while (getline(datafile, line))
    {
        if (row == 0)
        {
            line = ""; // skip first header (ugly)
        }
        else
        {
            stringstream iss(line);
            if (!s.parseStream(iss))
            {
                samplesVector.emplace_back(s);
                stringstream iss2(line);
                s.reset();
                s.parseStream(iss2);
            }
        }
        row++;
    }
    samplesVector.emplace_back(s); // push last sample
    cout << "Found " << samplesVector.size() << " samples" << endl;
    for (auto &sampleElem : samplesVector)
    {
        sampleElem.print();
    }
    return 0;
}