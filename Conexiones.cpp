#include<iostream>
#include<list>
#include<typeinfo>

using namespace std;

template<class T>
class ComputerConnections
{
private:

    string IP;
    string name;
    list<T> ConIN;     // Pila (Last In First Out)
    list<T> ConOUT;    // Cola (First In First Out)
public:

    ComputerConnections(){}

    ComputerConnections(string IP_, string name_)
    {
        this->IP = IP_;
        this->name = name_;
    }

    void addConnectionIN(T value)
    {
        /*
        Add an element to the top of the stack,
        remembering that this container has a FILO 
        structure (Last In First Out).
        */
        this->ConIN.push_front(value);
    }

    T getConnectionIN()
    {
        /* 
        Get first element in the stack. 
        */
       if(this->ConINSize() != 0)
       {
            return this->ConIN.front();
       }else
       {
           return "There are no elements in the stack";
       }

    }

    void removeConnectionIN()
    {
        /*
        Remove the frist element in the stack.
        */
       this->ConIN.pop_front();

    }

    void addConnectionOUT(T value)
    {
        /*
        Add an element to the top of the queue, 
        remembering that this containter has LIFO
        structure (Last In First Out).
        */

        this->ConOUT.push_back(value);
    }

    T getConnectionOUT()
    {
        /*
        Get first element in of the queue.
        */
        if(this->ConOUT.size() != 0)
        {
            return this->ConOUT.front();
        }else
        {
            return "There are no elements in the queue";
        }
        
        
    }

    void removeConnectionOUT()
    {
        /*
        Remove the first element from the queue.
        */
       this->ConOUT.pop_front();
    }

    int ConINSize()
    {
        /*
        Returns the size of ConIN.
        */ 
        return this->ConIN.size();
        
    }

    int ConOUTSize()
    {
        /*
        Returns the size of ConOUT.
        */
        return this->ConOUT.size();        
    }

};

