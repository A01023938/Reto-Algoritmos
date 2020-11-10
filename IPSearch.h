#include <iostream>
#include <unordered_map>

using namespace std;

void SearchIP_Name(unordered_map<string, string> ip_name, unordered_map<string, ComputerConnections> CCDict)
{

    while (true)
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
}