#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include "DirectedGraph.h"
#include "UndirectedGraph.h"
#include <queue>

template <typename TV, typename TE>
class BFS
{
    public:
        UnDirectedGraph<TV, TE> *graph1;
        DirectedGraph<TV, TE> *graph2;
        std::unordered_map<std::string, Vertex<TV, TE> *> vertexes;
        string start_id;

        BFS(UnDirectedGraph<TV, TE> *graph, string id);
        BFS(DirectedGraph<TV, TE> *graph, string id);
        vector<Vertex<TV, TE> *> apply_bfs();
};

template <typename TV, typename TE>
BFS<TV, TE>::BFS(UnDirectedGraph<TV, TE> *graph, string id)
{
    vertexes = graph1->getVertexes(graph);
    this->graph1 = graph;
    this->start_id = id;
}

template <typename TV, typename TE>
BFS<TV, TE>::BFS(DirectedGraph<TV, TE> *graph, string id)
{
    vertexes = graph2->getVertexes(graph);
    this->graph2 = graph;
    this->start_id = id;
}

template <typename TV, typename TE>
vector<Vertex<TV, TE> *> BFS<TV, TE>::apply_bfs()
{
    vector<Vertex<TV, TE> *> result;

    unordered_map<Vertex<TV, TE> *, bool> visited;
    auto it = this->vertexes.begin();
    for (it;it != this->vertexes.end(); it++)
    {
        visited[it->second] = false;
    }

    std::list<Vertex<TV, TE> *> queue;
    visited[this->vertexes[this->start_id]] = true;

    queue.push_back(this->vertexes[this->start_id]);

    while (!queue.empty())
    {
        Vertex<TV, TE> *s = queue.front();
        result.push_back(s);
        queue.pop_front();

        for (auto it2 = s->edges.begin(); it2 != s->edges.end(); it2++)
        {
            if (!visited[(*it2)->vertexes[1]])
            {
                visited[(*it2)->vertexes[1]] = true;
                queue.push_back((*it2)->vertexes[1]);
            }
            if (!visited[(*it2)->vertexes[0]])
            {
                visited[(*it2)->vertexes[0]] = true;
                queue.push_back((*it2)->vertexes[0]);
            }
        }
    }
    return result;
}

#endif /* BFS_H */