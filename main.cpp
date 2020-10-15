#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include"read.cpp"
#include"sort.cpp"
#include"search.cpp"
#include"Conexiones.cpp"

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

    string path = "/mnt/c/Users/matug/documents/school/Semestre 3/Reto algoritmo/datos.csv";
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
    
    // Pregunta 4
    
    vector<string> source_IP;

    for (int i = 0; i < records.size(); i++)
    {
        object = records[i];
        source_IP.push_back(object.sourceIP);
    }

    hello.sort(source_IP);

    cout << "La dirección IP interna de la compañia es 172.21.104 seguido de un identificador de la computadora dentro de la red." << endl;

    // for (int i = 1000; i < 1100; i++)
    // {
    //     cout << source_IP[i] << endl;
    // }

    // Pregunta 5 ¿Alguna computadora se llama server.reto.com?

    if (search.binarySearch("server.reto.com"))
    {
        cout << "Si existe una computadora que se llame server.reto.com." << endl;
    }else
    {
        cout << "No existe una computadora que se llame server.reto.com." << endl;
    }

    source_names.clear();
    
    // Pregunta 6 ¿Qué servicio de mail utilizan de todos estos: gmail.com, outlook.com, protonmail.com, freemailserver.com?

    vector<string> destination_names;

   for (int i = 0; i < records.size(); i++)
    {
        object = records[i];
        destination_names.push_back(object.destinationName);
    }

    hello.sort(destination_names);

    Search<string> search_2(destination_names);
    

    if (search_2.binarySearch("gmail.com"))
    {
        cout << "Los empleados de la compañia usan gmail.com." << endl;
    }

    if (search_2.binarySearch("outlook.com"))
    {
        cout << "Los empleados de la compañia usan outlook.com." << endl;
    }

    if (search_2.binarySearch("protonmail.com"))
    {
        cout << "Los empleados de la compañia usan protonmail.com." << endl;
    }

    if (search_2.binarySearch("freemailserver.com"))
    {
        cout << "Los empleados de la compañia usan freemailserver.com." << endl;
    }


    // Pregunta 7 Considerando solamente los puertos destino ¿Qué puertos abajo del 1000 se están usando? Lista los puertos e investiga que aplicación/servicio lo utiliza generalmente.

    vector<string> destination_ports;
    vector<string> good_ports;

    for (int i = 0; i < records.size(); i++)
    {
        object = records[i];
        destination_ports.push_back(object.destinationPort);
    }

    hello.sort(destination_ports);

    for (int i = 0; i < destination_ports.size(); i++)
    {
        if (find(good_ports.begin(),good_ports.end(), destination_ports[i]) != good_ports.end())
        {
            
        }else
        {
            if (destination_ports[i] != "-")
            {
                if (stoi(destination_ports[i]) < 1000)
                {
                    good_ports.push_back(destination_ports[i]);
                }
            }
        }
    }
    
    for (int i = 0; i < good_ports.size(); i++)
    {
        cout << good_ports[i] << endl;
    }
    

    return 0;
}