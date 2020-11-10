#include<iostream>

using namespace std;

class Record
{
public:
    string date;
    string hour;
    string sourceIP;
    string sourcePort;
    string sourceName;
    string destinationIP;
    string destinationPort;
    string destinationName;
    
    Record()
    {
        date = ""; 
        hour = "";
        sourceIP = "";
        sourcePort = "";
        sourceName = "";
        destinationIP = "";
        destinationPort = "";
        destinationName = "";
    }

    Record(string date_, string hour_, string sourceIP_, string sourcePort_, string sourceName_, string destinationIP_, string destinationPort_, string destinationName_)
    {
        date = date_; 
        hour = hour_;
        sourceIP = sourceIP_;
        sourcePort = sourcePort_;
        sourceName = sourceName_;
        destinationIP = destinationIP_;
        destinationPort = destinationPort_;
        destinationName = destinationName_;
    }

    void print()
    {
        cout << date << endl;
        cout << hour << endl;
        cout << sourceIP << endl;
        cout << sourcePort << endl;
        cout << sourceName << endl;
        cout << destinationIP << endl;
        cout << destinationPort << endl;
        cout << destinationName << endl;

    }

};




