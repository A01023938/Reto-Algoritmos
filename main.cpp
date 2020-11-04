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
#include "search.cpp"
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

    // Print comparison between the number of dates and the number of records
    /*

    int size = 0;
    for(auto& i : dates)
    {
        size += i.second; 
    }
    cout << records.size() << " : " << size << endl;

    */

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
    // Print destination names and their IP's
    /*

    for (auto& i : destination_names_map)
    {
        cout << i.first << "  ->  " << i.second << endl;
    }
    
    */

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

    // Imprime el diccionario que contiene el nombre de cada IP y cuantas conexiones entrantes y salientes tiene
    /*

    for (auto& i : CCDict)
    {
        cout << i.first << " Connections In Size: " << i.second.ConINSize() <<  " Connections Out Size: " << i.second.ConOUTSize() << endl;
    }

    */

    // Search by IP or by name

    /*
    bool search;
    char yes_no;

    cout << "Would you like to search a specific IP? Type 'Y' if yes and 'N' for no." << endl;
    cin >> yes_no;
    cout << endl;

    if (yes_no == 'Y' || yes_no == 'y')
    {
        search = true;
    }
    else
    {
        search = false;
    }

    while (search)
    {
        char input;

        cout << "Search by IP(1) or by URL(2)?" << endl;
        cout << "If you want to exit search please type '0'." << endl;
        cin >> input;
        cout << endl;

        if (input == '0')
        {
            break;
        }

        while ((input != '1') && (input != '2') && (input != '0'))
        {
            cout << "This is not a valid input, please type '1' to search by IP or '2' to search by URL." << endl;
            cin >> input;
            cout << endl;
        }

        // Search by IP
        if (input == '1')
        {
            string IP_search;

            cout << "Please type the IP that you would like to investigate." << endl;
            cin >> IP_search;
            cout << endl;

            while (IP_search != "exit" && ip_name.find(IP_search) == ip_name.end())
            {
                cout << "This IP does not match any IP in our data." << endl;
                cout << "Please enter another IP or type 'exit' to exit search by IP." << endl;
                cin >> IP_search;
                cout << endl;
            }

            cout << "Name: " << ip_name[IP_search] << endl;
            cout << "Connections IN: " << CCDict[ip_name[IP_search]].ConINSize() << endl;
            cout << "Connections OUT: " << CCDict[ip_name[IP_search]].ConOUTSize() << endl;

            if (ip_name[IP_search].find("reto.com") != string::npos)
            {
                cout << "This computer belongs to the 'reto.com' network. " << endl;

                if (CCDict[ip_name[IP_search]].ConINSize() > 0)
                {
                    cout << "Danger!" << endl;
                    while (CCDict[ip_name[IP_search]].ConINSize() != 0)
                    {
                        cout << "Recieved a connection from " << CCDict[ip_name[IP_search]].getConnectionIN() << " on " << FindFirstConnection("172.21.104.99", CCDict[ip_name[IP_search]].getConnectionIN()) << endl;
                        CCDict[ip_name[IP_search]].removeConnectionIN();
                    }
                }
            }
            else
            {
                string checkConnections;

                cout << endl;
                cout << "Would you like to check the connections IN and OUT of this IP? (Y/N)" << endl;
                cin >> checkConnections;

                if (checkConnections == "y" || checkConnections == "Y")
                {
                    cout << "Which connectios would you like to check (I)N or (O)UT?" << endl;
                    cin >> checkConnections;

                    if (checkConnections == "I" || checkConnections == "i")
                    {
                        while (CCDict[ip_name[IP_search]].ConINSize() > 0)
                        {
                            cout << "Recieved a connection from IP: " << CCDict[ip_name[IP_search]].getConnectionIN() << " Name: " << ip_name[CCDict[ip_name[IP_search]].getConnectionIN()] << endl;
                            CCDict[ip_name[IP_search]].removeConnectionIN();
                        }
                    }
                    if (checkConnections == "O" || checkConnections == "o")
                    {
                        while (CCDict[ip_name[IP_search]].ConOUTSize() > 0)
                        {
                            cout << "Recieved a connection from " << CCDict[ip_name[IP_search]].getConnectionOUT() << endl;
                            CCDict[ip_name[IP_search]].removeConnectionOUT();
                        }
                    }
                }
            }

            cout << endl;
        }
        if (input == '2')
        {
            string IP_search;

            cout << "Please type the URL that you would like to investigate." << endl;
            cin >> IP_search;
            cout << endl;

            while (IP_search != "exit" && CCDict.find(IP_search) == CCDict.end())
            {
                cout << "This URL does not match any URL in our data." << endl;
                cout << "Please enter another URL or type 'exit' to exit search by IP." << endl;
                cin >> IP_search;
                cout << endl;
            }

            for (auto& i : ip_name)
            {
                if (i.second == IP_search)
                {
                    cout << "IP: " << i.first << endl;
                    break;
                }
            }

            for (auto &i : CCDict)
            {
                if (i.first == IP_search)
                {
                    cout << "Connections IN: " << i.second.ConINSize() << endl;
                    cout << "Connections OUT: " << i.second.ConOUTSize() << endl;
                }
            }

            if (IP_search.find("reto.com") != string::npos)
            {
                cout << "This computer belongs to the 'reto.com' network. " << endl;

                if (CCDict[IP_search].ConINSize() > 0)
                {
                    cout << "Danger!" << endl;
                    while (CCDict[IP_search].ConINSize() != 0)
                    {
                        cout << "Recieved a connection from " << CCDict[IP_search].getConnectionIN() << " on " << FindFirstConnection("172.21.104.99", CCDict[IP_search].getConnectionIN()) << endl;
                        CCDict[IP_search].removeConnectionIN();
                    }
                }
            }

            cout << endl;
        }
    }

    */

    // Avance 3

    // IP Anomalos

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
        }
    }

    int unique_connections = 0;
    int badCon1 = 0;
    int badCon2 = 0;

    for (auto &i : networkComputers)
    {
        if (CCDict[i.second].ConINSize() > 0)
        {
            cout << "Name: " << i.second << endl;
            cout << "IP: " << i.first << endl;
            while (CCDict[i.second].ConINSize() != 0)
            {
                cout << "Recieved a connection from " << CCDict[i.second].getConnectionIN() << " at " << FindFirstConnection(i.first, CCDict[i.second].getConnectionIN()) << endl;
                CCDict[i.second].removeConnectionIN();
            }
            cout << endl;
            unique_connections++;
        }
        if (CCDict[i.second].ConOUTSize() > 0)
        {
            while (CCDict[i.second].ConOUTSize() != 0)
            {
                if (CCDict[i.second].getConnectionOUT() == "122.210.219.145")
                {
                    badCon1++;
                }
                if (CCDict[i.second].getConnectionOUT() == "178.62.64.51")
                {
                    badCon2++;
                }
                CCDict[i.second].removeConnectionOUT();
            }
            cout << "This computer connected to in6u9mmzf2o5dwr8o43l.ru " << badCon1 << " times." << endl;
            cout << "This computer connected to gncbrmxpm138gzbscrle.ru " << badCon2 << " times." << endl;
            cout << endl;
        }
    }

    cout << "Of the computers in the network, " << unique_connections << " of " << networkComputers.size() << " have been accessed. " << endl;
    cout << endl;

    /*

    Considerando el resultado de las preguntas 3 y 4, ¿Qué crees que este ocurriendo en esta red?

    La computadora carol.reto.com fue infectada y se conecto a todas las demas otras computadoras. 

    */



    

    return 0;
}