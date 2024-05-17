#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("oferta.in");
    ofstream fout("oferta.out");

    int n, k;
    fin >> n >> k;
    vector<int> v(n);

    // citesc preturile produselor
    for (int i = 0; i < n; i++)
        fin >> v[i];

    // stochez in dp[i] pretul minim pentru a cumpara primele i produse
    vector<double> dp(n);
    if (k == 1) {
        dp[0] = v[0];
        dp[1] = v[0] + v[1] - min(v[0], v[1]) * 0.5;

        // testez gruparile pe cazuri
        for (int i = 2; i < n; i++) {
            // cazul in care cumpar produsul i impreuna cu produsul i - 1,
            // deci cu reducere 50% pe cel mai ieftin
            double a = dp[i - 2] + v[i - 1] + v[i] - min(v[i], v[i - 1]) * 0.5;
            // cazul in care cumpar produsul i impreuna cu produsele i - 1,
            //  i - 2, deci cel mai ieftin produs gratis
            double b = dp[i - 3] + v[i - 2] + v[i] + v[i - 1] -
             min(min(v[i], v[i - 1]), v[i - 2]);
            // cazul in care cumpar produsul i separat
            double c = dp[i - 1] + v[i];
            dp[i] = min(a, min(b, c));
        }
        fout << fixed << setprecision(1) << dp[n - 1];
    }
    return 0;
}
