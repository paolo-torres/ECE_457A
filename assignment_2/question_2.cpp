#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const vector<vector<const char> > maze {
    {'1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '1'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'0', '0', '0', '0', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1'},
    {'1', '1', 'B', '0', '0', '0', '1', '1', '0', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1'},
    {'1', '1', '1', '0', '0', '0', '1', '1', '0', '0', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', 'A', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '*', '1'},
    {'0', '0', '0', '0', '0', '0', '0', '1', '0', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '1'},
    {'1', '1', '*', '*', '*', '*', '*', '*', '*', '*', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0'},
    {'1', '1', '*', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0'},
    {'1', '1', '*', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '0', '1', '1', '1', '1', '1', '0', '0', '0'},
    {'1', '1', '*', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '0', '0', '0', '0'},
    {'1', '1', '*', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '0', '1', '0', '1', '1', '0', '1', '1', '0'},
    {'1', '1', 'S', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '0', '1', '1', '0', '1', '1', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '0', '1', '1', '0', '1', '1', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1'},
    {'1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1'},
    {'1', '1', '0', '0', '0', '1', '0', '0', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1'},
    {'1', '1', '0', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
    {'0', '0', '0', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1', '1', '1'},
    {'0', '0', '0', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1'},
    {'1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

vector<vector<int> > tracePath(map<vector<int>, vector<vector<int>> > &m, int &cost, int i, int j, int iEnd, int jEnd) {
    vector<vector<int> > path; 
    int iTrace = iEnd;
    int jTrace = jEnd;
    path.push_back({iEnd, jEnd});
    while (iTrace != i || jTrace != j) {
        for (auto it = m.begin(); it != m.end(); ++it) {
            for (int v = 0; v < it->second.size(); ++v) {
                if (iTrace == it->second[v][0] && jTrace == it->second[v][1]) {
                    iTrace = it->first[0];
                    jTrace = it->first[1];
                    path.push_back({iTrace, jTrace});
                    if (maze[iTrace][jTrace] == '*') {
                        cost += 30;
                    } else {
                        ++cost;
                    }
                }
            }
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

bool isValid(int x, int y, vector<vector<bool> > &visited) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && !visited[x][y] && maze[x][y] != '0';
}

bool bfs(vector<vector<int> > &path, map<vector<int>, vector<vector<int>> > &m, int &cost, int &nodes, int i, int j, int iEnd, int jEnd) {
    vector<vector<bool> > visited(maze.size(), vector<bool>(maze[0].size(), false));
    vector<vector<int> > dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    queue<vector<int> > q;
    visited[i][j] = true;
    q.push({i, j});
    while (!q.empty()) {
        vector<int> s = q.front();
        q.pop();
        if (s[0] == iEnd && s[1] == jEnd) {
            path = tracePath(m, cost, i, j, iEnd, jEnd);
            return true;
        }
        for (int i = 0; i < dirs.size(); ++i) {
            int x = s[0] + dirs[i][0];
            int y = s[1] + dirs[i][1];
            if (isValid(x, y, visited)) {
                visited[x][y] = true;
                q.push({x, y});
                if (m.find({s[0], s[1]}) == m.end()) {
                    m.insert({{s[0], s[1]}, vector<vector<int>>()});
                }
                m[{s[0], s[1]}].push_back(q.back());
                ++nodes;
            }
        }
    }
    return false;
}

void applyBFS(int i, int j, int iEnd, int jEnd) {
    vector<vector<int> > path;
    map<vector<int>, vector<vector<int>> > m;
    int cost = 0;
    int nodes = 0;

    if (bfs(path, m, cost, nodes, i, j, iEnd, jEnd)) {
        cout << "Path: ";
        for (int i = 0; i < path.size(); ++i) {
            cout <<  "(" << path[i][0] << ", " << path[i][1] << ") > ";
        }
        cout << endl;
        cout << "Cost: " << cost << endl;
        cout << "Nodes: " << nodes << endl << endl;
    }
}

bool dfs(vector<vector<bool> > visited, vector<pair<int, int> > &path, int &cost, int &nodes, int i, int j, int iEnd, int jEnd) {
    if (!visited[i][j]) {
        visited[i][j] = true;
        path.push_back(make_pair(i, j));
        if (maze[i][j] == '*') {
            cost += 30;
        } else {
            ++cost;
        }
        ++nodes;
        if (i == iEnd && j == jEnd) {
            return true;
        }
        if (j > 0 && maze[i][j-1] != '0') {
            if (dfs(visited, path, cost, nodes, i, j - 1, iEnd, jEnd)) {
                return true;
            }
        }
        if (i > 0 && maze[i-1][j] != '0') {
            if (dfs(visited, path, cost, nodes, i - 1, j, iEnd, jEnd)) {
                return true;
            }
        }
        if (j < maze[0].size() - 1 && maze[i][j+1] != '0') {
            if (dfs(visited, path, cost, nodes, i, j + 1, iEnd, jEnd)) {
                return true;
            }
        }
        if (i < maze.size() && maze[i+1][j] != '0') {
            if (dfs(visited, path, cost, nodes, i + 1, j, iEnd, jEnd)) {
                return true;
            }
        }
        visited[i][j] = false;
        path.pop_back();
        if (maze[i][j] == '*') {
            cost -= 30;
        } else {
            --cost;
        }
        --nodes;
    }
    return false;
}

void applyDFS(int i, int j, int iEnd, int jEnd) {
    vector<vector<bool> > visited(maze.size(), vector<bool>(maze[0].size(), false));

    vector<pair<int, int> > path;
    int cost = 0;
    int nodes = 0;

    if (dfs(visited, path, cost, nodes, i, j, iEnd, jEnd)) {
        cout << "Path: ";
        for (int i = 0; i < path.size(); ++i) {
            cout << "(" << path[i].first << ", " << path[i].second << ") > ";
        }
        cout << endl;
        cout << "Cost: " << cost << endl;
        cout << "Nodes: " << nodes << endl << endl;
    }

    for (auto &v: visited) {
        fill(v.begin(), v.end(), false);
    }

    path.clear();
    nodes = 0;
}

int main() {
    cout << "Breadth First Search" << endl << endl;

    applyBFS(13, 2, 5, 23);
    applyBFS(13, 2, 3, 2);
    applyBFS(24, 0, 0, 24);

    cout << "Depth First Search" << endl << endl;

    applyDFS(13, 2, 5, 23);
    applyDFS(13, 2, 3, 2);
    applyDFS(24, 0, 0, 24);

    return 0;
}
