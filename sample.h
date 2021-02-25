#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#define N 12

using namespace std;

struct sample
{
    sample(string name) : mName(name) { reset(); }
    void reset();
    void setMarkerValues(string marker, std::vector<int> values); // set marker values
    bool operator==(sample &rhs);                                 // comparison operator

    string mName;                                   // Name
    unordered_map<string, vector<int>> mMarkersMap; // Map of markers values
    vector<int> &getMarkerValues(string marker);    // get reference to a given a certain label
    bool mUsed = false;                             // is used?
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
        cerr << "Marker name not found" << std::endl;
        throw;
    }
}

void sample::setMarkerValues(string marker, std::vector<int> values) // set marker values
{
    getMarkerValues(marker) = values;
}

void sample::reset()
{
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
};