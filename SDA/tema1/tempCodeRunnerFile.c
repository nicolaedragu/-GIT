/* DRAGU Nicolae - 314CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListaDubla
{
    char val;
    struct ListaDubla *ant;
    struct ListaDubla *urm;
} Nod;

typedef struct Nod_Deget
{
    Nod *sentinel;
    Nod *final;
    Nod *finger;
} banda;

typedef struct ListaSimpla
{
    char *valoare;
    struct ListaSimpla *urm;
} Coada;

typedef struct SimpleList
{
    void *p;
    struct SimpleList *urm;
    struct SimpleList *ant;
} UndoRedo;

void insereazaUltim(char *comanda, Coada **cap, Coada **ultim)
{
    Coada *temp_elem;
    temp_elem = (Coada *)malloc(sizeof(Coada));
    temp_elem->valoare = (char *)malloc(25 * sizeof(char));
    strcpy(temp_elem->valoare, comanda);
    temp_elem->urm = NULL;

    if (*cap == NULL)
    {
        *cap = temp_elem;
        *ultim = temp_elem;
    }
    else
    {
        (*ultim)->urm = temp_elem;
        *ultim = (*ultim)->urm;
        // (*cap)->urm = *ultim;
        (*ultim)->urm = NULL;
    }
}

void insereazaUNDO(void *bb, UndoRedo **U, UndoRedo **U_sf)
{
    UndoRedo *temp_elem;
    temp_elem = (UndoRedo *)malloc(sizeof(UndoRedo));
    temp_elem->p == bb;

    if (*U == NULL)
    {
        *U = temp_elem;
        (*U)->ant = NULL;
        *U_sf = temp_elem;
        (*U_sf)->urm = NULL;
    }
    else
    {
        (*U_sf)->urm = temp_elem;
        temp_elem->ant = *(U_sf);
        *U_sf = temp_elem;
        (*U_sf)->urm = NULL;
    }
}

void MOVE_LEFT(banda *b)
{
    if (b->final == b->sentinel->urm)
        return;
    else
    {
        b->finger = b->finger->ant;
    }
}

void INSERT_LEFT(banda *b, char insert, FILE *g)
{
    if (b->final == b->sentinel->urm)
        fprintf(g, "ERROR\n");
    else
    {
        b->finger->ant->val = insert;
        b->finger = b->finger->ant;
    }
}

void INSERT_RIGHT(banda *b, char insert, FILE *g)
{
    if (b->finger == b->final) // finger e pe ultima pozitie
    {
        Nod *nod_urmator = (Nod *)malloc(sizeof(Nod));
        nod_urmator->urm = NULL;
        nod_urmator->val = insert;
        nod_urmator->ant = b->final;
        b->final->urm = nod_urmator;
        b->final = b->final->urm;
        b->finger = b->final;
    }
    else
    {
        b->finger->urm->val = insert;
        b->finger = b->finger->urm;
    }
}

void MOVE_RIGHT(banda *b)
{
    if (b->finger == b->final) // finger e pe ultima pozitie
                               // se creeaza celula noua, se insereaza # in ea
    {
        Nod *nod_urmator = (Nod *)malloc(sizeof(Nod));
        nod_urmator->urm = NULL;
        nod_urmator->val = '#';
        nod_urmator->ant = b->final;
        b->final->urm = nod_urmator;
        b->final = b->final->urm;
        b->finger = b->final;
    }
    else
    {
        b->finger = b->finger->urm;
    }
}

void MOVE_RIGHT_CHAR(banda *b, char caut)
{
    if (b->finger->val == caut)
        return;
    else
    {
        // Nod *copieFinger = (Nod *)malloc(sizeof(Nod));
        // copieFinger = b->finger;
        while (b->finger->val != caut)
        {
            if (b->finger == b->final) // finger e pe ultima pozitie
            {
                Nod *nod_urmator = (Nod *)malloc(sizeof(Nod));
                nod_urmator->urm = NULL;
                nod_urmator->val = '#';
                nod_urmator->ant = b->final;
                b->final->urm = nod_urmator;
                b->final = b->final->urm;
                b->finger = b->final;
                break;
            }
            else
                b->finger = b->finger->urm;
        }
    }
}

void MOVE_LEFT_CHAR(banda *b, char caut, FILE *g)
{
    if (b->finger->val == caut)
        return;
    else
    {
        Nod *copieFinger = (Nod *)malloc(sizeof(Nod));
        copieFinger = b->finger;
        while (b->finger->val != caut)
        {
            if (b->finger == b->sentinel->urm) // finger e pe ultima pozitie
            {
                fprintf(g, "ERROR\n");
                b->finger = copieFinger;
                break;
            }
            else
                b->finger = b->finger->ant;
        }
    }
}

void WRITE(banda *b, char de_scris)
{
    b->finger->val = de_scris;
}

// Afisare caracter de pe finger
void SHOW_CURR(banda *b, FILE *g)
{
    fprintf(g, "%c\n", b->finger->val);
}
// Afisare intreaga banda
void SHOW(banda *b, FILE *g)
{
    Nod *nod_urmator = (Nod *)malloc(sizeof(Nod));
    nod_urmator = b->sentinel->urm;
    while (nod_urmator != NULL)
    {
        if (nod_urmator == b->finger)
            fprintf(g, "|%c|", nod_urmator->val);
        else
            fprintf(g, "%c", nod_urmator->val);
        nod_urmator = nod_urmator->urm;
    }
}

void printeaza_coada(Coada *cap, FILE *g)
{
    while (cap != NULL)
    {
        fprintf(g, "%s ", cap->valoare);
        cap = cap->urm;
    }
    fputs("", g);
}

void free_coada(Coada **cap)
{
    Coada *current_node = *cap;
    while (current_node != NULL)
    {
        Coada *temp = current_node;
        current_node = current_node->urm;
        free(temp);
    }
}
void free_undo_redo(UndoRedo **cap)
{
    UndoRedo *current_node = *cap;
    while (current_node != NULL)
    {
        UndoRedo *temp = current_node;
        current_node = current_node->urm;
        free(temp);
    }
}

void free_nod(Nod **final, Nod **sentinel)
{
    Nod *current_node = *final;
    while (current_node != *sentinel)
    {
        Nod *temp = current_node->ant;
        // if (current_node->ant != NULL)
        // current_node = current_node->ant;
        // if (temp != NULL)
        // free(temp);
        free(current_node);
        current_node = temp;
    }
}
/*
void free_banda(banda *cap)
{
    banda *current_node = cap;
    free_nod(&current_node->sentinel);
    // free_nod(&current_node->finger);
    // free_nod(&current_node->final);
}

*/

void deleteNode(UndoRedo **cap, UndoRedo *del)
{
    if ((*cap == NULL) || (del == NULL))
        return;
    if (*cap == del)
        *cap = del->urm;
    if (del->urm != NULL)
        del->urm->ant = del->ant;
    if (del->ant != NULL)
        del->ant->urm = del->urm;
    free(del);
    return;
}

int main()
{
    int n, i;
    char *comanda;
    FILE *f = fopen("tema1.in", "r");
    FILE *g = fopen("tema1.out", "w");

    /* n = numarul de comenzi */
    fscanf(f, "%d ", &n);

    comanda = (char *)malloc(50 * sizeof(char));
    /* Initializare Coada Comenzi */
    Coada *Comenzi, *ComenziUltim, *CopieComenzi;
    Comenzi = (Coada *)malloc(n * sizeof(Coada));
    Comenzi = NULL;
    ComenziUltim = (Coada *)malloc(n * sizeof(Coada));
    ComenziUltim = NULL;
    CopieComenzi = (Coada *)malloc(n * sizeof(Coada));

    /* Initializare banda */
    banda b;
    b.sentinel = (Nod *)malloc(sizeof(Nod));
    b.finger = (Nod *)malloc(sizeof(Nod));
    b.final = (Nod *)malloc(sizeof(Nod));
    
    b.sentinel->ant = NULL;
    b.sentinel->val = '\0';
    b.sentinel->urm = b.final;
    b.final->ant = b.sentinel;
    b.final->val = '#';
    b.final->urm = NULL;
    b.finger = b.final;

    // Comenzi contine comenzile, CU SPATIU
    for (i = 0; i < n; i++)
    {
        fgets(comanda, 50, f);
        comanda[strcspn(comanda, "\n")] = 0;
        insereazaUltim(comanda, &Comenzi, &ComenziUltim);
    }

    // Queue contine prima parte a comenzii, FARA SPATIU
    Coada *Queue = (Coada *)malloc(n * sizeof(Coada));
    Coada *QueueUltim = (Coada *)malloc(n * sizeof(Coada));
    Queue = NULL;
    QueueUltim = NULL;
    char *ptr, s[20];
    CopieComenzi = Comenzi;
    for (i = 0; i < n; i++)
    {
        strcpy(s, CopieComenzi->valoare);
        ptr = strtok(s, " ");
        insereazaUltim(ptr, &Queue, &QueueUltim);
        CopieComenzi = CopieComenzi->urm;
    }
    // exec contine comenziile din coada pentru EXECUTE
    Coada *exec = (Coada *)malloc(sizeof(Coada));
    Coada *ultim_exec = (Coada *)malloc(sizeof(Coada));
    exec = NULL;
    ultim_exec = NULL;

    UndoRedo *UNDO = (UndoRedo *)malloc(sizeof(UndoRedo));
    UndoRedo *UNDO_sf = (UndoRedo *)malloc(sizeof(UndoRedo));
    UndoRedo *REDO = (UndoRedo *)malloc(sizeof(UndoRedo));
    UndoRedo *REDO_sf = (UndoRedo *)malloc(sizeof(UndoRedo));
    UNDO = NULL;
    REDO = NULL;

    void *temp;
    Nod *ex = malloc(sizeof(Nod));
    UndoRedo *ur = (UndoRedo *)malloc(sizeof(UndoRedo));
    int ok;
    char c;
    for (i = 0; i < n; i++)
    {
        ok = 0;
        // Functia EXECUTE
        if (exec != NULL)
        {
            strcpy(s, exec->valoare);
            ptr = strtok(s, " ");
            c = *(exec->valoare + strlen(ptr) + 1);
        }
        if (strcmp(Queue->valoare, "EXECUTE") == 0)
        {
            ok = 1;
            if (strcmp(exec->valoare, "MOVE_LEFT") == 0)
            {
                temp = b.finger;
                // *ex = *((Nod *)temp);
                MOVE_LEFT(&b);
                insereazaUNDO(temp, &UNDO, &UNDO_sf);
            }
            else if (strcmp(exec->valoare, "MOVE_RIGHT") == 0)
            {
                temp = b.finger;
                // *ex = *((Nod *)temp);
                MOVE_RIGHT(&b);
                insereazaUNDO(temp, &UNDO, &UNDO_sf);
            }
            else if (strcmp(ptr, "MOVE_LEFT_CHAR") == 0)
                MOVE_LEFT_CHAR(&b, c, g);
            else if (strcmp(ptr, "MOVE_RIGHT_CHAR") == 0)
                MOVE_RIGHT_CHAR(&b, c);
            else if (strcmp(ptr, "WRITE") == 0)
            {
                WRITE(&b, c);
                // Golire stive UNDO REDO
                free_undo_redo(&UNDO);
                UNDO = NULL;
                free_undo_redo(&REDO);
                REDO = NULL;
            }
            else if (strcmp(ptr, "INSERT_LEFT") == 0)
                INSERT_LEFT(&b, c, g);
            else if (strcmp(ptr, "INSERT_RIGHT") == 0)
                INSERT_RIGHT(&b, c, g);
            // SHOW(&b, g);    fprintf(g, "\n");
            exec = exec->urm;
        }
        // Functiile UPDATE
        if (ok == 0)
            if (strcmp(Queue->valoare, "MOVE_LEFT") == 0)
            {
                // MOVE_LEFT(&b);
                // insereazaUltim(Comenzi->valoare, &exec, &ultim_exec);
                ok = 1;
            }
        if (ok == 0)
            if (strcmp(Queue->valoare, "MOVE_RIGHT") == 0)
            {
                // MOVE_RIGHT(&b);
                // insereazaUltim(Comenzi->valoare, &exec, &ultim_exec);
                ok = 1;
            }
        if (ok == 0)
            if (strcmp(Queue->valoare, "MOVE_LEFT_CHAR") == 0)
            {
                // MOVE_LEFT_CHAR(&b, c, g);
                insereazaUltim(Comenzi->valoare, &exec, &ultim_exec);
                ok = 1;
            }
        if (ok == 0)
            if (strcmp(Queue->valoare, "MOVE_RIGHT_CHAR") == 0)
            {
                // MOVE_RIGHT_CHAR(&b, c);
                insereazaUltim(Comenzi->valoare, &exec, &ultim_exec);
                ok = 1;
            }
        if (ok == 0)
            if (strcmp(Queue->valoare, "WRITE") == 0)
            {
                // WRITE(&b, c);
                insereazaUltim(Comenzi->valoare, &exec, &ultim_exec);
                ok = 1;
            }
        if (ok == 0)
            if (strcmp(Queue->valoare, "INSERT_LEFT") == 0)
            {
                // INSERT_LEFT(&b, c, g);
                insereazaUltim(Comenzi->valoare, &exec, &ultim_exec);
                ok = 1;
            }
        if (ok == 0)
            if (strcmp(Queue->valoare, "INSERT_RIGHT") == 0)
            {
                // INSERT_RIGHT(&b, c, g);
                insereazaUltim(Comenzi->valoare, &exec, &ultim_exec);
                ok = 1;
            }
        // Functiile Queue
        if (ok == 0)
            if (strcmp(Queue->valoare, "SHOW_CURRENT") == 0)
            {
                // SHOW_CURR(b, g);
                fprintf(g, "%c\n", b.finger->val);
                ok = 1;
            }
        if (ok == 0)
            if (strcmp(Queue->valoare, "SHOW") == 0)
            {
                SHOW(&b, g);
                fprintf(g, "\n");
                ok = 1;
            }
        // Functiile UNDO/REDO
        
        if (ok == 0)
        
            if (strcmp(Queue->valoare, "UNDO") == 0)
            {
                ur = UNDO_sf;
                // *ex = *((Nod *)ur->p);
                ex = ur->p;
                // printf("1 = %c\n",(char*)ur->p);
                // eliminare nod din UNDO
                deleteNode(&UNDO, ur);

                temp = b.finger;
                insereazaUNDO(temp, &REDO, &REDO_sf);
                b.finger = ex;
                ok = 1;
            }
        if (ok == 0)
            if (strcmp(Queue->valoare, "REDO") == 0)
            {
                ur = REDO_sf;
                // *ex = *((Nod *)ur->p);
                ex = ur->p;
                // eliminare nod din REDO
                deleteNode(&REDO, ur);

                temp = b.finger;
                insereazaUNDO(temp, &UNDO, &UNDO_sf);
                b.finger = ex;
                ok = 1;
            }
        
        if (i != n - 1)
        {
            Queue = Queue->urm;
            Comenzi = Comenzi->urm;
        }
    }

    free_coada(&Comenzi);
    // free_banda(&b);
    free_nod(&b.final,&b.sentinel);
    fclose(f);
    fclose(g);
    return 0;
}