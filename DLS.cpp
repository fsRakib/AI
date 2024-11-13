#include <iostream>
#include <vector>
using namespace std;

const int N = 100;
vector<int> g[N];
bool visited[N];
vector<int> path;

// DLS function with depth limit
bool dls(int vertex, int goalNode, int limit) {
    visited[vertex] = true;
    path.push_back(vertex);

    // Check if we reached the goal node
    if (vertex == goalNode) return true;

    // Stop recursion if the depth limit is reached
    if (limit <= 0) {
        path.pop_back();  // Backtrack
        return false;
    }

    // Visit all unvisited neighbors with a reduced depth limit
    for (int child : g[vertex]) {
        if (!visited[child]) {
            if (dls(child, goalNode, limit - 1)) return true; // Goal found
        }
    }

    // Backtrack if goal not found in this path
    path.pop_back();
    return false;
}

int main() {
    int node, edge;
    cout << "Enter number of nodes and edges: ";
    cin >> node >> edge;

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < edge; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int goalNode, depthLimit;
    cout << "Enter goal node: ";
    cin >> goalNode;
    cout << "Enter depth limit: ";
    cin >> depthLimit;

    if (dls(1, goalNode, depthLimit)) {  // Start DLS from node 1 with depth limit
        cout << "Path to goal node " << goalNode << ": ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "Goal node " << goalNode << " not found within depth limit " << depthLimit << "." << endl;
    }

    return 0;
}
