#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "read.cpp"
#include "sort.cpp"
#include "Conexiones.cpp"

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

string FindFirstConnection(string IP_destination, string IP_source, vector<Record> records = records)
{
    string date = "--no date--";

    for (int i = 0; i < records.size(); i++)
    {
        if (records[i].sourceIP == IP_source && records[i].destinationIP == IP_destination)
        {
            date = records[i].date;
        }
    }
    return date;
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

    vector<string> d;

    for (int i = 0; i < records.size(); i++)
    {
        d.push_back(records[i].date);
    }

    QuickSort<string> sort;
    sort.sort(d);

    unordered_map<string, int> dates;
    string last_date = d[0];
    int numCon = 0;

    for (int i = 0; i < d.size(); i++)
    {
        if (d[i] != last_date)
        {
            pair<string, int> date(d[i], numCon);
            dates.insert(date);
            last_date = d[i];
            numCon = 0;
        }
        else
        {
            numCon++;
        }
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

    // Avance 3

    // IP Anomalos
    cout << "---- Nombres Anomalos ----" << endl;
    cout << endl;

    // IP: 122.210.219.145
    // Name: in6u9mmzf2o5dwr8o43l.ru

    // IP: 178.62.64.51  
    // Name: gncbrmxpm138gzbscrle.ru

    
    // Del los nombres de dominio encontrados en el paso anterior, ¿cuál es su ip? ¿Cómo determinarías esta información de la manera más optima en complejidad temporal?

    for (auto& i : ip_name)
    {
        if (i.second == "in6u9mmzf2o5dwr8o43l.ru" || i.second == "gncbrmxpm138gzbscrle.ru")
        {
            cout << "Name: " << i.second << endl;
            cout << "IP: " << i.first << endl;
            cout << endl;
        }
    }
    cout << "--------------------------" << endl;

    int unique_connections = 0;

    for (auto& i : ip_name)
    {
        if ((i.second.find("reto.com") != string::npos) && (CCDict[i.second].ConINSize() > 0))
        {
            unique_connections++;
        }
    }

    cout << endl;
    cout << "De las computadoras que pertenecen a 'reto.com' " << unique_connections << " de " << networkComputers.size() << " tienen una conexion entrante." << endl;
    cout << endl;

    cout << "Algunas de las computadoras que han sido accesadas son: " << endl;
    cout << endl;

    int sample = 0;
    for (auto& i : networkComputers)
    {
        if (CCDict[i.second].ConINSize() > 0)
        {
            cout << "Name: " << i.second << endl;
            cout << "IP: " << i.first << endl;
            cout << "Got accessed by " << CCDict[i.second].getConnectionIN() << "/" << ip_name[CCDict[i.second].getConnectionIN()] << " on ";
            for (int j = 0; j < records.size(); j++)
            {
                if ((records[j].destinationIP == i.first) && (records[j].sourceIP == CCDict[i.second].getConnectionIN()))
                {
                    cout << records[j].date <<endl;
                    break;
                }
                
            }
            while (CCDict[i.second].ConOUTSize() != 0)
            {
                string s = CCDict[i.second].getConnectionOUT();
                if ((s == "122.210.219.145") || (s == "178.62.64.51"))
                {
                    cout << "This computer connected to " << s << "/" << ip_name[s] << " on ";
                    for (int k = 0; k < records.size(); k++)
                    {
                        if ((records[k].destinationIP == s) && (records[k].sourceIP == i.first))
                        {
                            cout << records[k].date << endl;
                            cout << "Source Port: " << records[k].sourcePort << endl;
                            cout << "Destination Port: " << records[k].destinationPort << endl; 
                            cout << endl;
                            break;
                        }
                    }
                    cout << endl;
                    break;
                }
                
                CCDict[i.second].removeConnectionOUT();
            }
            
            sample++;   
        }

        if (sample == 10)
        {
            break;
        }
    }
    

    return 0;
}