#include<iostream>
#include<vector>

using namespace std;

template <class T>
class Sort
{

public:
    virtual void sort(vector<T> &data) = 0;

    void exchange(vector<T> &data, int posI, int posJ)
    {
        T temp = data[posI];
        data[posI] = data[posJ];
        data[posJ] = temp;
    }
};

template <class T>
class MergeSort : public Sort<T>
{
public:

    void sort(vector<T> &data)
    {
        sortAux(data, 0, data.size() - 1);
    }

    void sortAux(vector<T> &data, int low, int high)
    {
        if(low >= high)
        {
            return;
        }
        int mid = (low + high)/2;
        sortAux(data, low, mid);
        sortAux(data, mid+1, high);
        merge(data, low, mid, high);
    }

    void merge(vector<T> &data, int low, int mid, int high)
    {
        int sizeA = mid - low + 1;
        int sizeB = high - mid;
        vector<T> copyA;
        vector<T> copyB;

        for (int i = 0; i < sizeA; i++)
        {
            copyA.push_back(data[low + 1]);
        }

        for (int i = 0; i < sizeB; i++)
        {
            copyB.push_back(data[mid + 1]);
        }
        
        int indexA = 0;
        int indexB = 0;
        int indexData = low;

        while (indexA < sizeA && indexB < sizeB)
        {
            if(copyA[indexA] < copyB[indexB])
            {
                data[indexData] = copyA[indexA];
                indexA++;
            }else
            {
                data[indexData] = copyB[indexB];
                indexB++;
            }
            indexData++;
        }

        while (indexA < sizeA)
        {
            data[indexData] = copyA[indexA];
            indexA++;
            indexData++;
        }
        while (indexB < sizeB)
        {
            data[indexData] = copyB[indexB];
            indexB++;
            indexData++;
        }
    }

};

template <class T>
class QuickSort: public Sort<T>{
	public:
	void sort(vector<T> &data){
		sortAux(data, 0, data.size()-1);
	}
	
	void sortAux(vector<T> &data, int low, int hi){
		if(low>=hi){
			return;
		}
		int j=partition(data, low, hi);//poner pivote en su lugar
		sortAux(data, low, j-1);//lado izquierdo
		sortAux(data, j+1, hi);//lado derecho
		
	}
	
	int partition(vector<T> &data, int low, int hi){
		int pivote=low;
		int i=low+1;
		int j=hi;
		while(true){
			while(data[i]<=data[pivote]&& i<hi){
				i++;
			}
			while(data[j]>data[pivote]&& j>low){
				j--;
			}
			if (i>=j){
				break;
			}else{
				this->exchange(data, i, j);
			}
		}
		this->exchange(data, pivote, j);
		return j;
	}
	
};