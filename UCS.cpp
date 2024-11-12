#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 2;
vector<pair<int, int>> adj[N];  // adj[node] = list of (neighbor, cost)
vector<int> parent(N, -1);      // Track path
vector<int> dist(N, INT_MAX);   // Distance from start node

// Function to print the path from start to goal
void printPath(int start, int goal) {
    vector<int> path;
    for (int v = goal; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    cout << "Path from " << start << " to " << goal << " with minimum cost:\n";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
    cout << "Total cost: " << dist[goal] << endl;
}

void uniformCostSearch(int start, int goal) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int cost = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        // Stop if we reach the goal node with minimum cost
        if (node == goal) {
            printPath(start, goal);
            return;
        }

        // Explore neighbors
        for (auto neighbor : adj[node]) {
            int nextNode = neighbor.first;
            int edgeCost = neighbor.second;
            int newCost = cost + edgeCost;

            // If a cheaper path is found, update the cost and path
            if (newCost < dist[nextNode]) {
                dist[nextNode] = newCost;
                parent[nextNode] = node;
                pq.push({newCost, nextNode});
            }
        }
    }

    cout << "No path found from " << start << " to " << goal << endl;
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter edges (u v cost):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});  // For undirected graphs; remove if directed
    }

    int start, goal;
    cout << "Enter start and goal nodes: ";
    cin >> start >> goal;

    uniformCostSearch(start, goal);

    return 0;
}

