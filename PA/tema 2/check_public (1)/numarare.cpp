#include <bits/stdc++.h>
using namespace std;

ifstream fin("numarare.in");
ofstream fout("numarare.out");

#define MOD 1000000007
#define MAXN 100005

long long result = 0;
vector<int> graf1[MAXN], graf2[MAXN];
vector<long long> dp;

void gaseste_drumuri(int d)
{
    for (int i = 1; i <= d; i++)
    {
        int node = i;
        for (auto vecin : graf1[node])
        {
            if (find(graf2[node].begin(), graf2[node].end(), vecin) != graf2[node].end())
            {
                dp[vecin] = (dp[vecin] + dp[node]) % MOD;
            }
        }
    }
    result = dp[d];
}

int main()
{
    int N, M;
    fin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        int x, y;
        fin >> x >> y;
        graf1[x].push_back(y);
    }

    for (int i = 0; i < M; i++)
    {
        int x, y;
        fin >> x >> y;
        graf2[x].push_back(y);
    }
    
    dp = vector<long long>(N + 1, 0);
    dp[1] = 1;

    gaseste_drumuri(N);

    fout << result;

    return 0;
}