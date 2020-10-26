#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
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

    unordered_map<string, string>  networkComputers;

    for (auto& i : ip_name)
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
    string last_date =  d[0];
    int numCon = 0;

    for (int i = 0; i < d.size(); i++)
    {
        if (d[i] != last_date)
        {
            pair<string, int> date(d[i], numCon);
            dates.insert(date);
            last_date = d[i];
            numCon = 0;
        }else
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

    unordered_map<string, string> destination_names_set;

    for (auto& i : ip_name)
    {
        if (i.second.find("reto.com") == string::npos)
        {
            pair<string, string> destinationNames(i.first, i.second);
            destination_names_set.insert(destinationNames);
        }
        
    }
    // Print destination names and their IP's
    /*

    for (auto& i : destination_names_set)
    {
        cout << i.first << "  ->  " << i.second << endl;
    }
    
    */

   unordered_map< string, ComputerConnections<string> > CCDict;

   for (auto& i : ip_name)
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
       pair<string, ComputerConnections<string> > PairIP (i.second, IP);
       CCDict.insert(PairIP);
   }
   
    for (auto& i : CCDict)
    {
        cout << i.first << " Connections In Size: " << i.second.ConINSize() <<  " Connections Out Size: " << i.second.ConOUTSize() << endl;
    }
    

    // for (int i = 0; i < records.size(); i++)
    // {
    //     if (records[i].destinationName.find("reto.com") == string::npos && records[i].destinationName.find("-") == string::npos)
    //     {
    //         destination_names_set.insert(records[i].destinationName);
    //     }
        
    // }

    // for (int i = 0; i < records.size(); i++)
    // {
    //     if(records[i].destinationIP.find("-") == string::npos)
    //     {
    //         ip.insert(records[i].destinationIP);
    //     }
        
    //     if(records[i].sourceIP.find("-") == string::npos)
    //     {
    //         ip.insert(records[i].sourceIP);
    //     }
    // }
    
    // for (auto i = ip.begin(); i != ip.end(); i++)
    // {

    //     ComputerConnections<string> IP(*i, *i);

    //     for (int j = 0; j < records.size(); j++)
    //     {
    //         if (records[j].sourceIP == *i)
    //         {
    //             IP.addConnectionOUT(records[j].destinationIP);
    //         }
    //         if (records[j].destinationIP == *i)
    //         {
    //             IP.addConnectionIN(records[j].sourceIP);
    //         }
    //     }

    //     pair<string, ComputerConnections<string> > PairIP (*i, IP);
        
    //     CCDict.insert(PairIP);

    // }
    
    
    // unordered_set<string>::iterator bad_page1 = destination_names_set.find("in6u9mmzf2o5dwr8o43l.ru");
    // unordered_set<string>::iterator bad_page2 = destination_names_set.find("gncbrmxpm138gzbscrle.ru");

    // string badip1;
    // string badip2;

    // for (int i = 0; i < records.size(); i++)
    // {
    //     if (records[i].destinationName == "in6u9mmzf2o5dwr8o43l.ru")
    //     {
    //         badip1 = records[i].destinationIP;
    //         break;
    //     }
    // }
    
    
    // for (int i = 0; i < records.size(); i++)
    // {
    //     if (records[i].destinationName == "gncbrmxpm138gzbscrle.ru")
    //     {
    //         badip2 = records[i].destinationIP;
    //         break;
    //     }
    // }

    // if (bad_page1 != destination_names_set.end())
    // {
    //     cout << "Our first supicious page is " << *bad_page1 << " and its ip is " << badip1 << endl;
    // }

    // if (bad_page1 != destination_names_set.end())
    // {
    //     cout << "Our first supicious page is " << *bad_page2 << " and its ip is " << badip2 << endl;
    // }
    

    // cout << endl;
    // int num;
    // cout << "Please choose a computer to examine. Remember that the computer ID must be between 1 and 150" << endl;
    // cout << "172.21.104.";
    // cin >> num;
    // while (num < 1 || num > 150)
    // {
    //     cout << "This number is not between 1 and 150. Please choose another number." << endl;
    //     cout << "172.21.104.";
    //     cin >> num;
    // }
    
    // string Using_IP = "172.21.104." + to_string(num);
    
    // ComputerConnections<string> GeneratedIP(Using_IP, "IP Generada por el usuario");

    // // date-hour-SourceIP-SourcePort-SourceName-destinationIP-destinationPort-destinationName


    // for (int i = 0; i < records.size(); i++)
    // {
    //     // The computer connected somewhere
    //     if(records[i].sourceIP == Using_IP)
    //     {
    //         // To which places our computer has connected
    //         GeneratedIP.addConnectionOUT(records[i].destinationIP);
    //     }
    //     // Another computer connected to our IP
    //     if(records[i].destinationIP == Using_IP)
    //     {
    //         // Add the computer IP that connected to our computer
    //         GeneratedIP.addConnectionIN(records[i].sourceIP);
    //     }
    // }
    // cout << "This computer has connected to " << GeneratedIP.ConOUTSize() << " IPs." << endl;
    // cout << "This computer was accessed " << GeneratedIP.ConINSize() << " time(s)." << endl;
    // cout << endl;
    // cout << "===============================================================================================" << endl;
    // cout << endl;
    // cout << "The computer with the IP '172.21.104.99' has connected to many other computers in our network." << endl;
    // cout << endl;
    // ComputerConnections<string> PossibleAttack("172.21.104.99", "Possible Attack");

    // for (int i = 0; i < records.size(); i++)
    // {
    //     // The computer connected somewhere
    //     if(records[i].sourceIP == "172.21.104.99")
    //     {
    //         // To which places our computer has connected
    //         PossibleAttack.addConnectionOUT(records[i].destinationIP);
    //     }
    //     // Another computer connected to our IP
    //     if(records[i].destinationIP == "172.21.104.99")
    //     {
    //         // Add the computer IP that connected to our computer
    //         PossibleAttack.addConnectionIN(records[i].sourceIP);
    //     }
    // }


    // cout << "Its last connection was made to the IP " << PossibleAttack.getConnectionOUT() << endl;
    // cout << "It was accessed last by " << PossibleAttack.getConnectionIN() << endl;
    // cout << "It connected to " << PossibleAttack.ConOUTSize() << " IPs" << endl;
    // cout << "It was accessed " << PossibleAttack.ConINSize() << " time(s)" << endl;

    // string last_connection = "000.000.000.000";
    // int n = 0;
    // while (PossibleAttack.ConOUTSize() != 0)
    // {
    //     if(PossibleAttack.getConnectionOUT() == last_connection)
    //     {
    //         num += 1;
    //         if (num == 3)
    //         {
    //             cout << "It made 3 consequently connections to " << last_connection << endl;
    //         }            
    //     }else
    //     {
    //         num = 0;
    //     }
    //     last_connection = PossibleAttack.getConnectionOUT();
    //     PossibleAttack.removeConnectionOUT();
    // }
    // cout << endl;
    // cout << "===============================================================================================" << endl;


    // for (int i = 0; i < records.size(); i++)
    // {
    //     if(records[i].destinationIP == "122.210.219.145")
    //     {
    //         cout << records[i].destinationName << endl;
    //         break;
    //     }
    // }
    
    // Bad IPs
    // 122.210.219.145
    
    // Good IPs
    // 161.229.35.160 gmail.com
    // 201.65.34.164 twitter.com
    // 36.160.190.27 microsoft.com
    
    /*
    To do list:
    - Make a dictionary that has the Ip address and an object Computer connections
    - Investigate bad Ip's
    */

    return 0;
}