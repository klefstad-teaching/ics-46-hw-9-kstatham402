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
    // cout << "Starting Algo from source: " << source << endl;
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push(Edge(source, 0));
    distance[source] = 0;
    // cout << "Initial distances: ";
    // for (int i = 0; i < n; ++i) {
    //     cout << distance[i] << " ";
    // }
    // cout << endl;
    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();
        int u = current.src;
        // cout << "Processing node: " << u << " with distance: " << current.weight << endl;
        if (visited[u]) {continue;}
        visited[u] = true;
        // cout << "Marking node " << u << " as visited" << endl;
        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            // cout << "Checking neighbor: " << v << " with edge weight: " << weight << endl;
            if (!visited[v] && distance[u]+weight < distance[v]) {
                distance[v] = distance[u]+weight;
                previous[v] = u;
                // cout << "Updating distance for node " << v << " to " << distance[v] << endl;
                pq.push(Edge(v, distance[v]));
            }
        }
    }
    // cout << "Final distances: ";
    // for (int i = 0; i < n; ++i) {
    //     cout << distance[i] << " ";
    // }
    // cout << endl;
    return distance;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous,
    int destination) {
    vector<int> shortest_path;
    // cout << "\n\nShortest path from source: " << destination << endl;
    if (distances[destination] == INF) {
        // cout << "No path found from source: " << destination << endl;
        return shortest_path;
    }
    // for (int i = destination; i != -1; i = previous[i]) {
    //     shortest_path.push_back(i);
    //     cout << "Pushing back node " << i << endl;
    // }
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}
void print_path(const vector<int>& v, int total) {
    // if (!v.empty()) {
    //     for (int edge : v) {
    //         cout << edge << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "Total cost is " << total << endl;
    if (v.size() == 0) {
        cout << "\nTotal cost is " << total << endl;
        return;
    }
    for (int edge : v) {
        cout << edge << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}
