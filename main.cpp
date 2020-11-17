#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
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


unordered_map<string, int> dayConnections(string date, vector<Record> r = records)
{
    unordered_map<string, int> dayC;

    for (int i = 0; i < r.size(); i++)
    {
        if (r[i].date == date && r[i].destinationName.find("reto.com") == string::npos && r[i].destinationName.find("-") == string::npos)
        {
            if (dayC.count(r[i].destinationName))
            {
                dayC[r[i].destinationName] += 1;
            }else
            {
                dayC[r[i].destinationName] = 1;                
            }
        }
    }
    
    return dayC;
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

    unordered_map<string, int> datesRecords;
    int num;
    for (auto i : d)
    {
        cout << "Date: " << i << endl;
        cout << endl;
        num = 0;
        datesRecords = dayConnections(i);
        for (auto j : datesRecords)
        {
            cout << j.first << " : " << j.second << endl;
        }
        datesRecords.clear();
        cout << endl;
    }

    
    
    

    return 0;
}