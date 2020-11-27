#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include "read.cpp"
#include "Conexiones.cpp"
#include "grafo.cpp"

using namespace std;

vector<Record> records;

void read(string path)
{
    ifstream fileIn;
    fileIn.open(path);
    string line, parts;
    vector<string> values;
    while (fileIn.good())
    {
        getline(fileIn, line);

        istringstream sIn(line); // Stirng de entrda
        int i = 0;
        while (getline(sIn, parts, ','))
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

    // Avance Entrega 3

    unordered_set<string> ip;

    unordered_set<string> names;

    unordered_map<string, string> ip_name;

    for (int i = 0; i < records.size(); i++)
    {
        if (ip.find(records[i].sourceIP) == ip.end() && names.find(records[i].sourceName) == names.end())
        {
            ip.insert(records[i].sourceIP);
            names.insert(records[i].sourceName);
            pair<string, string> ipname(records[i].sourceIP, records[i].sourceName);
            ip_name.insert(ipname);
        }
        if (ip.find(records[i].destinationIP) == ip.end() && names.find(records[i].destinationName) == names.end())
        {
            ip.insert(records[i].destinationIP);
            names.insert(records[i].destinationName);
            pair<string, string> ipname(records[i].destinationIP, records[i].destinationName);
            ip_name.insert(ipname);
        }
    }

    // Computadoras que son parte de la compañia y su nombre contiene "reto.com"

    unordered_map<string, string> networkComputers;

    for (auto &i : ip_name)
    {
        if (i.second.find("reto.com") != string::npos)
        {
            pair<string, string> networkIP(i.first, i.second);
            networkComputers.insert(networkIP);
        }
    }

    // Las fechas y el numero de conexiones que tienen registradas

    set<string> d;

    for (int i = 0; i < records.size(); i++)
    {
        d.insert(records[i].date);
    }

    // Puertos de destino

    unordered_set<string> destinationPorts;

    for (int i = 0; i < records.size(); i++)
    {
        destinationPorts.insert(records[i].destinationPort);
    }

    // Conjunto de computadoras que no pertenzcan a dominio.reto.com

    unordered_map<string, string> destination_names_map;

    for (auto &i : ip_name)
    {
        if (i.second.find("reto.com") == string::npos)
        {
            pair<string, string> destinationNames(i.first, i.second);
            destination_names_map.insert(destinationNames);
        }
    }


    // Every name and their connections

    unordered_map<string, ComputerConnections<string>> CCDict;

    for (auto &i : ip_name)
    {
        ComputerConnections<string> IP(i.first, i.second);

        for (int j = 0; j < records.size(); j++)
        {
            if (records[j].sourceIP == i.first)
            {
                IP.addConnectionOUT(records[j].destinationIP);
            }
            if (records[j].destinationIP == i.first)
            {
                IP.addConnectionIN(records[j].sourceIP);
            }
        }
        pair<string, ComputerConnections<string>> PairIP(i.second, IP);
        CCDict.insert(PairIP);
    }

    // Avance 4


    // // Grafo de conexiones internas por dia

    vector<Graph<string>> graphConByDate;
    // // Por cada fecha
    // for (auto date : d)
    // {
    //     // Crea un grafo que contenga las conexiones de las computadoras internas que se hicieron
    //     Graph<string> conDayA;
        
    //     // Indica que dia es
    //     // cout << endl;
    //     // cout << date << endl;
    //     // cout << endl;

    //     // Iterar sobre los retos para buscar las conexiones que sucedieron ese dia
    //     for (int i = 0; i < records.size(); i++)
    //     {
    //         // La conexion tiene que ser de una computadora "reto.com" a una comutadora "reto.com" y la fecha tiene que ser la de ese dia
    //         if (records[i].sourceName.find("reto.com") != string::npos && records[i].destinationName.find("reto.com") != string::npos && records[i].date == date)
    //         {
    //             // Si el primer no esta en el grafo
    //             if (conDayA.nodos.find(records[i].sourceName) == conDayA.nodos.end())
    //             {
    //                 // Agregar el nodo
    //                 conDayA.agregarNodo(records[i].sourceName);
    //                 // cout << "Se agrego el nodo: " << records[i].sourceName << endl;

                
    //             }

    //             // Si el segundo no esta en el grafo
    //             if (conDayA.nodos.find(records[i].destinationName) == conDayA.nodos.end())
    //             {
    //                 // Agregar el nodo
    //                 conDayA.agregarNodo(records[i].destinationName);
    //                 // cout << "Se agrego el nodo: " << records[i].destinationName << endl;

    //             }

    //             // Si ya existe una conexion entre ambos
    //             if (conDayA.nodos[records[i].sourceName]->siguientes.find(conDayA.nodos[records[i].destinationName]) != conDayA.nodos[records[i].sourceName]->siguientes.end() )
    //             {
    //                 // modificarPeso(Nodo<T> *nodo, int nuevoPeso = 1)
    //                 conDayA.nodos[records[i].sourceName]->modificarPeso(conDayA.nodos[records[i].destinationName]);
    //                 // cout << "Se modifico el peso de " << records[i].sourceName << " a " << records[i].destinationName << " a ser " << conDayA.nodos[records[i].sourceName]->verPeso(conDayA.nodos[records[i].destinationName]) << endl;

    //             // Si no existe una conexion entre ambos
    //             }else
    //             {
    //                 conDayA.agregarArcoDirigido(records[i].sourceName, records[i].destinationName);
    //                 // cout << "Se realizo una conexion de " << records[i].sourceName << " a " << records[i].destinationName << " con un peso de " << conDayA.nodos[records[i].sourceName]->verPeso(conDayA.nodos[records[i].destinationName]) << endl;

    //             }
    //         }
    //     }

    //     graphConByDate.push_back(conDayA);  
    // }
    

    // int dates[10] = {10,11,12,13,14,17,18,20,21};

    // for (int i = 0; i < graphConByDate.size(); i++)
    // {
    //     cout << endl;
    //     cout << "Day: " << dates[i] << "-8-20" << endl;
    //     cout << endl;

    //     graphConByDate[i].verPesos();
    // }
    

    // Grafo de conexiones a paginas web

    // graphConByDate.clear();

    // Por cada fecha
    for (auto date : d)
    {
        // Crea un grafo que contenga las conexiones de las computadoras internas que se hicieron
        Graph<string> conDayA;

        // Iterar sobre los retos para buscar las conexiones que sucedieron ese dia
        for (int i = 0; i < records.size(); i++)
        {
            // La conexion tiene que ser de una computadora "reto.com" a una pagina web y la fecha tiene que ser la de ese dia
            if (records[i].sourceName.find("reto.com") != string::npos && records[i].destinationName.find("reto.com") == string::npos && records[i].date == date)
            {
                // Si el primer no esta en el grafo
                if (conDayA.nodos.find(records[i].sourceName) == conDayA.nodos.end())
                {
                    // Agregar el nodo
                    conDayA.agregarNodo(records[i].sourceName);
                    // cout << "Se agrego el nodo: " << records[i].sourceName << endl;

                
                }

                // Si el segundo no esta en el grafo
                if (conDayA.nodos.find(records[i].destinationName) == conDayA.nodos.end())
                {
                    // Agregar el nodo
                    conDayA.agregarNodo(records[i].destinationName);
                    // cout << "Se agrego el nodo: " << records[i].destinationName << endl;

                }

                // Si ya existe una conexion entre ambos
                if (conDayA.nodos[records[i].sourceName]->siguientes.find(conDayA.nodos[records[i].destinationName]) != conDayA.nodos[records[i].sourceName]->siguientes.end() )
                {
                    // modificarPeso(Nodo<T> *nodo, int nuevoPeso = 1)
                    conDayA.nodos[records[i].sourceName]->modificarPeso(conDayA.nodos[records[i].destinationName]);
                    // cout << "Se modifico el peso de " << records[i].sourceName << " a " << records[i].destinationName << " a ser " << conDayA.nodos[records[i].sourceName]->verPeso(conDayA.nodos[records[i].destinationName]) << endl;

                // Si no existe una conexion entre ambos
                }else
                {
                    conDayA.agregarArcoDirigido(records[i].sourceName, records[i].destinationName);
                    // cout << "Se realizo una conexion de " << records[i].sourceName << " a " << records[i].destinationName << " con un peso de " << conDayA.nodos[records[i].sourceName]->verPeso(conDayA.nodos[records[i].destinationName]) << endl;

                }
            }
        }

        graphConByDate.push_back(conDayA);  
    }
    

    int dates[10] = {10,11,12,13,14,17,18,19,20,21};

    for (int i = 0; i < graphConByDate.size(); i++)
    {
        cout << endl;
        cout << "Day: " << dates[i] << "-8-20" << endl;
        cout << endl;

        graphConByDate[i].checarCon("twitter.com");
    }

    /*
    Utilizando un grafo con las conexiones entre las ip de la red interna, determina la cantidad de computadoras con las que se ha conectado A por día. ¿Es el vértice que más conexiones salientes hacia la red interna tiene?

    10-8-2020 -> 0
    11-8-2020 -> 0
    12-8-2020 -> 0
    13-8-2020 -> 0
    14-8-2020 -> 31 Dia que ocurrio la infeccion y si es el vertice con mas conexiones
    17-8-2020 -> 0
    18-8-2020 -> 0
    19-8-2020 -> 0
    20-8-2020 -> 0
    21-8-2020 -> 0

    No existen computadoras que se conecten hacia A (carol.reto.com)

    Computadoras que se conectan a in6u9mmzf2o5dwr8o43l.ru por dia

    10-8-2020 -> 0
    11-8-2020 -> 0
    12-8-2020 -> 0
    13-8-2020 -> 0
    14-8-2020 -> 31 Dia que ocurrio la infeccion 
    17-8-2020 -> 31
    18-8-2020 -> 31
    19-8-2020 -> 31
    20-8-2020 -> 31
    21-8-2020 -> 31

    Computadoras que se conectan a gncbrmxpm138gzbscrle.ru

    10-8-2020 -> 0
    11-8-2020 -> 0
    12-8-2020 -> 0
    13-8-2020 -> 0
    14-8-2020 -> 1 Dia que ocurrio la infeccion 
    17-8-2020 -> 0
    18-8-2020 -> 0
    19-8-2020 -> 0
    20-8-2020 -> 0
    21-8-2020 -> 0
   
   Computadoras que se conectan a twitter.com

    10-8-2020 -> 7
    11-8-2020 -> 8
    12-8-2020 -> 11
    13-8-2020 -> 7
    14-8-2020 -> 5 Dia que ocurrio la infeccion 
    17-8-2020 -> 4
    18-8-2020 -> 30
    19-8-2020 -> 5
    20-8-2020 -> 6
    21-8-2020 -> 7

    */


    return 0;
}