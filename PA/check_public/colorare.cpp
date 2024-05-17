#include <bits/stdc++.h>
using namespace std;

// definesc MOD ca fiind 10^9 + 7
const int MOD = 1e9 + 7;

// functie care calculeaza ridicarea la putere logaritmica
long long int logarithmic_exponentiation(long long base, int exp) {
    long long int result = 1;
    // base %= MOD;
    while (exp > 0) {
        if (exp & 1) {  // testez daca este impar
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;  // injumatatesc exponentul
    }
    return result;
}

// functie care actualizeaza valoarea de iesire pentru cazul in care
// zona dinainte este orizontala
void horizontal_prev(long long int &out, char current, int &counter) {
    if (current == 'H')  // daca zona curenta este orizontala
        out = (out * 3) % MOD;
    else if (current == 'V')  // daca zona curenta este verticala
        out = (out * 1) % MOD;

    // scad numarul de zone curente ramase
    counter--;
}

// functie care actualizeaza valoarea de iesire pentru cazul in care
// zona dinainte este verticala
void vertical_prev(long long int &out, char current, int &counter) {
    if (current == 'H')  // daca zona curenta este orizontala
        out = (out * 2) % MOD;
    else if (current == 'V')  // daca zona curenta este verticala
        out = (out * 2) % MOD;

    // scad numarul de zone curente ramase
    counter--;
}

int main() {
    ifstream fin("colorare.in");
    ofstream fout("colorare.out");

    int n;
    fin >> n;
    long long int out;
    char tip, prev_tip;
    int numar;

    // citesc o pereche
    fin >> numar >> tip;
    n--;

    // initializez valoarea de iesire in functie de tipul zonei
    if (tip == 'H')
        out = 6;
    else
        out = 3;
    numar--;

    // inmultesc exponential valoarea de iesire cu 2 sau 3 in functie de
    // cate zone au mai ramas de acelasi tip
    if (tip == 'H')
        out = (out * logarithmic_exponentiation(3, numar)) % MOD;
    else
        out = (out * logarithmic_exponentiation(2, numar)) % MOD;

    // citesc restul de perechi
    while (n > 0) {
        prev_tip = tip;
        fin >> numar >> tip;
        n--;
        // daca zona dinainte este orizontala
        if (prev_tip == 'V')
            // actualizez in functie de zona curenta
            vertical_prev(out, tip, numar);
        else
            // actualizez in functie de zona curenta
            horizontal_prev(out, tip, numar);

        // inmultesc exponential valoarea de iesire cu 2 sau 3 in functie de
        // cate zone au mai ramas de acelasi tip
        if (tip == 'H')
            out = (out * logarithmic_exponentiation(3, numar)) % MOD;
        else
            out = (out * logarithmic_exponentiation(2, numar)) % MOD;
    }

    fout << out;
    return 0;
}
