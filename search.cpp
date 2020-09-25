#include <iostream>
#include<vector>

using namespace std;

template <class T>
class Search
{
public:
    vector<T> list;
    // Default constructor
    Search() = default;

    // Constructor
    Search(vector<T> list_)
    {
        list = list_;
        
    }
    // Binary Search
    int binarySearch(T searchedItem)
    {
        int start = 0;
        int end = list.size() - 1;

        if(searchedItem > list[end] || searchedItem < list[start])
        {
            return 0;
        }

        while (end >= start)
        {
            int half = (start + end)/2;

            if(list[half] == searchedItem)
            {
                return half;
            }
            else if (searchedItem > list[half])
            {
                start = half + 1;
            }
            else
            {
                end = half - 1;
            }
        }
        return 0;
    }

    // Busqueda binaria (recursiva)
    int binarySearchRecursive(T searchedItemP, int start, int end)
    {
        if(end<start)
        {
            return -1;
        }

        int half = (start + end)/2; // Regardles of the type of data that is "T" half would always be an integer

        if(list[half]==searchedItemP)
        {
            return half;
        }
        else if (searchedItemP>list[half]) // If the searched item is greater than the item located at the middle then search form the middle to the top
        {
            return binarySearchRecursive(searchedItemP, half+1, end);
        }
        else // If not search form the beggining to end
        {
            return binarySearchRecursive(searchedItemP, start, half-1);
        }
    }

    int sequencialSearch2(T searchedItem)
    {
        int step = 2;
        int start = 0;
        int end = list.size();

        while (start < list.size())
        {
            end = start + step;

            if(end > list.size())
            {
                end = list.size();
            }
            if(list[end - 1] >= searchedItem)
            {
                for (int i = 0; i < end; i++)
                {
                    if(list[i] == searchedItem)
                    {
                        return i;
                    }
                }
                return -1;
            }
            start = end;
        }
        return -1;
    }

};