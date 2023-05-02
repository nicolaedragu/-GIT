/* DRAGU Nicolae - 314CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Nod
{
    // 0 pentru nod INTERN
    // 1 pentru nod FRUNZA
    unsigned char is_leaf;
    unsigned char red, green, blue;
    // struct Nod *stangaSus, *dreaptaSus, *dreaptaJos, *stangaJos;
    // 0=st sus | 1 = dr sus | 2 = dr jos | 3 = st jos
    struct Nod *children[4];
} Nod;

typedef struct QuadTree
{
    unsigned char red, green, blue;
    unsigned char is_leaf;
    int StangaSus, DreaptaSus, DreaptaJos, StangaJos;
} QuadTree;

typedef struct color
{
    unsigned char red, green, blue;
} color;

void initializare_radacina(Nod **temp)
{
    *temp = (Nod *)malloc(sizeof(Nod));
    (*temp)->is_leaf = 0;
    int i;
    for (i = 0; i < 4; i++)
        (*temp)->children[i] = NULL;
    // DE STERS asta cu = 0 daca merge si fara
    // (*temp)->red = 0;
    // (*temp)->green = 0;
    // (*temp)->blue = 0;
    // pana aici
}

color **citire_image(int width, int height, FILE *fp)
{
    int i;
    color **image;
    image = (color **)malloc(height * sizeof(color *));
    for (i = 0; i < height; i++)
        image[i] = (color *)malloc(width * sizeof(color));
    for (i = 0; i < height; i++)
    {
        fread(image[i], sizeof(color), width, fp);
        // printf("(%u, %u, %u) ", image[i][0].red, image[i][0].green, image[i][0].blue);
        // printf("\n");
    }
    return image;
}
/*
Nod *insertNod(Nod **rootPtr, unsigned char r, unsigned char g, unsigned char b)
{
    int i;
    if ((*rootPtr)->is_leaf == 1)
    {
        return createNod(r, g, b);
    }
    else // (*rootPtr)->is_leaf == 0
    {
        (*rootPtr)->is_leaf = 0;
        for (i = 0; i < 4; i++)
        {
            (*rootPtr)->children[i] = (Nod *)malloc(sizeof(Nod));
            (*rootPtr)->children[i]->is_leaf = 1;
            // patrat_mare((*rootPtr)->children[i], I, J, *image, )
        }
    }
    return *rootPtr;
}
*/

void patrat_mic(Nod *patrat, color **image, int *numar_noduri, int *numar_blocuriOK, int prag, unsigned long long size, int x, int xsf, int y, int ysf, int *latura, int *nivel)
{
    int i, j;
    unsigned long long red = 0, green = 0, blue = 0, mean = 0;
    for (i = x; i < xsf; i++)
        for (j = y; j < ysf; j++)
        {
            red += image[i][j].red;
            green += image[i][j].green;
            blue += image[i][j].blue;
        }
    // in cerinta, formulele apar cu size^2, cu size = latura subatricei
    // patratice, in timp ce eu folosesc in functie variabila size precum
    // aria sa, deci nu mai este nevoie de ridicarea sa la putere
    red /= size;
    green /= size;
    blue /= size;
    patrat->red = (unsigned char)red;
    patrat->green = (unsigned char)green;
    patrat->blue = (unsigned char)blue;
    for (i = x; i < xsf; i++)
        for (j = y; j < ysf; j++)
            mean += (red - image[i][j].red) * (red - image[i][j].red) + (green - image[i][j].green) * (green - image[i][j].green) + (blue - image[i][j].blue) * (blue - image[i][j].blue);
    mean /= (3 * size);
    if (mean > prag)
    {
        *numar_noduri = *numar_noduri + 4;
        *nivel = *nivel + 1;
        patrat->is_leaf = 0;
        for (i = 0; i < 4; i++)
            patrat->children[i] = (Nod *)malloc(sizeof(Nod));
        patrat_mic(patrat->children[0], image, numar_noduri, numar_blocuriOK, prag, size / 4, x, (x + xsf) / 2, y, (y + ysf) / 2, latura, nivel);
        patrat_mic(patrat->children[1], image, numar_noduri, numar_blocuriOK, prag, size / 4, x, (x + xsf) / 2, (y + ysf) / 2, ysf, latura, nivel);
        patrat_mic(patrat->children[2], image, numar_noduri, numar_blocuriOK, prag, size / 4, (x + xsf) / 2, xsf, (y + ysf) / 2, ysf, latura, nivel);
        patrat_mic(patrat->children[3], image, numar_noduri, numar_blocuriOK, prag, size / 4, (x + xsf) / 2, xsf, y, (y + ysf) / 2, latura, nivel);
    }
    else // ramane nedivizat
    {
        *numar_blocuriOK = *numar_blocuriOK + 1;
        patrat->is_leaf = 1;
        if ((xsf - x) > *latura)
            *latura = (xsf - x);
    }
}

void creareTree(QuadTree *arbore, Nod *node, int *index)
{
    int copie_index;
    copie_index = *index;
    arbore[*index].is_leaf = node->is_leaf;
    arbore[*index].red = node->red;
    arbore[*index].green = node->green;
    arbore[*index].blue = node->blue;
    if (node->is_leaf == 0)
    {
        *index = *index + 1;
        arbore[copie_index].StangaSus = *index;
        creareTree(arbore, node->children[0], index);
        *index = *index + 1;
        arbore[copie_index].DreaptaSus = *index;
        creareTree(arbore, node->children[1], index);
        *index = *index + 1;
        arbore[copie_index].DreaptaJos = *index;
        creareTree(arbore, node->children[2], index);
        *index = *index + 1;
        arbore[copie_index].StangaJos = *index;
        creareTree(arbore, node->children[3], index);
    }
}

// Function to recursively print the quadtree
void print_quadtree(QuadTree *quadtree, int numar_noduri)
{
    int i;
    for (i = 0; i < numar_noduri; i++)
        if (quadtree[i].is_leaf == 1)
            printf("quadtree[%d]: %d {%u, %u, %u} | ", i, quadtree[i].is_leaf, quadtree->red, quadtree->green, quadtree->blue);
        else
        {
            // If the Nod is not a leaf, print its position and size and recursively call the function for each child Nod
            printf("quadtree[%d]: %d\n", i, quadtree[i].is_leaf);
            for (i = 0; i < 4; i++)
            {
                print_quadtree(&quadtree[quadtree[i].StangaSus], numar_noduri);
                print_quadtree(&quadtree[quadtree[i].DreaptaSus], numar_noduri);
                print_quadtree(&quadtree[quadtree[i].DreaptaJos], numar_noduri);
                print_quadtree(&quadtree[quadtree[i].StangaJos], numar_noduri);
            }
        }
}

void patrat_mare(color **image, int width, int height, int prag, char *out)
{
    int i, numar_noduri = 0, numar_blocuriOK = 0;
    Nod *radacina;
    // QuadTree *quadtree;
    FILE *g = fopen(out, "w");
    initializare_radacina(&radacina);
    // e radacina, trebuie sa ii alocam memorie pentru copii
    for (i = 0; i < 4; i++)
        radacina->children[i] = (Nod *)malloc(sizeof(Nod));
    unsigned long long size;
    size = width * height;
    int latura = 0;
    int nivel = 2, nivelStangaSus, nivelDreaptaSus, nivelDreaptaJos;
    patrat_mic(radacina->children[0], image, &numar_noduri, &numar_blocuriOK, prag, size / 4, 0, height / 2, 0, width / 2, &latura, &nivel);
    nivelStangaSus = nivel;
    // printf ("nivel Stanga Sus = %d\t", nivelStangaSus);
    nivel = 2;
    patrat_mic(radacina->children[1], image, &numar_noduri, &numar_blocuriOK, prag, size / 4, 0, height / 2, width / 2, width, &latura, &nivel);
    nivelDreaptaSus = nivel;
    // printf ("nivel Dreapta Sus = %d\t", nivelDreaptaSus);
    nivel = 2;
    patrat_mic(radacina->children[2], image, &numar_noduri, &numar_blocuriOK, prag, size / 4, height / 2, height, width / 2, width, &latura, &nivel);
    nivelDreaptaJos = nivel;
    // printf ("nivel Dreapta Jos = %d\t", nivelDreaptaJos);
    nivel = 2;
    patrat_mic(radacina->children[3], image, &numar_noduri, &numar_blocuriOK, prag, size / 4, height / 2, height, 0, width / 2, &latura, &nivel);
    // printf ("nivel Stanga Jos = %d\t", nivel);
    // nivelStangaJos = nivel;
    // quadtree = (QuadTree *)malloc(numar_noduri * sizeof(QuadTree));
    i = 0;
    // creareTree(&quadtree, radacina, &i);
    // fwrite("niveluri", sizeof(int), 1, g);
    if (nivel < nivelStangaSus)
        nivel = nivelStangaSus;
    if (nivel < nivelDreaptaJos)
        nivel = nivelDreaptaJos;
    if (nivel < nivelDreaptaSus)
        nivel = nivelDreaptaSus;
    // fwrite(&nivel, sizeof(int), 1, g);
    // fwrite(&numar_blocuriOK, sizeof(int), 1, g);
    // fwrite(&latura, sizeof(int), 1, g);
    // printf("1) nivel = %d\n", nivel);
    // printf("2) blocuri = %d\n", numar_blocuriOK);
    // printf("3) latura = %d\n", latura);
    fprintf(g, "%d\n", nivel);
    fprintf(g, "%d\n", numar_blocuriOK);
    fprintf(g, "%d\n", latura);
    // cerinta 2
    // print_quadtree(quadtree, numar_noduri);
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[2], "rb");
    char tipPPM[2], width[5], height[6];
    int ww, hh;
    int val_max;
    fread(tipPPM, sizeof(char), 3, fp);
    fread(width, sizeof(char), 4, fp);
    fread(height, sizeof(char), 4, fp);
    char end[2];
    fscanf(fp, "%d%c", &val_max, end);
    hh = atoi(height);
    ww = atoi(width);
    // printf ("w = %d, h = %d\n", ww, hh);
    // printf("MAX = %d\n", val_max);
    color **image = citire_image(ww, hh, fp);

    // int i, j;
    // patrat_mare(&root, i, j, image, ww, hh);
    int prag = atoi(argv[1]);
    patrat_mare(image, ww, hh, prag, argv[3]);

    // Print the resulting quadtree
    // print_quadtree(quadtree);

    // free(pixels);
    fclose(fp);
    return 0;
}
/*
https://curs.upb.ro/2022/pluginfile.php/509159/mod_assign/intro/SDA___Tema_2_2023.pdf
https://thoughtbot.com/blog/how-to-handle-large-amounts-of-data-on-maps
*/