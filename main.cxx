#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
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
    vector<float> tmpVec(N, -1.f);

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
#ifdef DEBUG
    cout << "Found " << samplesVector.size() << " samples" << endl;
    for (auto &sampleElem : samplesVector)
    {
        sampleElem.print();
    }
#endif
    // Actual clusterization
    vector<vector<sample>> sampleClusters;
    for (int iSample{0}; iSample < samplesVector.size(); ++iSample)
    {
        if (samplesVector[iSample].mUsed)
        {
            continue;
        }
        sampleClusters.push_back(vector<sample>{samplesVector[iSample]});
        samplesVector[iSample].mUsed = true;
        for (int jSample{0}; jSample < samplesVector.size(); ++jSample)
        {
            if ((iSample != jSample) && !samplesVector[jSample].mUsed)
            {
                if (samplesVector[iSample] == samplesVector[jSample])
                {
                    sampleClusters.back().push_back(samplesVector[jSample]);
                    samplesVector[jSample].mUsed = true;
                }
            }
        }
    }
    sort(sampleClusters.begin(), sampleClusters.end(), [](auto &i, auto &j) { return i.size() > j.size(); });

    // print results
    int counter{0};
    for (auto &cluster : sampleClusters)
    {
        cout << "Cluster " << counter << ": ";
        for (auto &s : cluster)
        {
            cout << s.mName << "\t";
        }
        ++counter;
        cout << endl;
    }
    return 0;
}