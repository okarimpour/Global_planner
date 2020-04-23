#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream> 
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <cassert>
#include <limits>
#include <list>

class Graph {
    public:
        Graph (int v);
        void addEdges (int u, int v, int weight);
        std::vector<int> Dijkstra (int start);
    private:
        int v;
        int INF = std::numeric_limits<int>::max(); //INT_MAX
        std::vector<std::list<std::pair<int, int> > > adj;
};

Graph::Graph (int v) {
    adj.resize(v);
}
void Graph::addEdges (int u, int v, int weight) {
    adj[u].push_back(std::make_pair(v, weight));
    adj[v].push_back(std::make_pair(u, weight));
}
std::vector<int> Graph::Dijkstra (int start) {
    std::vector<bool> visited(adj.size(), false);
    std::vector<int> distances(adj.size(), INF);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > pq;
    pq.push(std::make_pair(0, start));
    distances[start] = 0;

    while (!pq.empty()) {
        int u = (pq.top()).second;
        pq.pop();
        visited[u] = true;
        std::list<std::pair<int, int> >::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); it++) {
            int v = (*it).first;
            int w = (*it).second;
            if (visited[v] == false && distances[u] + w < distances[v]) {
                distances[v] = distances[u] + w;
                pq.push(std::make_pair(distances[v], v));
            }
        }
    }
    return distances;
}

int main () {
    int verteces = 9;

    Graph Graph(verteces);

    Graph.addEdges(0, 3, 5);
    Graph.addEdges(1, 3, 5);
    Graph.addEdges(1, 4, 1);
    Graph.addEdges(4, 5, 2);
    Graph.addEdges(2, 3, 6);
    Graph.addEdges(3, 5, 3);
    Graph.addEdges(2, 6, 6);
    Graph.addEdges(6, 7, 3);
    Graph.addEdges(3, 7, 2);
    Graph.addEdges(5, 7, 5);
    Graph.addEdges(5, 8, 4);
    Graph.addEdges(7, 8, 7);

    std::vector<int> dis = Graph.Dijkstra(0);

    printf("The minimum distances of each node from the start are consequently listed below: \n");
    for (int i = 0; i < dis.size(); i++) {
        printf("%d %d \n", i, dis[i]);
    }

    return 0;
}