#include "dijkstras.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    previous.resize(n,-1);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push(Edge(source, 0));
    distance[source] = 0;
    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();
        int u = current.src;
        if (visited[u]) {continue;}
        visited[u] = true;
        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            if (!visited[v] && distance[u]+weight < distance[v]) {
                distance[v] = distance[u]+weight;
                previous[v] = u;
                pq.push(Edge(v, distance[v]));
            }
        }
    }
    return distance;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous,
    int destination) {
    vector<int> shortest_path;
    if (distances[destination] == INF) {
        return shortest_path;
    }
    for (int i = destination; i != -1; i = previous[i]) {
        shortest_path.push_back(i);
    }
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}
void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "Empty Path" << endl;
        return;
    }
    for (int edge : v) {
        cout << edge << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}
