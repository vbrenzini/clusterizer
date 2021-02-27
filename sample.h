#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <sstream>

#define N 12
// #define DEBUG 1

using namespace std;

struct sample
{
    sample(string name) : mName(name) { reset(); }
    void reset();
    void setMarkerValues(string marker, vector<int> values); // set marker values
    bool operator==(sample &rhs);                            // comparison operator
    void print();                                            // debug print
    bool parseStream(stringstream &stream);                  // digest data from stream and set map accordingly
    vector<int> &getMarkerValues(string marker);             // get reference to a given a certain label

    string mSampleFile = "";                        // Sample File
    string mName;                                   // Name
    unordered_map<string, vector<int>> mMarkersMap; // Map of markers values

    bool mUsed = false; // is used?
};

inline bool sample::operator==(sample &rhs)
{
    bool isEqual = getMarkerValues("ANUCS501") == rhs.getMarkerValues("ANUCS501") &&
                   getMarkerValues("9269") == rhs.getMarkerValues("9269") &&
                   getMarkerValues("4910") == rhs.getMarkerValues("4910") &&
                   getMarkerValues("5159") == rhs.getMarkerValues("5159") &&
                   getMarkerValues("ANUCS305") == rhs.getMarkerValues("ANUCS305") &&
                   getMarkerValues("9043") == rhs.getMarkerValues("9043") &&
                   getMarkerValues("B05") == rhs.getMarkerValues("B05") &&
                   getMarkerValues("1528") == rhs.getMarkerValues("1528") &&
                   getMarkerValues("3735") == rhs.getMarkerValues("3735") &&
                   getMarkerValues("CS1") == rhs.getMarkerValues("CS1") &&
                   getMarkerValues("D02") == rhs.getMarkerValues("D02") &&
                   getMarkerValues("C11") == rhs.getMarkerValues("C11") &&
                   getMarkerValues("H06") == rhs.getMarkerValues("H06");

    return isEqual;
}

inline vector<int> &sample::getMarkerValues(string marker)
{
    vector<int> values(0);
    auto it = mMarkersMap.find(marker);
    if (it != mMarkersMap.end())
    {
        return it->second;
    }
    else
    {
        cerr << "Marker name not found" << endl;
        throw;
    }
}

inline void sample::setMarkerValues(string marker, vector<int> values) // set marker values
{
    getMarkerValues(marker) = values;
}

inline void sample::reset()
{
    mSampleFile = "";
    mName = "";

    mMarkersMap.insert(make_pair<string, vector<int>>("ANUCS501", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("9269", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("4910", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("5159", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("ANUCS305", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("9043", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("B05", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("1528", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("3735", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("CS1", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("D02", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("C11", vector<int>(N, -1)));
    mMarkersMap.insert(make_pair<string, vector<int>>("H06", vector<int>(N, -1)));

    mUsed = false;
}

inline void sample::print()
{
    cout << "Sample File: " << mSampleFile << endl;
    cout << "Sample Name: " << mName << endl;
    cout << "Markers: " << endl;
    for (auto &marker : mMarkersMap)
    {
        cout << " • " << setw(10) << marker.first;
        for (auto &value : marker.second)
        {
            if (value != -2)
            {
                cout << "\t" << value;
            }
            else
            {
                cout << "\t - ";
            }
        }
        cout << endl;
    }
}

inline bool sample::parseStream(stringstream &stream)
{
    string tmpFileName, tmpSampleName;
    stream >> tmpFileName >> tmpSampleName;
    if (mSampleFile == "" && mName == "")
    {
        // This is a new uninitialized sample object!
        mSampleFile = tmpFileName;
        mName = tmpSampleName;

        // Get subsequent data
        string tmpMarker;
        string tmpdye;
        vector<float> tmpValues(3 * N, -2);
        stream >> tmpMarker >> tmpdye;
        for (int iVal{0}; iVal < 3 * N; ++iVal)
        {
            stream >> tmpValues[iVal];
        }

        // Find marker:
        auto it = mMarkersMap.find(tmpMarker);
        if (it != mMarkersMap.end())
        {
            // Set values (every three tmpVals)
            for (int iVal{0}; iVal < N; ++iVal)
            {
                (it->second)[iVal] = (int)tmpValues[3 * iVal];
            }
        }
        else
        {
            cerr << "Marker name: " << tmpMarker << " not found" << endl;
            throw;
        }

        return true;
    }
    else
    {
        // This sample has already been initialized
        if (mSampleFile != tmpFileName || mName != tmpSampleName)
        {
#ifdef DEBUG
            cerr << "Stream data is incompatible with this sample!" << endl;
            cerr << "Filename: " << tmpFileName << " Samplename: " << tmpSampleName << endl;
            cerr << "Sample dump follows:" << endl;
            print();
#endif
            return false;
        }
        else
        {
            // Get subsequent data
            string tmpMarker;
            string tmpdye;
            vector<float> tmpValues(3 * N, -2);
            stream >> tmpMarker >> tmpdye;
            for (int iVal{0}; iVal < 3 * N; ++iVal)
            {
                stream >> tmpValues[iVal];
            }

            // Find marker:
            auto it = mMarkersMap.find(tmpMarker);
            if (it != mMarkersMap.end())
            {
                // Set values (every three tmpVals)
                for (int iVal{0}; iVal < N; ++iVal)
                {
                    (it->second)[iVal] = (int)tmpValues[3 * iVal];
                }
            }
            else
            {
                cerr << "Marker name: " << tmpMarker << " not found" << endl;
                throw;
            }

            return true;
        }
    }
}