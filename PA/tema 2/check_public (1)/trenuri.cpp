#include <bits/stdc++.h>
using namespace std;

ifstream fin("trenuri.in");
ofstream fout("trenuri.out");

#define MAXN 200001
vector<int> graf[MAXN];

void topsort(int node, vector<bool> &visited, stack<int> &Stack) {
    visited[node] = true;

    for (auto vecin : graf[node]) {
        if (!visited[vecin]) {
            topsort(vecin, visited, Stack);
        }
    }

    Stack.push(node);
}

int find_longest_path(int N, stack<int> &Stack) {
    vector<int> dist(N + 1, INT_MIN);
    dist[1] = 1;

    while (!Stack.empty()) {
        int node = Stack.top();
        Stack.pop();

        if (dist[node] != INT_MIN) {
            for (auto vecin : graf[node]) {
                if (dist[vecin] <= dist[node] + 1) {
                    dist[vecin] = dist[node] + 1;
                }
            }
        }
    }

    return dist[2];
}

int main()
{
    // read first 2 cities
    string sursa, destinatie;
    fin >> sursa >> destinatie;

    // read number of direct routes between 2 cities
    int M;
    fin >> M;
    // read all direct routes and make a map of them so we can
    // work on the graph with nodes as numbers
    map<string, int> cities;
    cities[sursa] = 1;
    cities[destinatie] = 2;

    int index = 3;
    int last_city_read = 0;
    for (int i = 0; i < M; i++)
    {
        string x, y;
        fin >> x >> y;
        if (cities.find(x) == cities.end())
        {
            cities[x] = index++;
            last_city_read = cities[x];
        }
        if (cities.find(y) == cities.end())
        {
            cities[y] = index++;
            last_city_read = cities[y];
        }
        graf[cities[x]].push_back(cities[y]);
    }

    int N = cities.size();

    stack<int> Stack;
    vector<bool> visited(N + 1, false);
    for (int i = 1; i <= N; i++)
    {
        if (!visited[i])
        {
            topsort(i, visited, Stack);
        }
    }

    fout << find_longest_path(N, Stack);

    return 0;
}