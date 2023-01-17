#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUM_CHARS 256

typedef struct trienode {
     struct trienode *children[NUM_CHARS];
    bool terminal;
} trienode;

trienode *createnode() {
    trienode *newnode = malloc(sizeof *newnode);

    for (int i=0; i < NUM_CHARS; i++) {
        newnode->children[i] = NULL;
    }
    newnode->terminal = false;
    return newnode;
}

bool trieinsert(trienode **root, char *signedtext) {
    if (*root == NULL) {
        *root = createnode();
    }

    unsigned char *text = (unsigned char *)signedtext;
    trienode *tmp = *root;
    int length = strlen(signedtext);

    for (int i=0; i < length; i++) {
        if (tmp->children[text[i]] == NULL) {
            //create a new node
            tmp->children[text[i]] = createnode();
        }
        tmp = tmp->children[text[i]];
    }
    if (tmp->terminal) {
        return false;
    } else {
        tmp->terminal = true;
        return true;
    }
}

void printtrie_rec(trienode *node, unsigned char *prefix, int length) {
    unsigned char newprefix[length+2];
    memcpy(newprefix, prefix, length);
    newprefix[length+1] = 0;

    if (node->terminal) {
        printf("WORD: %s\n", prefix);
    }

    for (int i=0; i < NUM_CHARS; i++) {
        if(node->children[i] != NULL) {
            newprefix[length] = i;
            printtrie_rec(node->children[i], newprefix, length+1);
        }
    }
}

void printtrie(trienode * root) {
    if (root == NULL) {
        printf("TRIE EMPTY!\n");
        return;
    }
    printtrie_rec(root, NULL, 0);
}

int main() {
    trienode * root = NULL;

    trieinsert(&root, "KIT");
    trieinsert(&root, "CATTLE");
    trieinsert(&root, "KIN");
    trieinsert(&root, "CAT");
    trieinsert(&root, "HAPPY");
    printtrie(root);
}