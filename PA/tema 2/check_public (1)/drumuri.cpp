#include <bits/stdc++.h>

using namespace std;

ifstream fin("drumuri.in");
ofstream fout("drumuri.out");

#define NMAX 100000
#define INF std::numeric_limits<long long>::max()

vector<pair<long long, long long>> graph[NMAX];
vector<pair<long long, long long>> reversed_graph[NMAX];

vector<long long> Dijkstra(long long source) {
    vector<long long> d(NMAX, INF);
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;
    d[source] = 0;
    pq.push({0, source});

    while(!pq.empty()) {
        long long node = pq.top().second;
        long long dist = pq.top().first;
        pq.pop();
        if(dist > d[node]) continue;
        for(auto it : reversed_graph[node]) {
            long long next = it.first;
            long long cost = it.second;
            if(d[next] >= d[node] + cost) {
                d[next] = d[node] + cost;
                pq.push({d[next], next});
            }
        }
    }

    return d;
}

int main() {
    long long N, M;
    // on next M lines we have the edges of the graph and the cost
    fin >> N >> M;
    for (long long i = 0; i < M; i++) {
        long long x, y, c;
        fin >> x >> y >> c;
        graph[x].push_back({y, c});
        reversed_graph[y].push_back({x, c}); // reverse the graph here
    }

    // last line has the 2 sources and the destination
    long long x, y, z;
    fin >> x >> y >> z;

    // run Dijkstra from destination z on reversed graph
    vector<long long> distances = Dijkstra(z);

    // find minimum distance from x to z and from y to z
    long long min1 = distances[x];
    long long min2 = distances[y];
    fout << min1 + min2 << '\n';
}