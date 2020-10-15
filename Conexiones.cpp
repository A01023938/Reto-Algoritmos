#include<iostream>
#include<stack>
#include<queue>

using namespace std;

template<class T>
class ComputerConnections
{
private:

    string IP;
    string name;
    stack<T> ConIN;     // Pila (Last In First Out)
    queue<T> ConOUT;    // Cola (First In First Out)
public:

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
        this->ConIN.push(value);
    }

    T getConnectionIN()
    {
        /* 
        Get first element in the stack. 
        */
        return this->ConIN.top();

    }

    void removeConnectionIN()
    {
        /*
        Remove the frist element in the stack.
        */
       this->ConIN.pop();

    }

    void addConnectionOUT(T value)
    {
        /*
        Add an element to the top of the stack, 
        remembering that this containter has FIFO
        structure (First In First Out).
        */

        this->ConOUT.push(value);
    }

    T getConnectionOUT()
    {
        /*
        Get first element in of the queue.
        */
        return this->ConOUT.top();
    }

};


int main()
{

    ComputerConnections<string> test("IP prueba", "Mateo");

    test.addConnectionIN("000.000.000.000");
    test.addConnectionIN("001.001.001.001");
    test.addConnectionIN("002.002.002.002");
    test.addConnectionIN("003.003.003.003");

    cout << test.getConnectionIN() << endl;

    test.removeConnectionIN();

    cout << test.getConnectionIN() << endl;

    

    return 0;
}