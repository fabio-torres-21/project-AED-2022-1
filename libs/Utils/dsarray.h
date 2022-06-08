#ifndef DSARRAY_H
#define DSARRAY_H

#include "ds.h"

template <typename T>
class DisjoinSetArray: public DisjoinSet<T>
{
    private:
        T* data;
        int* parent;
        int* rank;
        int n;
        int unionCounter;

    public:
        DisjoinSetArray(vector<T> data);
        void MakeSet(int x); //MakseSet the element with index x
        void MakeSet(); //MakseSet all elements
        int Find(int x); //Find the root of x (with optimization)
        void Union(int x, int y); //Union two sets represented by x and y (apply rank)
        bool isConnected(int x, int y); //check whether there is a path between x and y
        int size(); //total number of elements
        int sets(); //number of sets
        int size(int x); //total number of elements that belong to the set of x
        void add(T element, int x); //add the element to the set of x
        vector<T> getElementsSet(int x); //return all elements that belong to the set of x
};

template <typename T>
DisjoinSetArray<T>::DisjoinSetArray(vector<T> data)
{
    this-> n = data.size();
    this->unionCounter = 0;

    this->data = new T[data.size()];
    this->rank = new int[data.size()];
    this->parent = new int[data.size()];

    for (int i = 0; i < data.size(); i++)
        this->data[i] = data[i];

    MakeSet();
}

template <typename T>
void DisjoinSetArray<T>::MakeSet(int x)
{
    this->parent[x] = x;
    this->rank[x] = 0;
}

template <typename T>
void DisjoinSetArray<T>::MakeSet()
{
    for (int i = 0; i < n; i++){
        this->parent[i] = i;
        this->rank[i] = 0;
    }
}

template <typename T>
int DisjoinSetArray<T>::Find(int x)
{
    if(x < 0 || x >= this->n) throw("Error");

    if (x == parent[x]) return x;
    return Find(parent[x]);
}

template <typename T>
void DisjoinSetArray<T>::Union(int x, int y)
{
    int xrep = Find(x); 
    int yrep = Find(y);

    if (xrep == yrep) return; 

    if (rank[xrep] < rank[yrep])
        parent[xrep] = yrep; 
    else if (rank[xrep] > rank[yrep])
        parent[yrep] = xrep;
    else { 
        parent[yrep] = xrep; 
        rank[xrep]++; 
    } 
    unionCounter++;
}

template <typename T>
bool DisjoinSetArray<T>::isConnected(int x, int y)
{
    return (Find(x) == Find(y));
}

template <typename T>
int DisjoinSetArray<T>::size()
{
    return n;
}

template <typename T>
int DisjoinSetArray<T>::sets()
{
    return (n- unionCounter);
}

template <typename T>
int DisjoinSetArray<T>::size(int x)
{
    int localSize = 0;
    for (int i = 0; i < n; i++)
        if (x == parent[i])
            localSize++;

    return localSize;
}

template <typename T>
void DisjoinSetArray<T>::add(T element, int x)
{
    return;
}

template <typename T>
vector<T> DisjoinSetArray<T>::getElementsSet(int x)
{
    vector<T> sets;
    int xrep = Find(x);
    for (int i = 0; i < n; i++) 
        if (xrep == parent[i])
            sets.push_back(data[i]);

    return sets;
}

#endif /* DSARRAY_H */