#include <string>
#include <vector>

using namespace std;

struct sample
{
    sample(string name) : mName(name){};

    // Name
    string mName;

    // Markers
    std::vector<int> mANUCS501;
    std::vector<int> m9269;
    std::vector<int> m4910;
    std::vector<int> m5159;
    std::vector<int> mANUCS305;
    std::vector<int> m9043;
    std::vector<int> mB05;
    std::vector<int> m1528;
    std::vector<int> m3735;
    std::vector<int> mCS1;
    std::vector<int> mD02;
    std::vector<int> mC11;
    std::vector<int> mH06;

    // comparison operator
    bool operator==(sample &rhs);
};

inline bool sample::operator==(sample &rhs)
{
    bool isEqual = mANUCS305 == rhs.mANUCS305 &&
                   m9043 == rhs.m9043 &&
                   mB05 == rhs.mB05 &&
                   m1528 == rhs.m1528 &&
                   m3735 == rhs.m3735 &&
                   mCS1 == rhs.mCS1 &&
                   mD02 == rhs.mD02 &&
                   mC11 == rhs.mC11 &&
                   mH06 == rhs.mH06;
    return isEqual;
}

/* Example
I_6	ANUCS501	B	4	2187	85.88	6	2819	96.84
I_6	9269	B	6	6226	128.74
I_6	4910	B	4	1317	164.32	10	1591	188.01												I_6	5159	B	6	3174	335.5																	I_6	ANUCS305	G	4	1658	140.27	8	2078	153.14											I_6	9043	G	3	4693	175.48																	I_6	B05	G	8	1773	239.27	9	2253	242.36													I_6	1528	G	7	2560	290.28																	I_6	3735	Y	3	2045	74.78	7	2303	92.08												I_6	CS1	Y	29	2172	281.47																		I_6	D02	R	6	2708	112.09																		I_6	C11	R	14	806	154.51	15	525	158.07															I_6	H06	R	7	1243	267.9	8	1102	270.98
*/