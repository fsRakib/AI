#include <iostream>
#include <vector>
using namespace std;

const int N = 100;
vector<int> g[N];
bool visited[N];
vector<int> path;

// Depth-Limited Search function
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

// Iterative Deepening Search (IDS)
bool ids(int start, int goalNode, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; depth++) {
        fill(visited, visited + N, false);  // Reset visited array for each depth
        path.clear();  // Clear path for each new depth level
        if (dls(start, goalNode, depth)) {
            return true;  // Goal found at this depth
        }
    }
    return false;  // Goal not found within maxDepth
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

    int goalNode, maxDepth;
    cout << "Enter goal node: ";
    cin >> goalNode;
    cout << "Enter maximum depth for IDS: ";
    cin >> maxDepth;

    if (ids(1, goalNode, maxDepth)) {  // Start IDS from node 1
        cout << "Path to goal node " << goalNode << ": ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "Goal node " << goalNode << " not found within maximum depth " << maxDepth << "." << endl;
    }

    return 0;
}

