#include <iostream> 
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

template <class T>
class Nodo{
	public:
	T value;
	bool visited;
	unordered_map<Nodo<T> *, int> siguientes;
	
	Nodo(T val){
		value=val;
		visited=false;
	}
	
	void agregarArcoDirigidoConPeso(Nodo<T> *sig, int peso){
		if(siguientes.find(sig)==siguientes.end()){
			siguientes[sig]=peso;
		}
	}
	
	void agregarArcoDirigido(Nodo<T> *sig){
		agregarArcoDirigidoConPeso(sig, 1);
	}
	
	void imprimirNodo(){
			cout<<value<<":";
			for(auto nodoSiguiente:siguientes){
				cout<<nodoSiguiente.first->value<<","<<nodoSiguiente.second<<";";
			}
			cout<<endl;
	}
	
	// bool conexion(Nodo<T> *nodo){
	// }
	int regresarPeso(Nodo<T> *nodo)
	{
		return siguientes[nodo];
	}
	
	void verPeso()
	{
		int n = siguientes.size();
		cout << n << endl;;
	}

	int checarCon(string name)
	{
		int n = 0; // Numero de veces que se ha conectado a <name>
		for (auto next : siguientes)
		{
			if (next.first->value == name)
			{
				n += 1;
			}
		}
		return n;
	}

	void modificarPeso(Nodo<T> *nodo, int nuevoPeso = 1){
        siguientes[nodo]+= nuevoPeso;
	}
};


template <class T>
class Graph{
	public:
	unordered_map<T, Nodo<T> *> nodos;
	
	void agregarNodo(T value){
		if(nodos.find(value)==nodos.end()){
			Nodo<T> *nuevo=new Nodo<T>(value);
			nodos[value]=nuevo;
		}
	}
	
	void agregarArcoDirigidoConPeso(T nodo1, T nodo2, int peso){
		if(nodos.find(nodo1)!=nodos.end() && nodos.find(nodo2)!=nodos.end()){
			nodos[nodo1]->agregarArcoDirigidoConPeso(nodos[nodo2], peso);
		}			
	}
	
	void agregarArcoDirigido(T nodo1, T nodo2){
		agregarArcoDirigidoConPeso(nodo1, nodo2, 1);
	}
	
	void agregarArcoConPeso(T nodo1, T nodo2, int peso){
		agregarArcoDirigidoConPeso(nodo1, nodo2, peso);
		agregarArcoDirigidoConPeso(nodo2, nodo1, peso);
	}
	
	void agregarArco(T nodo1, T nodo2){
		agregarArcoConPeso(nodo1, nodo2, 1);
	}
	
	void imprimirGrafo(){
		for(auto parValorNodo: nodos){
			parValorNodo.second->imprimirNodo();
		}
	}

	void verPesos(){
		for (auto nodo : nodos)
		{
			cout << nodo.first << " : ";
			nodo.second->verPeso();
		}
		
	}

	void checarCon(string name)
	{
		int n = 0;
		for (auto nodo : nodos)
		{
			n += nodo.second->checarCon(name);
		}

		cout << n << " computadoras se han conectado a " << name << endl;
		
	}
	
	/*void modificar(T nodo1, T nodo2, int nuevoPeso){
		//Encontrar que existan
		//buscar si existe el arco nodo1-nodo2 y modificarlo
	}*/

    bool DFS(T v1, T v2)
    {
        stack<T> porVisitar;
        
		porVisitar.push(v1);
		while (porVisitar.size() != 0)
		{
			if (porVisitar.top() == v2)
			{
				return true;
			}else
			{
				porVisitar.pop();
				for (auto next : nodos[v1]->siguientes)
				{
					porVisitar.push(next.first->value);
				}
				v1 = porVisitar.top();
			}
		}
		return false;
    }

	bool BFS(T v1, T v2)
	{
		queue<T> porVisitar;
		
		porVisitar.push(v1);
		while (porVisitar.size() != 0)
		{
			if (porVisitar.front() == v2)
			{
				return true;
			}else
			{
				porVisitar.pop();
				for (auto next : nodos[v1]->siguientes)
				{
					porVisitar.push(next.first->value);
				}
				v1 = porVisitar.front();
			}
			
		}
		return false;
		
	}
};