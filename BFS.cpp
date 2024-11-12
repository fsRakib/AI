#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 2;
bool vis[N];
vector<int> adj[N];

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    // Initialize visited array
    for (int i = 0; i < n + 1; i++) {
        vis[i] = false;
    }

    // Input edges
    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int start, goal;
    cout << "Enter start and goal nodes: ";
    cin >> start >> goal;

    // BFS traversal with level tracking
    queue<int> q;
    q.push(start);
    vis[start] = true;

    bool found = false;
    int level = 0;
    cout << "Level-wise traversal from " << start << " to " << goal << ":" << endl;

    while (!q.empty()) {
        int size = q.size();  // Number of nodes at the current level
        cout << "Level " << level << ": ";

        for (int i = 0; i < size; i++) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            // Check if we reached the goal node
            if (node == goal) {
                found = true;
            }

            // Traverse adjacent nodes
            for (int neighbor : adj[node]) {
                if (vis[neighbor]==false) {
                    vis[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
        level++;

        // Stop processing further levels once the goal is found
        if (found) break;
    }

    return 0;
}
