#include <iostream>
#include <vector>
#include "dijkstras.h"  // Include your header file

using namespace std;
// g++ -std=c++17 -o dijkstras_main src/dijkstras_main.cpp src/dijkstras.cpp
void test_dijkstra() {
    Graph G;
    G.numVertices = 3;
    G.resize(3);

    G[0].push_back(Edge(0, 1, 1));
    G[0].push_back(Edge(0, 2, 4));
    G[1].push_back(Edge(1, 2, 3));

    int source = 0;
    vector<int> previous;

    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    cout << "Shortest distances from source" << source << ": dist[0] = 0, dist[1] = 1, dist[2] = 4" << endl;
    for (int i = 0; i < G.numVertices; i++) {
        cout << "dist[" << i << "] = " << distances[i] << endl;
    }

    cout << "\nPrevious node array: [-1, 0, 0]" << endl;
    for (int i = 0; i < G.numVertices; i++) {
        cout << previous[i] << ", ";
    }
    cout << endl;
}
int test_dijkstra_small() {
    Graph G;
    string filename = "src/small.txt";

    try {
        file_to_graph(filename, G);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    int source = 0; // Set the source vertex
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    cout << "Shortest distances from node " << source << ":\n";
    for (size_t i = 0; i < distances.size(); i++) {
        cout << "Total Cost is " << (distances[i] == INF ? "INF" : to_string(distances[i])) << endl;
    }

    int destination = 2; // Example destination
    vector<int> shortest_path = extract_shortest_path(distances, previous, destination);

    cout << "Shortest path from " << source << " to " << destination << ": ";
    if (shortest_path.empty()) {
        cout << "No path exists.\n";
    } else {
        for (int node : shortest_path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}

int main() {
    test_dijkstra_small();
    // test_dijkstra();
    return 0;
}
