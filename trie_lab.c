#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int count;
    struct Trie *child[26];
};

void insert(struct Trie **ppTrie, char *word) {
    struct Trie *current = *ppTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (current->child[index] == NULL) {
            current->child[index] = (struct Trie*) malloc(sizeof(struct Trie));
            current->child[index]->count = 0;
            for (int j = 0; j < 26; j++) {
                current->child[index]->child[j] = NULL;
            }
        }
        current = current->child[index];
    }
    current->count++;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (current->child[index] == NULL) {
            return 0;
        }
        current = current->child[index];
    }
    return current->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        pTrie->child[i] = deallocateTrie(pTrie->child[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    // read the number of words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    struct Trie* trie = (struct Trie*) malloc(sizeof(struct Trie));
    trie->count = 0;
    for (int i = 0; i < 26; i++) {
        trie->child[i] = NULL;
    }

    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }

    for (int i = 0; i < 5; i++) {
        printf("%s: %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("Error: trie not deallocated properly.\n");
    }

    return 0;
}
