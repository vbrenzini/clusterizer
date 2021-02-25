#include <iostream>
#include <fstream>
#include <sstream>
#include "sample.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argv[1] == nullptr)
    {
        std::cerr << "Please provide input file" << std::endl;
        return 1;
    }

    // std::string filename = argv[1];
    // ifstream datafile(filename);
    // std::cout << "Reading file: " << filename << std::endl;

    // int row{0};
    // while (!datafile.eof())
    // {
    //     if (!row)
    //     {
    //         std::string str;
    //         std::getline(datafile, str);
    //         std::stringstream ss(str);
    //         int col = 0;
    //         // while (ss >> my_array[row][col])
    //         // {
    //         //     col++;
    //         // }
    //         row++;
    //     }
    // }
    return 0;
}