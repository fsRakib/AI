#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> g[N];
int visited[N];
int level[N];
int parent[N];  // Array to store the parent of each node in the path

void BFS(int source, int goalNode) {
    queue<int> q;
    q.push(source);
    visited[source] = 1;
    parent[source] = -1;  // Root node has no parent
    bool found = false;

    cout << "Order of BFS traversal:" << endl;

    while (!q.empty() && !found) {
        int current_vertex = q.front();
        q.pop();
        cout << current_vertex << " ";

        // If the current vertex is the goal, stop the search
        if (current_vertex == goalNode) {
            found = true;
            break;
        }

        // Traverse all children of the current vertex
        for (int child : g[current_vertex]) {
            if (!visited[child]) {
                q.push(child);
                visited[child] = 1;
                level[child] = level[current_vertex] + 1;
                parent[child] = current_vertex;  // Record the parent to reconstruct path
            }
        }
    }
    cout << endl;

    // Print the path from source to goal node if found
    if (found) {
        vector<int> path;
        int current = goalNode;
        while (current != -1) {  // Trace back from goal node to source
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());  // Reverse to get path from source to goal

        cout << "Path from " << source << " to " << goalNode << ": ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "Goal node " << goalNode << " not reachable from source " << source << "." << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter edges (for an undirected graph):" << endl;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int goalNode;
    cout << "Enter goal node: ";
    cin >> goalNode;

    BFS(1, goalNode);  // Start BFS from node 1

    // Print levels of each node
    cout << "Levels of nodes:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "Node: " << i << " level: " << level[i] << endl;
    }

    return 0;
}

