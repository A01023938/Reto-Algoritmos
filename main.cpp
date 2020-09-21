#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include"read.cpp"

using namespace std;

vector<Record> records;

void read(string path)
{
    ifstream fileIn;
    fileIn.open(path);
    string line, parts;
    string values[8];
    while(fileIn.good())
    {
        getline(fileIn, line);
        
        istringstream sIn(line); // Stirng de entrda
        int i = 0;
        while(getline(sIn, parts, ','))
        {
            cout << i << endl;
            values[i] = parts;
            cout << values[i] << endl;
            i++;
        }

        cout << "Hello" << endl;

        // if (values[7].find('\r') != values[7].npos)
        // {
        //     values[7] = values[7].substr(0, values[7].size() - 1);
        // }

        cout << "hello 2" << endl;

        Record register_(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7]);
    
        records.push_back(register_);
        
        // values.clear();
        cout << "Done processing" << endl;
        break;
        
    }

};
int main()
{
    // Vector de records

    string path = "/mnt/c/Users/matug/documents/school/Semestre 3/Reto algoritmo/equipo3.csv";
    read(path);

    return 0;
}