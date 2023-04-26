#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 10

typedef struct trie_node
{
    struct trie_node *children[ALPHABET_SIZE];
    int is_end_of_word;
} trie_node;

trie_node *create_node()
{
    trie_node *node = (trie_node *)malloc(sizeof(trie_node));
    node->is_end_of_word = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

void insert(trie_node *root, char *word)
{
    int length = strlen(word);
    trie_node *current = root;
    for (int i = 0; i < length; i++)
    {
        int index = word[i] - '0';
        if (current->children[index] == NULL)
        {
            current->children[index] = create_node();
        }
        current = current->children[index];
    }
    current->is_end_of_word = 1;
}

int search(trie_node *root, char *word)
{
    int length = strlen(word);
    trie_node *current = root;
    for (int i = 0; i < length; i++)
    {
        int index = word[i] - '0';
        if (current->children[index] == NULL)
        {
            return 0;
        }
        current = current->children[index];
    }
    return (current != NULL && current->is_end_of_word);
}

int delete(trie_node *root, char *word)
{
    int length = strlen(word);
    trie_node *current = root;
    for (int i = 0; i < length; i++)
    {
        int index = word[i] - '0';
        if (current->children[index] == NULL)
        {
            return 0;
        }
        current = current->children[index];
    }
    current->is_end_of_word = 0;
    return 1;
}

void print_words(trie_node *root, char word[], int level)
{
    if (root->is_end_of_word)
    {
        word[level] = '\0';
        printf("%s\n", word);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != NULL)
        {
            word[level] = i + '0';
            print_words(root->children[i], word, level + 1);
        }
    }
}

void print_trie(trie_node *root)
{
    char word[100];
    print_words(root, word, 0);
}

int main()
{
    trie_node *root = create_node();

    insert(root, "123");
    insert(root, "12");
    insert(root, "456");
    insert(root, "789");
    insert(root, "45");
    insert(root, "7890");

    printf("Trie contents:\n");
    print_trie(root);

    printf("\nSearching for '123': %d\n", search(root, "123"));
    printf("Searching for '456': %d\n", search(root, "456"));
    printf("Searching for '7890': %d\n", search(root, "7890"));
    printf("Searching for '12': %d\n", search(root, "12"));

    printf("\nDeleting '12': %d\n", delete (root, "12"));

    printf("\nTrie contents after deletion:\n");
    print_trie(root);

    printf("\nSearching for '12': %d\n", search(root, "12"));
    printf("Searching for '123': %d\n", search(root, "123"));

    return 0;
}
