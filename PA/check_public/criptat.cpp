#include <bits/stdc++.h>
using namespace std;

// structura pentru a stoca cuvantul si raportul
struct Word {
    string word;
    double ratio;
    char dominant;
};

// functia pentru a calcula numarul de litere dominante dintr-un cuvant
int dominantCount(string &word, char dominant) {
    int count = 0;
    for (char c : word)
        if (c == dominant)
            count++;

    return count;
}

// functia pentru a calcula raportul
double calculateRatio(string &word, char dominant) {
    int count = dominantCount(word, dominant);
    if (count == word.size())
        return 1.0;
    else
        return (double)count / word.size();
}

// Functia de comparare pentru sortare
bool compare(Word &a, Word &b) {
    if (a.ratio != b.ratio)
        return a.ratio > b.ratio;
    else
        // sortare dupa numarul de litere dominante din cuvant
        return dominantCount(a.word, a.dominant) <
               dominantCount(b.word, b.dominant);
}

int main() {
    ifstream fin("criptat.in");
    ofstream fout("criptat.out");

    int n;
    fin >> n;
    fin.get();
    vector<Word> words;
    string word;
    map<char, int> distinctLetters;
    int len = 0, dominant_count = 0, i, max = 0;

    // citire cuvinte
    for (i = 0; i < n; i++) {
        getline(fin, word);
        words.push_back({word, 0, 0});
        // calculare lista de litere distincte
        for (char c : word)
            distinctLetters[c]++;
    }

    // pentru fiecare litera distincta, calculez lungimea maxima a parolei
    // cu litera respectiva ca litera dominanta
    for (auto pair : distinctLetters) {
        char c = pair.first;
        // sortez vectorul de cuvinte in functie de raportul de
        //  aparitie al literei c
        for (Word &w : words) {
            w.ratio = calculateRatio(w.word, c);
            w.dominant = c;
        }
        sort(words.begin(), words.end(), compare);

        len = 0;
        dominant_count = 0;
        for (int i = 0; i < n; i++) {
            int current_len = words[i].word.size();
            int current_dominant_count = dominantCount(words[i].word, c);

            // daca adaug cuvantul recent la parola si trec peste
            // pragul de 50% litere dominante, ma opresc
            if (dominant_count + current_dominant_count <=
                        (len + current_len) / 2)
                break;
            len += current_len;
            dominant_count += current_dominant_count;
        }

        // daca am gasit o noua parola mai lunga, o retin
        if (max < len)
            max = len;
    }

    fout << max;
    return 0;
}
