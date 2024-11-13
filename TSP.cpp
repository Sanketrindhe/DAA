#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF INT_MAX

int n, finalCost = INF;
vector<vector<int>> costMatrix;
vector<bool> visited;

class Node {
public:
    int level, pathCost, bound;
    vector<int> path;

    Node(int l, int c, int b) {
        level = l;
        pathCost = c;
        bound = b;
    }
};

int calculateBound(Node &node) {
    int bound = node.pathCost;
    int visitedCount = node.level;

    // Find the minimum cost of reaching the next unvisited cities
    for (int i = 0; i < n; i++) {
        if (visited[i] == false) {
            int minEdge = INF;
            for (int j = 0; j < n; j++) {
                if (i != j && visited[j] == false) {
                    minEdge = min(minEdge, costMatrix[i][j]);
                }
            }
            bound += minEdge;
        }
    }

    return bound;
}

void TSPBranchAndBound() {
    // Initialize the root node
    Node root(0, 0, 0);
    root.path.push_back(0);

    vector<bool> visitedCities(n, false);
    visitedCities[0] = true;

    // Create a priority queue (min-heap)
    vector<Node> pq;
    pq.push_back(root);

    while (!pq.empty()) {
        Node node = pq.back();
        pq.pop_back();

        // If all cities are visited, update the final cost
        if (node.level == n - 1) {
            if (costMatrix[node.path[node.level]][0] != INF) {
                int finalCostCandidate = node.pathCost + costMatrix[node.path[node.level]][0];
                if (finalCostCandidate < finalCost) {
                    finalCost = finalCostCandidate;
                    for (int i = 0; i <= node.level; i++) {
                        cout << node.path[i] + 1 << " --> ";
                    }
                    cout << node.path[0] + 1 << endl;
                }
            }
            continue;
        }

        // Generate the child nodes
        for (int i = 0; i < n; i++) {
            if (!visitedCities[i] && costMatrix[node.path[node.level]][i] != INF) {
                Node child(node.level + 1, node.pathCost + costMatrix[node.path[node.level]][i], 0);
                child.path = node.path;
                child.path.push_back(i);

                visitedCities[i] = true;
                child.bound = calculateBound(child);

                // If the bound is less than the final cost, explore this child
                if (child.bound < finalCost) {
                    pq.push_back(child);
                }
                visitedCities[i] = false;
            }
        }
    }
}

int main() {
    cout << "Enter the number of cities: ";
    cin >> n;

    costMatrix.resize(n, vector<int>(n));

    cout << "Enter the cost matrix (use " << INF << " for infinity):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> costMatrix[i][j];
        }
    }

    cout << "\nThe best path is:\n";
    TSPBranchAndBound();
    cout << "\nMinimum cost: " << finalCost << endl;

    return 0;
}
