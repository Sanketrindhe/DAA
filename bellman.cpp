#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Edge structure to store the graph
struct Edge {
    int u, v, weight;
};

// Bellman-Ford Algorithm
void bellmanFord(int vertices, int edges, vector<Edge>& graph, int source) {
    // Step 1: Initialize distances from source to all other vertices as INFINITE
    vector<int> distance(vertices, INT_MAX);
    distance[source] = 0;

    // Step 2: Relax all edges 'vertices - 1' times
    for (int i = 1; i < vertices; ++i) {
        for (int j = 0; j < edges; ++j) {
            int u = graph[j].u;
            int v = graph[j].v;
            int weight = graph[j].weight;
            
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < edges; ++i) {
        int u = graph[i].u;
        int v = graph[i].v;
        int weight = graph[i].weight;

        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    // Print the shortest distances
    cout << "Vertex Distance from Source " << source << ":\n";
    for (int i = 0; i < vertices; ++i) {
        if (distance[i] == INT_MAX)
            cout << i << ": INF\n";
        else
            cout << i << ": " << distance[i] << endl;
    }
}

int main() {
    int vertices, edges;

    // Taking input for number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    // Vector to store edges
    vector<Edge> graph(edges);

    // Taking input for each edge
    cout << "Enter the edges (u, v, weight) format:\n";
    for (int i = 0; i < edges; ++i) {
        cout << "Edge " << i + 1 << ": ";
        cin >> graph[i].u >> graph[i].v >> graph[i].weight;
    }

    int source;
    // Taking input for the source vertex
    cout << "Enter the source vertex: ";
    cin >> source;

    // Run the Bellman-Ford Algorithm
    bellmanFord(vertices, edges, graph, source);

    return 0;
}
