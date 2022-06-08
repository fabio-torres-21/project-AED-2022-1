#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include "../Graph/Algorithms/dfs.h"

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
    private: 
    public:
        bool insertVertex(string id, TV vertex);   
        bool createEdge(string id1, string id2, TE w);     
        bool deleteVertex(string id);     
        bool deleteEdge(string id1, string id2);   
        TE &operator()(string start, string end);  
        float density();
        bool isDense(float threshold = 0.5);
        bool isConnected();
        bool isStronglyConnected();
        bool empty();
        void clear();  
        void displayVertex(string id);
        bool findById(string id);
        void display();

    public:
        Vertex<TV, TE>* findVertex(string id);
        string findByVertex(Vertex<TV, TE>* v);
        Vertex<TV, TE>* findByData(TV data);
        TE getweigthEdge(string id1, string id2);
        unordered_map<string, Vertex<TV, TE>*> getVertexesMST(){
            return this->vertexes;
        }
};

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::insertVertex(string id, TV vertex)
{
    if (this->findById(id))
        return false;
    
    Vertex<TV, TE>* newVertex = new Vertex<TV, TE>;
    newVertex->id = id;
    newVertex->data = vertex;
    this->vertexes[id] = newVertex;
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w)
{
    if (!findById(id1) || !findById(id2))
        return false;

    Edge<TV, TE>* newEdge = new Edge<TV, TE>;
    newEdge->vertexes[0] = this->vertexes[id1];
    newEdge->vertexes[1] = this->vertexes[id2];
    newEdge->weight = w;
    this->vertexes[id1]->edges.push_back(newEdge);

    auto *newEdge1 = new Edge<TV, TE>;
    newEdge1->vertexes[1] = this->vertexes[id1];
    newEdge1->vertexes[0] = this->vertexes[id2];
    newEdge1->weight = w;

    this->vertexes[id2]->edges.push_back(newEdge1);
    this->edgesSize++;
    return true;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteVertex(string id)
{
    list<Edge<TV, TE>*> edges = this->vertexes[id]->edges;
    if (findById(id)) { 
        for (auto &e : edges)
            deleteEdge((*e).vertexes[0]->id,(*e).vertexes[1]->id); 
            
        this->vertexes.erase(id); 
        return true; 
    } return false; 
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::deleteEdge(string id1, string id2)
{
     if (findById(id1) && findById(id2)) {
        //eliminar arista de memeoria
        list<Edge<TV, TE>*> edges = this->vertexes[id1]->edges;
        for (auto& i :edges) {
            if ((*i).vertexes[0] == this->vertexes[id2] || (*i).vertexes[1] == this->vertexes[id2]) {
                this->vertexes[id1]->edges.remove(i);
            }
        }
        edges = this->vertexes[id2]->edges;
        for (auto& j :edges) 
            if ((*j).vertexes[0] == this->vertexes[id1] || (*j).vertexes[1] == this->vertexes[id1]) 
                this->vertexes[id2]->edges.remove(j);
        this->edgesSize--;
        return true;
    }
    return false;
}

template<typename TV, typename TE>
TE &UnDirectedGraph<TV, TE>::operator()(string start, string end)
{
    if (!findById(start) || !findById(end)) 
        throw("ERROR: ID of some vertex does not exist");

    list<Edge<TV, TE>*> edges = this->vertexes[start]->edges;

    for (auto i= edges.begin(); i!=edges.end(); i++)
        if ((*i)->vertexes[0] == this->vertexes[end] || (*i)->vertexes[1] == this->vertexes[end]) 
            return (*i)->weight;
    throw("ERROR: The vertex does not exist"); 
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::displayVertex(string id)
{
    if (findById(id)){
        Vertex<TV, TE>* vertex = this->vertexes[id];
        cout<<"ID: " << id <<endl;
        cout<<"Data: " << vertex->data <<endl;
        cout<<"Edges: { ";
        list<Edge<TV, TE>*> edges = this->vertexes[id]->edges;
        for (auto it = edges.begin(); it!=edges.end(); it++) 
            cout<<"("<< (*it)->vertexes[0]->id <<", "<< (*it)->vertexes[1]->id << "), ";
        cout<<" }"<<endl;

    } else
        throw("ERROR: The vertex does not exist");         
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::findById(string id)
{
    return !(this->vertexes.find(id) == this->vertexes.end());
}


template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::display()
{
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); it++) {
        cout<<"ID: " << (*it).first <<endl;
        cout<<"Data: " << (*it).second->data <<endl;
        cout<<"Edges: { ";
        list<Edge<TV, TE>*> edges = (*it).second->edges;
        for (auto it = edges.begin(); it!=edges.end(); it++)
            cout<<"("<< (*it)->vertexes[0]->id <<", "<< (*it)->vertexes[1]->id  <<", "<< (*it)->weight<< "), ";
        
        cout<<" }"<<endl;
        cout<<endl;
    }
}

template<typename TV, typename TE>
float UnDirectedGraph<TV, TE>::density()
{
    if( this->empty() ) throw "Graph is empty";
    
    float E = 0.0, V = 0.0;
    E = this->edgesSize;
    V = this->vertexes.size();
    return 2*E/(V*(V-1));
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isDense(float threshold) 
{
    return (density() >= threshold);
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::empty() 
{
    return (this->vertexes.size() == 0);
}

template<typename TV, typename TE>
void UnDirectedGraph<TV, TE>::clear() 
{
    while (!this->vertexes.empty()) {
        auto i = *this->vertexes.begin();
        deleteVertex(i.first);
    }
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isConnected()
{
    DFS<TV, TE> dfs(this, this->vertexes.begin()->first);
    auto vector = dfs.apply_dfs();
    if(vector.size() == this->vertexes.size())
        return true;
    else
        return false;
}

template<typename TV, typename TE>
bool UnDirectedGraph<TV, TE>::isStronglyConnected()
{
    throw("Not Applicable");
}


/*  ----------- PUBLIC FUNCTIONS ----------- */
template<typename TV, typename TE>
Vertex<TV, TE>* UnDirectedGraph<TV, TE>::findVertex(string id) 
{
    if ( findById(id) )
        return this->vertexes[id];
    else
        throw("ERROR: The vertex does not exist");         
}

template<typename TV, typename TE>
string UnDirectedGraph<TV, TE>::findByVertex(Vertex<TV, TE>* v) 
{
    for (auto itr = this->vertexes.begin(); itr != this->vertexes.end(); itr++) 
        if (itr->second == v) return itr->first;
    throw "Out of range";
}

template<typename TV, typename TE>
Vertex<TV, TE>* UnDirectedGraph<TV, TE>::findByData(TV data) 
{
    for (auto itr = this->vertexes.begin(); itr != this->vertexes.end(); itr++)
        if (itr->second->data == data) return itr->second;
    return nullptr;
}

template<typename TV, typename TE>
TE UnDirectedGraph<TV, TE>::getweigthEdge(string id1, string id2)
{
    // Se obtienen los vertices de la lista vertexes
    Vertex<TV, TE>* v1 = this->vertexes.at(id1);
    Vertex<TV, TE>* v2 = this->vertexes.at(id2);
    for (auto it = this->vertexes.begin(); it != this->vertexes.end(); it++) {
        list<Edge<TV, TE>*> edges = (*it).second->edges;
        for (auto it = edges.begin(); it!=edges.end(); it++) {
            if ( (((*it)->vertexes[0]->data == v1->data) &&
                    ((*it)->vertexes[1]->data == v2->data)) ||
                (((*it)->vertexes[1]->data == v1->data) &&
                    ((*it)->vertexes[0]->data == v2->data)) ) {
                return (*it)->weight;
            }
        }
    }
    return -1.5;
}

#endif