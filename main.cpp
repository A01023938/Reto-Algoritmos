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
    vector<string> values;
    while(fileIn.good())
    {
        getline(fileIn, line);
        
        istringstream sIn(line); // Stirng de entrda
        int i = 0;
        while(getline(sIn, parts, ','))
        {
            values.push_back(parts);
        }

        if (values[7].find('\r') != values[7].npos)
        {
            values[7] = values[7].substr(0, values[7].size() - 1);
        }

        Record register_(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7]);
    
        records.push_back(register_);
        
        values.clear();        
    }

};
int main()
{
    // Vector de records

    string path = "/mnt/c/Users/matug/documents/school/Semestre 3/Reto algoritmo/equipo3.csv";
    read(path);

    int i = 0;
    Record first_date = records[0];
    Record next_date = records[i];

    // Primera pregunta: ¿Cuántos registros tiene tu archivo?
    cout << "Mi archivo contiene " << records.size() << " registros." << endl;
  
    while (first_date.date == next_date.date)
    {
        i++;
        next_date = records[i];
        
    }
    
    // Segunda pregunta: ¿Cuántos récords hay en el segundo día registrado? ¿Qué día es este?
    cout << "El segundo día en el registro es " << records[i].date << endl;

    first_date = records[i];
    next_date = records[i];

    while (first_date.date == next_date.date)
    {
        i++;
        next_date = records[i];
        
    }

    cout << "El segundo día de mi registro contiene " << i << " récords." << endl;


    return 0;
}