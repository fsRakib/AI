#include <bits/stdc++.h>
using namespace std;

// Possible moves for the blank space (0): down, right, up, left
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

// Calculate the Manhattan distance for heuristic
int calculateManhattan(const vector<vector<int>>& current, const vector<vector<int>>& goal) {
    int distance = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (current[i][j] != 0) {
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        if (current[i][j] == goal[x][y]) {
                            distance += abs(i - x) + abs(j - y);
                        }
                    }
                }
            }
        }
    }
    return distance;
}

// Check if a position is within the grid bounds
bool isValid(int x, int y) {
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

// Print the current puzzle state
void printState(const vector<vector<int>>& state) {
    for (const auto& row : state) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "- - -" << endl;
}

// A* algorithm to solve the 8-puzzle problem
void solve8Puzzle(vector<vector<int>> start, vector<vector<int>> goal) {
    priority_queue<pair<int, vector<vector<int>>>> pq; // (total_cost, state)
    map<vector<vector<int>>, bool> visited;
    map<vector<vector<int>>, string> path;
    int startX, startY;

    // Find initial blank position
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (start[i][j] == 0) {
                startX = i;
                startY = j;
            }
        }
    }

    // Initialize priority queue with starting state
    int startCost = calculateManhattan(start, goal);
    pq.push({-startCost, start});
    path[start] = "";

    while (!pq.empty()) {
        auto current = pq.top().second;
        pq.pop();

        // If goal state is reached, print solution path and state
        if (current == goal) {
            cout << "Solution found with path: " << path[current] << " (0:down, 1:right, 2:up, 3:left)" << endl;
            printState(current);
            return;
        }

        // Skip already visited states
        if (visited[current]) continue;
        visited[current] = true;

        // Get current blank position
        int blankX, blankY;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current[i][j] == 0) {
                    blankX = i;
                    blankY = j;
                }
            }
        }

        // Explore possible moves
        for (int i = 0; i < 4; i++) {
            int newX = blankX + dx[i];
            int newY = blankY + dy[i];

            if (isValid(newX, newY)) {
                // Create new state by swapping blank with target position
                vector<vector<int>> newState = current;
                swap(newState[blankX][blankY], newState[newX][newY]);

                // Skip if already visited
                if (visited[newState]) continue;

                // Calculate new cost and add to priority queue
                int newCost = calculateManhattan(newState, goal);
                pq.push({-(newCost + path[current].size() + 1), newState});
                path[newState] = path[current] + to_string(i);
            }
        }
    }

    cout << "No solution found." << endl;
}

int main() {
    vector<vector<int>> start = {
        {1, 3, 0},
        {4, 2, 6},
        {7, 5, 8}
    };

    vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    solve8Puzzle(start, goal);
    return 0;
}
