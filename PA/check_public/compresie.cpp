#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("compresie.in");
    ofstream fout("compresie.out");

    int n, m;
    fin >> n;
    vector<int> v(n);

    // primul sir
    for (int i = 0; i < n; i++)
        fin >> v[i];

    fin >> m;
    vector<int> w(m);
    // al doilea sir
    for (int i = 0; i < m; i++)
        fin >> w[i];

    // indici si numarul de secvente egale
    int i = 0, j = 0, out = 0;

    // parcurg ambele siruri simultan
    while (i < n && j < m) {
        // initializez sumele cu primul element din fiecare sir
        int sum_v = v[i], sum_w = w[j];
        // adauga elemente la suma mai mica pana cand sumele sunt egale
        while (i < n && j < m && sum_v != sum_w) {
            if (sum_v < sum_w)
                sum_v += v[++i];
            else
                sum_w += w[++j];
        }
        // daca sumele sunt egale, creste numarul de secvente
        //  egale si avanseaza ambii indici
        if (sum_v == sum_w) {
            out++;
            i++;
            j++;
        }
    }

    // daca nu am parcurs complet ambele siruri se afiseaza -1
    if (i < n || j < m)
        fout << -1;
    else
        fout << out;

    return 0;
}
