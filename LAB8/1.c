#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char character;
    int frequency;
    struct node *left;
    struct node *right;
} node;

node *create_node(char character, int frequency)
{
    node *new_node = malloc(sizeof(node));
    new_node->character = character;
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void interschimbare(node **a, node **b)
{
    node *temp = *a;
    *a = *b;
    *b = temp;
}

void min_heap(node **nodes, int heap_size, int index)
{
    int smallest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    if (left_child < heap_size && nodes[left_child]->frequency < nodes[smallest]->frequency)
        smallest = left_child;

    if (right_child < heap_size && nodes[right_child]->frequency < nodes[smallest]->frequency)
        smallest = right_child;

    if (smallest != index)
    {
        interschimbare(&nodes[index], &nodes[smallest]);
        min_heap(nodes, heap_size, smallest);
    }
}

node *build_huffman_tree(char *text, int length)
{
    int frequencies[256] = {0};

    for (int i = 0; i < length; i++)
        frequencies[(int)text[i]]++;

    node **nodes = malloc(256 * sizeof(node *));
    int heap_size = 0;

    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] > 0)
        {
            nodes[heap_size] = create_node((char)i, frequencies[i]);
            heap_size++;
        }
    }

    while (heap_size > 1)
    {
        node *left = nodes[0];
        interschimbare(&nodes[0], &nodes[heap_size - 1]);
        heap_size--;

        min_heap(nodes, heap_size, 0);

        node *right = nodes[0];
        interschimbare(&nodes[0], &nodes[heap_size - 1]);
        heap_size--;

        min_heap(nodes, heap_size, 0);

        node *new_node = create_node('\0', left->frequency + right->frequency);
        new_node->left = left;
        new_node->right = right;

        nodes[heap_size] = new_node;
        heap_size++;

        for (int i = heap_size / 2 - 1; i >= 0; i--)
            min_heap(nodes, heap_size, i);
    }

    return nodes[0];
}

void encode_character(node *root, char character, char *code, int depth)
{
    if (root == NULL)
        return;

    if (root->character == character)
    {
        code[depth] = '\0';
        printf("%s", code);
        return;
    }

    code[depth] = '0';
    encode_character(root->left, character, code, depth + 1);

    code[depth] = '1';
    encode_character(root->right, character, code, depth + 1);
}

void encode_text(node *root, char *text, int length)
{
    for (int i = 0; i < length; i++)
    {
        char code[256] = {0};
        encode_character(root, text[i], code, 0);
    }
}

void decode_text(node *root, char *code, int length)
{
    node *current = root;

    for (int i = 0; i < length; i++)
    {
        if (code[i] == '0')
            current = current->left;
        else
            current = current->right;

        if (current->left == NULL && current->right == NULL)
        {
            printf("%c", current->character);
            current = root;
        }
    }
}

int main()
{
    char text[] = "TEXT";
    int length = strlen(text);

    node *root = build_huffman_tree(text, length);

    printf("Coduri Huffman pentru caracterele din text:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%c: ", text[i]);
        encode_character(root, text[i], NULL, 0);
        printf("\n");
    }

    printf("\Text codat:\n");
    encode_text(root, text, length);
    printf("\n");

    char code[] = "1011000100111111101010110011011110010000101010000111011";
    printf("\nText decodat:\n");
    decode_text(root, code, strlen(code));
    printf("\n");

    return 0;
}