#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"
#include <queue>
#include "../Utils/dfs.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{        
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
};

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::insertVertex(string id, TV vertex)
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
bool DirectedGraph<TV, TE>::createEdge(string id1, string id2, TE w)
{
    if (!this->findById(id1) || !this->findById(id2))
        return false;

    Edge<TV, TE>* newEdge = new Edge<TV, TE>;
    newEdge->vertexes[0] = this->vertexes[id1];
    newEdge->vertexes[1] = this->vertexes[id2];
    newEdge->weight = w;

    this->vertexes[id1]->edges.push_back(newEdge);
    this->edgesSize++;
    return true; 
}


template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteVertex(string id){
    if(!this->findById(id))
        return false;

    for(auto &v : this->vertexes) {
        auto edgesList = v.second->edges;
        for(auto &e : edgesList) {
            if((*e).vertexes[1] == this->vertexes[id]) {
                v.second->edges.remove(e);
                this->edgesSize--;
            }
        }
    }
    this->vertexes.erase(id);
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::deleteEdge(string id1, string id2) 
{
    if (findById(id1)) {
        list<Edge<TV, TE>*> edges = this->vertexes[id1]->edges;
        cout<<"s"<<endl;
        for (auto &it : edges){
            if ((*it).vertexes[1] == this->vertexes[id2]){
                this->vertexes[id1]->edges.remove(it);
                this->edgesSize--;
            }
        }
        return true;
    } else
        return false;
}

template<typename TV, typename TE>
TE &DirectedGraph<TV, TE>::operator()(string start, string end) 
{
    if (!findById(start) || !findById(end)) 
        throw("ERROR: ID of some vertex does not exist");

    list<Edge<TV, TE>*> edges = this->vertexes[start]->edges;
    for (auto i= edges.begin(); i!=edges.end(); i++){
        if ((*i)->vertexes[1] == this->vertexes[end])
            return (*i)->weight;
    }
    throw("ERROR: The vertex does not exist"); 
}

template<typename TV, typename TE>
float DirectedGraph<TV, TE>::density() {
    if( empty() ) throw "Graph is empty";
    float E = 0.0, V = 0.0;
    E = this->edgesSize;
    V = this->vertexes.size();
    return E/(V*(V-1));
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isDense(float threshold) 
{
    return (this->density() >= threshold);
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isConnected()
{
    return false;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::isStronglyConnected()
{
    for(auto it = this->vertexes.begin(); it != this->vertexes.end(); it++) {
        DFS<TV, TE> dfs2(this, it->first);
        auto vector = dfs2.apply_dfs();
        if(vector.size() != this->vertexes.size())
            return false;
    }
    return true;
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::empty()
{
    return (this->vertexes.size() == 0);
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::clear()
{
    for (auto &v : this->vertexes) {
        auto edgesList = v.second->edges;
        for (auto &e : edgesList) 
            delete e;
    }
    this->vertexes.clear();
    this->edgesSize = 0;

}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::displayVertex(string id)
{
    if (findById(id)){
        Vertex<TV, TE>* vertex = this->vertexes[id];
        cout<<"ID: " << id <<endl;
        cout<<"Data: " << vertex->data <<endl;
        cout<<"N Edges: "<< this->vertexes[id]->edges.size()<<endl;

        cout<<"Edges: { ";
        list<Edge<TV, TE>*> edges = this->vertexes[id]->edges;
        
        for (auto it = edges.begin(); it!=edges.end(); it++)
            cout<<"("<< (*it)->weight << ") ";
        cout<<" }"<<endl;
    } else
        throw("ERROR: The vertex does not exist");         
}

template<typename TV, typename TE>
bool DirectedGraph<TV, TE>::findById(string id)
{
    return !(this->vertexes.find(id) == this->vertexes.end()); 
}

template<typename TV, typename TE>
void DirectedGraph<TV, TE>::display()
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


#endif