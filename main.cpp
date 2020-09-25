#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include"read.cpp"
#include"sort.cpp"
#include"search.cpp"

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

    // Pregunta 3
    vector<string> source_names;

    Record object;

    for (int i = 0; i < records.size(); i++)
    {
        object = records[i];
        source_names.push_back(object.sourceName);
    }
    
    QuickSort<string> hello;
    
    hello.sort(source_names);
    
    Search<string> search(source_names);

    // ¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?
    string samuel = "samuel.reto.com";
    string jeffrey = "jeffrey.reto.com";
    string katherine = "katherine.reto.com";
    string betty = "betty.reto.com";
    string benjamin = "benjamin.reto.com";
    string raymond = "raymond.reto.com";

    if (search.binarySearch(samuel))
    {
        cout << "Una computadora pertenece a Samuel." << endl;
    }else
    {
        cout << "Ninguna computadora pertenece a Samuel." << endl;
    }
    
    
    if (search.binarySearch(jeffrey))
    {
        cout << "Una computadora pertenece a Jeffrey." << endl;
    }else
    {
        cout << "Ninguna computadora pertenece a Jeffrey." << endl;

    }
    

    if (search.binarySearch(katherine))
    {
        cout << "Una computadora pertenece a Katherine." << endl;
    }else
    {
        cout << "Ninguna computadora pertenece a Katherine." << endl;
    }
    

    if (search.binarySearch(betty))
    {
        cout << "Una computadora pertenece a Betty." << endl;
    }else
    {
        cout << "Ninguna computadora pertenece a Betty." << endl;
    }
    

    if (search.binarySearch(benjamin))
    {
        cout << "Una computadora pertenece a Benjamin." << endl;
    }else
    {
        cout << "Ninguna computadora pertenece a Benjamin." << endl;
    }
    

    if (search.binarySearch(raymond))
    {
        cout << "Una computadora pertenece a Raymond." << endl;
    }else
    {
        cout << "Ninguna computadora pertenece a Raymond." << endl;
    }
    

    
    return 0;
}