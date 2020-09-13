#include<sstream>
#include"read.h"

Record::Record(string date, string hour, string fileName)
{
    this->date = date; 
    this->hour = hour;
    this->fileName = fileName;
}

void Record::readFile(string path)
{
    ifstream fileIn;
    fileIn.open(path); // Open file

    string line, parts; // Line would represent a whole line of csv and parts would represent each individual value

    while (fileIn.good())
    {
        getline(fileIn, line);
        istringstream sIn(line);
        
        while (getline(line, sIn, ','))
        {
            std::cout << (sIn) << endl;
        }
        break;   
    }
}

