#include <iostream>
#include <vector>
#include "dijkstras.h"

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
void test_dijkstra_small() {
    Graph G;
    string filename = "src/largest.txt";

    try {
        file_to_graph(filename, G);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }

    int source = 1;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    for (int i = 0; i < distances.size(); i++) {
        vector<int> shortest_path = extract_shortest_path(distances, previous, i);
        print_path(shortest_path, distances[i]);
    }
}

int main() {
    test_dijkstra_small();
    // test_dijkstra();
    return 0;
}
