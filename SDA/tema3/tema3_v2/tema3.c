/* DRAGU Nicolae - 314CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structura pentru nod din grafic
typedef struct Node
{
    int index;
    char obiectiv[20];
    struct Node *urm;
    int *distante;
    float *scoruri;
    int adancime;
} Node;

// structura grafului
typedef struct Graph
{
    int numar_noduri;
    int numar_muchii;
    Node **noduri;
    char obiective[10000][10000];
    int obiective_index;
    int comoara;
} Graph;

// functie de alocare a memoriei pentru graf
Graph *creareGraph(int n, int m)
{
    int i;
    Graph *harta = (Graph *)malloc(sizeof(Graph));

    harta->noduri = (Node **)malloc(n * sizeof(Node *));
    for (i = 0; i < n; i++)
        harta->noduri[i] = (Node *)malloc(sizeof(Node));

    // alocare memorie pentru noduri
    for (i = 0; i < n; i++)
    {
        harta->noduri[i]->index = i;
        harta->noduri[i]->urm = NULL;
    }
    harta->obiective_index = 0;

    return harta;
}

// functie pentru a initializa numele obiectivului cu nodul cu un index dat
void actualizareNode(Node **locatie, int index, char obiectiv[20], Node *next)
{
    strcpy((*locatie)->obiectiv, obiectiv);
    (*locatie)->index = index;
    (*locatie)->urm = next;
}

// functie pentru a initializa numele obiectivului cu nodul cu un index dat
// fara a actualiza nodul urmator, legat de acesta
void actualizarePartial(Node **locatie, int index, char obiectiv[20])
{
    strcpy((*locatie)->obiectiv, obiectiv);
    (*locatie)->index = index;
}

// functie ce aloca memorie nodului
Node *creareNode(int nr_noduri)
{
    int i;
    Node *locatie = (Node *)malloc(sizeof(Node));
    locatie->distante = (int *)malloc(nr_noduri * sizeof(int));
    locatie->scoruri = (float *)malloc(nr_noduri * sizeof(float));
    for (i = 0; i < nr_noduri; i++)
        locatie->distante[i] = 0;
    for (i = 0; i < nr_noduri; i++)
        locatie->scoruri[i] = 0;
    locatie->urm = NULL;
    return locatie;
}

// formula pentru calcularea scorului
void actualizareArc(Graph **harta, int start, int finish)
{
    (*harta)->noduri[start]->scoruri[finish] /= (float)(*harta)->noduri[finish]->adancime;
}

// functie pentru stocarea distantei dintre obiectivul1 si obiectivul2
void Muchie(Graph *harta, char obiectiv1[20], char obiectiv2[20], int distanta)
{
    int i, index1 = -1, index2 = -1;
    for (i = 0; i < harta->obiective_index; i++)
    {
        // daca este deja stocat, s-a mai regasit obiectivul pana acum
        if (strcmp(harta->obiective[i], obiectiv1) == 0)
            index1 = i;
        if (strcmp(harta->obiective[i], obiectiv2) == 0)
            index2 = i;
    }
    // daca nu s-a mai intampinat
    if (index1 == -1)
    {
        strcpy(harta->obiective[harta->obiective_index], obiectiv1);
        index1 = harta->obiective_index;
        harta->obiective_index++;
    }
    if (index2 == -1)
    {
        strcpy(harta->obiective[harta->obiective_index], obiectiv2);
        index2 = harta->obiective_index;
        harta->obiective_index++;
    }
    actualizareNode(&(harta->noduri[index2]), index2, obiectiv2, harta->noduri[index1]);
    // stocare distanta dintre nodurile pentru care s-a apelat functia
    harta->noduri[index2]->distante[index1] = distanta;
    actualizareNode(&(harta->noduri[index1]), index1, obiectiv1, harta->noduri[index1]);
    harta->noduri[index1]->distante[index2] = distanta;
}

// functie pentru stocarea distantei dintre obiectivul1 si obiectivul2, dar unidirectional
void Arc(Graph *harta, char obiectiv1[20], char obiectiv2[20], int distanta, int index)
{
    int i, index1 = -1, index2 = -1;
    for (i = 0; i < harta->obiective_index; i++)
    {
        // daca este deja stocat, s-a mai regasit obiectivul pana acum
        if (strcmp(harta->obiective[i], obiectiv1) == 0)
            index1 = i;
        if (strcmp(harta->obiective[i], obiectiv2) == 0)
            index2 = i;
    }
    // daca nu s-a mai intampinat
    if (index1 == -1)
    {
        strcpy(harta->obiective[harta->obiective_index], obiectiv1);
        index1 = harta->obiective_index;
        harta->obiective_index++;
    }
    if (index2 == -1)
    {
        strcpy(harta->obiective[harta->obiective_index], obiectiv2);
        index2 = harta->obiective_index;
        harta->obiective_index++;
    }
    actualizarePartial(&(harta->noduri[index2]), index2, obiectiv2);
    actualizareNode(&(harta->noduri[index1]), index1, obiectiv1, harta->noduri[index2]);
    // stocare distanta dintre nodurile pentru care s-a apelat functia
    harta->noduri[index1]->distante[index2] = distanta;
    harta->noduri[index1]->scoruri[index2] = distanta;
}

// actualizarea adancimii in structura hartii pentru nodul corespunzator
void adancimeNod(Graph **harta, char obiectiv[20], int adancime)
{
    int gasit = 0, i = 0;
    while (gasit == 0)
    {
        if (strcmp((*harta)->obiective[i], obiectiv) == 0)
        {
            (*harta)->noduri[i]->adancime = adancime;
            gasit = 1;
        }
        else
            i++;
    }
}

// functie de citire a hartii
void citesteInsula(Graph **harta, FILE *f)
{
    char obiectiv1[20];
    char obiectiv2[20];
    int distanta, i;

    for (i = 0; i < (*harta)->numar_noduri; i++)
    {
        (*harta)->noduri[i] = creareNode((*harta)->numar_noduri);
    }

    for (i = 0; i < (*harta)->numar_muchii; i++)
    {
        fscanf(f, "%s", obiectiv1);
        fscanf(f, "%s", obiectiv2);
        fscanf(f, "%d", &distanta);
        Arc((*harta), obiectiv1, obiectiv2, distanta, i);
    }
    int adancime, g_comoara, j;
    // citire adancime pentru fiecare nod
    for (i = 0; i < (*harta)->numar_noduri; i++)
    {
        fscanf(f, "%s", obiectiv1);
        fscanf(f, "%d", &adancime);
        adancimeNod(harta, obiectiv1, adancime);
    }

    // calculare scor pentru fiecare arc
    for (i = 0; i < (*harta)->numar_noduri; i++)
        for (j = 0; j < (*harta)->numar_noduri; j++)
        {
            distanta = (*harta)->noduri[i]->distante[j];
            if ((i != j) && (distanta != 0))
            {
                actualizareArc(harta, i, j);
            }
        }

    fscanf(f, "%d", &g_comoara);
    (*harta)->comoara = g_comoara;
}

// functie de citire a hartii
void citesteHarta(Graph **harta, FILE *f)
{
    char obiectiv1[20];
    char obiectiv2[20];
    int distanta, i;

    // initializare distante cu 0
    for (i = 0; i < (*harta)->numar_noduri; i++)
        (*harta)->noduri[i] = creareNode((*harta)->numar_noduri);

    // citire muchii bidirectionale
    for (i = 0; i < (*harta)->numar_muchii; i++)
    {
        fscanf(f, "%s", obiectiv1);
        fscanf(f, "%s", obiectiv2);
        fscanf(f, "%d", &distanta);
        Muchie((*harta), obiectiv1, obiectiv2, distanta);
    }
}

// functie de determinare a nodurilor adiacente, vecinii
int *determinareVecini(Node *nod, int numar_noduri, int *capat)
{
    int i, k;
    int *vecini;
    k = 0;
    for (i = 0; i < numar_noduri; i++)
        // daca e muchie intre cele 2 noduri
        if (nod->distante[i] != 0)
            k++;
    vecini = (int *)malloc(k * sizeof(int));
    k = 0;
    for (i = 0; i < numar_noduri; i++)
        if (nod->distante[i] != 0)
            vecini[k++] = i;
    *capat = k;
    return vecini;
}

// algoritmul de dfs
void dfs(Graph *harta, int i, int *trecut, int *vecini, int capat, int *contor)
{
    int j;
    trecut[i] = 1;
    vecini = determinareVecini(harta->noduri[i], harta->numar_noduri, &capat);
    for (j = 0; j < capat; j++)
    {
        if (trecut[vecini[j]] == 0)
        {
            *contor = *contor + 1;
            // apelare recursiv
            dfs(harta, vecini[j], trecut, vecini, capat, contor);
        }
    }
}

int *determinareStPoints(Graph *harta, int zone, int *contori)
{
    int *starting_points = (int *)malloc(zone * sizeof(int));
    int i, *trecut, k = 0, *vecini, capat, contor = 0;
    trecut = (int *)calloc(harta->numar_noduri, sizeof(int));
    for (i = 0; i < harta->numar_noduri; i++)
    {
        vecini = determinareVecini(harta->noduri[i], harta->numar_noduri, &capat);
        if (trecut[i] == 0)
        {
            dfs(harta, i, trecut, vecini, capat, &contor);
            // s-a parcurs printr-o componenta conexa
            contori[k] = contor;
            starting_points[k++] = i;
            contor = 0;
        }
        free(vecini);
    }

    free(trecut);
    return starting_points;
}

int determinareZone(Graph *harta)
{
    int i, *trecut, k = 0, *vecini, capat, contor = 0;
    trecut = (int *)calloc(harta->numar_noduri, sizeof(int));
    for (i = 0; i < harta->numar_noduri; i++)
    {
        vecini = determinareVecini(harta->noduri[i], harta->numar_noduri, &capat);
        if (trecut[i] == 0)
        {
            dfs(harta, i, trecut, vecini, capat, &contor);
            k++;
            contor = 0;
        }
        free(vecini);
    }

    free(trecut);
    return k;
}

// functie pentru algorimul Prims
int gasire_vecin_minim(Graph *harta, int *distante, int *trecut)
{
    int min = 99999, min_index, i;
    for (i = 0; i < harta->numar_noduri; i++)
        if ((trecut[i] == 0) && (distante[i] <= min))
        {
            min = distante[i];
            min_index = i;
        }
    return min_index;
}
// functie pentru algorimul Dijkstra
int gasire_arc_minim(Graph *harta, float *scoruri, int *trecut)
{
    int min = 99999, min_index, i;
    for (i = 0; i < harta->numar_noduri; i++)
        if ((trecut[i] == 0) && (scoruri[i] <= min))
        {
            min = scoruri[i];
            min_index = i;
        }
    return min_index;
}

// gasirea indicelui corabiei
int gasireCorabie(Graph *harta)
{
    int i = 0, ok = 0;
    while (ok == 0)
    {
        if (strcmp(harta->noduri[i]->obiectiv, "Corabie") == 0)
            ok = 1;
        else
            i++;
    }
    if (ok == 1)
        return i;
    else
        return -1;
}

// functie pentru afisarea arborelui
void afisareArbore(int arbore[], int p, Graph *harta, FILE *g)
{
    int i;
    for (i = 0; i < p; i++)
        fprintf(g, "%s ", harta->noduri[arbore[i]]->obiectiv);

    fprintf(g, "\n");
}

int PRIMS(Graph *harta, int lungime_sa, int starting_point, FILE *g)
{
    int nr_noduri, drum = 0;
    nr_noduri = harta->numar_noduri;
    int *trecut = (int *)calloc(nr_noduri, sizeof(int));
    int *distante = (int *)malloc(nr_noduri * sizeof(int));

    int i, next;
    for (i = 0; i < nr_noduri; i++)
        distante[i] = 99999;

    distante[starting_point] = 0; // distanta de la un nod la el insisi = 0
    int capat = 0, *vecini, v;

    for (i = 0; i < lungime_sa; i++)
    {
        next = gasire_vecin_minim(harta, distante, trecut);
        trecut[next] = 1;

        capat = 0;
        vecini = determinareVecini(harta->noduri[next], nr_noduri, &capat);

        for (v = 0; v < capat; v++)
            if ((trecut[vecini[v]] == 0) &&
                (harta->noduri[next]->distante[vecini[v]] < distante[vecini[v]]))
                distante[vecini[v]] = harta->noduri[next]->distante[vecini[v]];
        free(vecini);
    }
    trecut[lungime_sa + starting_point] = 1;

    // afisareArbore(arbore_minim, harta);
    for (i = 0; i < nr_noduri; i++)
        if (distante[i] != 99999)
            drum += distante[i];

    free(trecut);
    free(distante);
    return drum;
}

int *DIJKSTRA(Graph *harta, int sursa, int corabie, FILE *g, int *elemente)
{
    int i, v, nr_noduri, *vecini, contor, ok, p, next, capat;
    nr_noduri = harta->numar_noduri;
    int *arbore_minim = (int *)calloc(nr_noduri, sizeof(int));
    int *trecut = (int *)calloc(nr_noduri, sizeof(int));
    float *scoruri = (float *)malloc(nr_noduri * sizeof(float));
    int *parcurs = (int *)calloc(nr_noduri, sizeof(int));

    for (i = 0; i < nr_noduri; i++)
        scoruri[i] = 99999;

    scoruri[sursa] = 0; // Distanta de la sursa la ea insisi este 0
    arbore_minim[0] = -1;

    // Gasirea drumului cel mai scurt pentru toate nodurile
    for (i = 0; i < nr_noduri - 1; i++)
    {
        // Selectarea nodului cu distanta minima care nu a fost vizitat
        next = gasire_arc_minim(harta, scoruri, trecut);
        trecut[next] = 1;

        capat = 0;
        vecini = determinareVecini(harta->noduri[next], nr_noduri, &capat);
        // Actualizarea distantei pentru toti vecinii nodului selectat
        for (v = 0; v < capat; v++)
            if ((trecut[vecini[v]] == 0) &&
                (scoruri[next] != 99999) &&
                (scoruri[next] + harta->noduri[next]->scoruri[vecini[v]] < scoruri[vecini[v]]))
            {
                arbore_minim[vecini[v]] = next;
                scoruri[vecini[v]] = scoruri[next] + harta->noduri[next]->scoruri[vecini[v]];
            }
        free(vecini);
    }

    i = nr_noduri - 1;
    while ((i != corabie) && (i >= 0))
        i--;
    if (i == -1)
    {
        fprintf(g, "Nu exista Corabie\n");
        return 0;
    }

    contor = 0;
    parcurs[0] = corabie;
    p = 1;
    ok = 1;
    while (ok == 1)
    {
        if (contor == nr_noduri)
        {
            fprintf(g, "Echipajul nu poate ajunge la insula\n");
            return 0;
        }
        parcurs[p++] = arbore_minim[i];
        i = arbore_minim[i];
        if (arbore_minim[i] == -1)
            ok = 0; // s-a gasit INSULA
        contor++;
    }

    // inversare pentru DRUMUL NORMAL Insula -> Corabie
    int *drum_final = (int *)malloc(p * sizeof(int));
    for (i = 0; i < p; i++)
        drum_final[i] = parcurs[p - i - 1];

    free(parcurs);
    free(arbore_minim);
    free(scoruri);
    free(trecut);
    *elemente = p;
    return drum_final;
}

// functie pentru prima cerinta, de unde se apeleaza functiile necesare pentru rezolvarea ei
void cerinta1(Graph *harta, FILE *f, FILE *g)
{
    citesteHarta(&harta, f);
    int i, j, aux, k, *starting_points, *contori;
    k = determinareZone(harta);
    contori = (int *)malloc(k * sizeof(int));
    starting_points = determinareStPoints(harta, k, contori);

    fprintf(g, "%d\n", k);

    int *drumuri = (int *)malloc(k * sizeof(int));
    for (i = 0; i < k; i++)
        drumuri[i] = PRIMS(harta, contori[i], starting_points[i], g);

    // sortarea vectorului *drumuri
    for (i = 0; i < k - 1; i++)
        for (j = i + 1; j < k; j++)
            if (drumuri[j] < drumuri[i])
            {
                aux = drumuri[j];
                drumuri[j] = drumuri[i];
                drumuri[i] = aux;
            }
    // afisarea
    for (i = 0; i < k; i++)
        fprintf(g, "%d\n", drumuri[i]);

    free(drumuri);
    free(contori);
    free(starting_points);
}

// functie pentru calcularea drumului
int calculareDrum(Graph *harta, int *arbore, int capat)
{
    int i, drum = 0;
    for (i = 0; i < capat - 1; i++)
        // se aduna distantele dintre 2 noduri alaturate
        drum += harta->noduri[arbore[i]]->distante[arbore[i + 1]];
    return drum;
}

// functie pentru calcularea greutatii minime de pe harta
int calculareGreutate(Graph *harta, int *arbore, int capat)
{
    int i, greutate = 99999;
    for (i = 1; i < capat - 1; i++)
        if (harta->noduri[arbore[i]]->adancime < greutate)
            greutate = harta->noduri[arbore[i]]->adancime;
    return greutate;
}

// functie pentru a doua cerinta, de unde se apeleaza functiile necesare pentru rezolvarea ei
void cerinta2(Graph *harta, FILE *f, FILE *g)
{
    int *arbore, elemente = 0, drum, corabie_poz, greutate_barca, numar_drumuri;
    citesteInsula(&harta, f);
    corabie_poz = gasireCorabie(harta);
    arbore = DIJKSTRA(harta, 0, corabie_poz, g, &elemente);

    afisareArbore(arbore, elemente, harta, g);
    drum = calculareDrum(harta, arbore, elemente);
    fprintf(g, "%d\n", drum);
    greutate_barca = calculareGreutate(harta, arbore, elemente);
    fprintf(g, "%d\n", greutate_barca);
    numar_drumuri = harta->comoara / greutate_barca;
    fprintf(g, "%d\n", numar_drumuri);

    free(arbore);
}

// eliberarea memoriei
void freeGraph(Graph **harta)
{
    int i, n = (*harta)->numar_noduri;
    for (i = 0; i < n; i++)
    {
        free((*harta)->noduri[i]->distante);
        free((*harta)->noduri[i]->scoruri);
    }
    for (i = 0; i < n; i++)
        free((*harta)->noduri[i]);
    free((*harta)->noduri);

    free((*harta));
}

int main(int argc, char **argv)
{
    FILE *f = fopen("tema3.in", "r");
    FILE *g = fopen("tema3.out", "w");
    // N = nr. noduri
    // M =  nr. muchii
    int N, M;
    char cerinta[1];
    // cerinta oferita in linie de comanda
    strcpy(cerinta, argv[1]);
    fscanf(f, "%d", &N);
    fscanf(f, "%d", &M);
    Graph *harta = creareGraph(N, M);
    harta->numar_noduri = N;
    harta->numar_muchii = M;

    if (strcmp(cerinta, "1") == 0)
        cerinta1(harta, f, g);
    else if (strcmp(cerinta, "2") == 0)
        cerinta2(harta, f, g);

    freeGraph(&harta);
    fclose(f);
    fclose(g);
    return 0;
}