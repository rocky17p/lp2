#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2); // Manhattan distance
}

bool isValid(int x, int y, vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    return x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 0;
}

void printPath(vector<vector<pair<int,int>>>& parent,
               pair<int,int> start,
               pair<int,int> goal) {

    vector<pair<int,int>> path;
    pair<int,int> cur = goal;

    while (cur != start) {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }
    path.push_back(start);

    reverse(path.begin(), path.end());

    cout << "Path:\n";
    for (auto &p : path)
        cout << "(" << p.first << "," << p.second << ") ";
}

void AStar(vector<vector<int>>& grid,
           pair<int,int> start,
           pair<int,int> goal) {

    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> gCost(n, vector<int>(m, INT_MAX));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m));

    // (f, g, x, y)
    priority_queue<tuple<int,int,int,int>,
                   vector<tuple<int,int,int,int>>,
                   greater<>> pq;

    gCost[start.first][start.second] = 0;
    pq.push({heuristic(start.first, start.second, goal.first, goal.second),
             0, start.first, start.second});

    while (!pq.empty()) {
        auto [f, g, x, y] = pq.top();
        pq.pop();

        if (make_pair(x, y) == goal) {
            cout << "Goal reached!\n";
            printPath(parent, start, goal);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny, grid)) {
                int newG = g + 1;

                if (newG < gCost[nx][ny]) {
                    gCost[nx][ny] = newG;
                    parent[nx][ny] = {x, y};

                    int h = heuristic(nx, ny, goal.first, goal.second);
                    pq.push({newG + h, newG, nx, ny});
                }
            }
        }
    }

    cout << "No path found!\n";
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };

    pair<int,int> start = {0, 0};
    pair<int,int> goal  = {3, 2};

    AStar(grid, start, goal);
}

