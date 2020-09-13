#include<fstream>
#include<string>


using namespace std;

#pragma once
class Record
{
private:
    string date;
    string hour;
    string fileName;
    
public:
    Record() = default;
    Record(string date, string hour, string fileName);

    void readFile(string path);
};




