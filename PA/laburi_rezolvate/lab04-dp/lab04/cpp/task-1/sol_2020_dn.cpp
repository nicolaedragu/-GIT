#include <bits/stdc++.h>
using namespace std;

// constanta modulo folosita in aceasta problema
#define MOD ((int)1e9 + 7)
// sau
// #define MOD 100000007
// (varianta 2 e mai ușor de busit, sesizați? :p)

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin.close();
    }

    int get_result() {
        // Calculati numarul de subsiruri ale lui v cu suma numerelor para si
        // returnati restul impartirii numarului la 10^9 + 7 (vezi macro-ul MOD).

        // Sunt prezentate 4 solutii.
        // Oricare dintre dinamici (solve_dp1_nn, solve_dp1_n, solve_dp2_n) s-au punctat cu 10 la laborator.
        // La teme/test va trebui sa alegeti pe cea care intra in timp!
        // (Daca intra toate, atunci alegeti una. Ideal ar fi sa fie cea mai rapida!)

        // 		Decomentati una din urmatoarele linii pentru a selecta solutia dorita.
        return solve_dp1_nn(); // T = O(n^2)
        // return solve_dp1_n();     // T = O(n)
        // return solve_dp2_n();     // T = O(n)
        // return solve_math();      // T = O(log n)
    }

    // Solutia 1: DP - neoptimizata
    // T = O(n ^ 2)
    // S = O(n)
    int solve_dp1_nn() {
        // dp_even[i] = numarul de subsiruri cu suma PARA folosind v[1..i]
        //              SI care se termina cu v[i]
        // dp_odd[i] = numarul de subsiruri cu suma IMPARA folosind v[1..i]
        //              SI care se termina cu v[i]
        vector<int> dp_even(n + 1);
        vector<int> dp_odd(n + 1);
        // Raspunsul este: suma(dp_even[i])

        // cazuri de baza
        dp_even[0] = 0;
        dp_odd[0] = 0;

        for (int i = 1; i <= n; ++i) {
            if (v[i] % 2 == 0) { // PAR
                dp_even[i] = 1; // v[i] singur
                dp_odd[i] = 0; // v[i] NU poate fi singur

                // v[i] poate fi adaugat la
                // - orice subsir cu suma PARA   => suma PARA
                // - orice subsir cu suma IMPARA => suma IMPARA
                for (int j = 1; j < i; ++j) {
                    dp_even[i] = (dp_even[i] + dp_even[j]) % MOD;
                    dp_odd[i] = (dp_odd[i] + dp_odd[j]) % MOD;
                }
            } else { // IMPAR
                dp_even[i] = 0; // v[i] NU poate fi singur
                dp_odd[i] = 1; // v[i] singur

                // v[i] poate fi adauga la
                // - orice subsir cu suma PARA   => suma IMPARA
                // - orice subsir cu suma IMPARA => suma PARA
                for (int j = 1; j < i; ++j) {
                    dp_even[i] = (dp_even[i] + dp_odd[j]) % MOD;
                    dp_odd[i] = (dp_odd[i] + dp_even[j]) % MOD;
                }
            }
        }

        // raspunsul este R = sum(dp_even[i]), i = 1:n
        // dp_even[1] = numarul de subsiruri cu sumara para care se termina cu v[1]
        // dp_even[2] = numarul de subsiruri cu sumara para care se termina cu v[2]
        // ...
        // dp_even[i] = numarul de subsiruri cu sumara para care se termina cu v[i]
        // ...
        // Numarul total de subsiruri cu suma para se obtine prin insumare

        int sol = 0;
        for (int i = 1; i <= n; ++i) {
            sol = (sol + dp_even[i]) % MOD;
        }

        return sol;
    }

    // Solutia 1: DP - optimizata
    // T = O(n)
    // S = O(n)
    // Observam ca in fiecare for cu j, noi extindem o suma
    // Ex. La pasul i - 1 am calculat S1 = dp[1] + .. + dp[i - 2]
    //     La pasul i     am calculat S2 = dp[1] + ...+ dp[i - 2] + dp[i -1]
    // Insa nu am folosit faptul ca S2 = S1 + dp[i - 1]
    // Putem sa folosim sume partiale sa facem o IMPLEMENTARE eficienta
    // cu ACEEASI IDEE!
    int solve_dp1_n() {
        // dp_even[i] = numarul de subsiruri cu suma PARA folosind v[1..i]
        //              SI care se termina cu v[i]
        // dp_odd[i] = numarul de subsiruri cu suma IMPARA folosind v[1..i]
        //              SI care se termina cu v[i]
        vector<int> dp_even(n + 1);
        vector<int> dp_odd(n + 1);
        // Raspunsul este: suma(dp_even[i])

        // cazuri de baza
        dp_even[0] = 0;
        dp_odd[0] = 0;

        // sume partiale
        int sum_even = 0; // dp_even[1] + dp_even[2] + ...
        int sum_odd = 0; //  dp_odd[1] +  dp_odd[2] + ...

        for (int i = 1; i <= n; ++i) {
            if (v[i] % 2 == 0) { // PAR
                dp_even[i] = 1; // v[i] singur
                dp_odd[i] = 0; // v[i] NU poate fi singur

                // v[i] poate fi adauga la
                // - orice subsir cu suma PARA   => suma PARA
                // - orice subsir cu suma IMPARA => suma IMPARA

                dp_even[i] = (dp_even[i] + sum_even) % MOD;
                dp_odd[i] = (dp_odd[i] + sum_odd) % MOD;
            } else { // IMPAR
                dp_even[i] = 0; // v[i] NU poate fi singur
                dp_odd[i] = 1; // v[i] singur

                // v[i] poate fi adauga la
                // - orice subsir cu suma PARA   => suma IMPARA
                // - orice subsir cu suma IMPARA => suma PARA
                dp_even[i] = (dp_even[i] + sum_odd) % MOD;
                dp_odd[i] = (dp_odd[i] + sum_even) % MOD;
            }

            // reactulizez sumele partiale
            sum_even = (sum_even + dp_even[i]) % MOD;
            sum_odd = (sum_odd + dp_odd[i]) % MOD;
        }

        // raspunsul este R = sum(dp_even[i]), i = 1:n
        // Dar stai.. este in sum_even aceasta suma!
        // Sesizati? :p

        return sum_even;
    }

    // Solutia 2: DP - alta idee
    // T = O(n)
    // S = O(n)
    int solve_dp2_n() {
        // dp_even[i] = numarul de subsiruri cu suma PARA folosind v[1..i]
        //  dp_odd[i] = numarul de subsiruri cu suma IMPARA folosind v[1..i]
        vector<int> dp_even(n + 1);
        vector<int> dp_odd(n + 1);
        // Observatie: Nu spunem daca acele subsiruri se termina sau nu cu v[i]!
        // Raspunsul este: dp_even[n]

        // cazuri de baza
        dp_even[0] = 0;
        dp_odd[0] = 0;

        for (int i = 1; i <= n; ++i) {
            if (v[i] % 2 == 0) { // elementul curent e par
                // subsirurile cu suma para sunt:
                // - toate subsirutile cu suma para de dinainte (dp_even[i - 1])
                // - toate subsirutile cu suma para de dinainte la care adaugam v[i] (dp_even[i - 1])
                // - subsirul format doar din v[i]
                dp_even[i] = (dp_even[i - 1] + dp_even[i - 1] + 1) % MOD;

                // subsirurile cu suma impara sunt:
                // - toate subsirurile cu suma impara de dinainte (dp_odd[i - 1])
                // - toate subsirurile cu suma impara de dinainte la care adaugam v[i] (dp_odd[i - 1])
                dp_odd[i] = (dp_odd[i - 1] + dp_odd[i - 1]) % MOD;
            } else { // elementul curent e impar
                // subsirurile cu suma para sunt:
                // - toate subsirurile cu suma para de dinainte (dp_even[i - 1])
                // - toate subsirurile cu suma impara de dinainte la care adaugam v[i] (dp_odd[i - 1])
                dp_even[i] = (dp_even[i - 1] + dp_odd[i - 1]) % MOD;

                // subsirurile cu suma impara sunt:
                // - toate subsirurile cu suma impara de dinainte (dp_odd[i - 1])
                // - toate subsirurile cu suma para de dinainte la care adaugam v[i] (dp_even[i - 1])
                // - subsirul format doar din v[i]
                dp_odd[i] = (dp_odd[i - 1] + dp_even[i - 1] + 1) % MOD;
            }
        }

        // numarul de subsiruri cu SUMA PARA folosind v[1..n]
        return dp_even[n];
    }

    // Solutia 3: math
    // - daca toate numerele sunt pare: 2^n - 1
    // -                        altfel: 2^(n-1) - 1
    // T = O(n) - tot parcurgem vectorul sa vedem daca toate sunt pare
    // S = O(1) - nu stocam tabloul dp (inputul nu a fost luat in calcul)
    int solve_math() {
        bool all_even = true;
        for (int i = 1; i <= n; ++i) {
            all_even &= (v[i] % 2 == 0);
        }

        int sol = (all_even ? log_pow(2, n) - 1 : log_pow(2, n - 1) - 1);
        sol = (sol + MOD) % MOD; // atentie! am scazut 1, expresia poate fi negativa
                                   // Testele nu surprind acest caz. La teme/test trebuie sa fiti atenti!

        return sol;
    }

    // returneaza base ^ exp % MOD
    int log_pow(int base, int exp) {
        if (!exp) {
            return 1;
        }

        int tmp = 1;
        while (exp != 1) {
            if (exp % 2 == 0) {
                base = (1LL * base * base) % MOD;
                exp /= 2;
            } else {
                tmp = (1LL * tmp * base) % MOD;
                exp--;
            }
        }

        return (1LL * tmp * base) % MOD;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
