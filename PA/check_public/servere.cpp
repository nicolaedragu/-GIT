#include <bits/stdc++.h>
using namespace std;

double curent_maxim(vector<double> &c);
double calcul_putere_server(double curent, vector<double> &p,
                            vector<double> &c);

// se foloseste metoda divide et impera pentru a gasi puterea maxima
double divide(vector<double> &p, vector<double> &c, double left,
              double right, double prag) {
    double mid = (left + right) / 2;
    double power = calcul_putere_server(mid, p, c);
    // calcul putere pentru capetele intervalului
    double power_left = calcul_putere_server(mid - prag, p, c);
    double power_right = calcul_putere_server(mid + prag, p, c);

    // conditie de oprire
    if (power_left < power && power_right < power)
        return power;

    // apelare recursiva
    if (power_left < power)
        return divide(p, c, mid, right, prag);
    return divide(p, c, left, mid, prag);
}

double calcul_putere_server(double curent, vector<double> &p,
                            vector<double> &c) {
    // infinit
    double min = numeric_limits<double>::max();

    for (long unsigned int i = 0; i < p.size(); i++) {
        if (p[i] - fabs(curent - c[i]) < min) {
            min = p[i] - fabs(curent - c[i]);
        }
    }
    return min;
}

// functie pentru a calcula curentul maxim pentru capatul din dreapta
// al intervalului pentru divide et impera
double curent_maxim(vector<double> &c) {
    double max = 0;
    for (long unsigned int i = 0; i < c.size(); i++)
        if (c[i] > max)
            max = c[i];

    return max;
}

int main() {
    ifstream fin("servere.in");
    ofstream fout("servere.out");

    long unsigned int n;
    fin >> n;
    vector<double> p(n);
    vector<double> c(n);

    for (long unsigned int i = 0; i < n; i++)
        fin >> p[i];

    for (long unsigned int i = 0; i < n; i++)
        fin >> c[i];

    // apelare functie
    fout << fixed << setprecision(1) << divide(p, c, 0,
         curent_maxim(c), 0.1);
    return 0;
}
