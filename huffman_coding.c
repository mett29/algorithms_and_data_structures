#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 11 // Number of characters * 2 - 1

/*
Consider C as a set of n characters. Each element c in C is an object with an attribute c.freq 
that defines its frequency. The algorithm builds a tree that corresponds to the optimal coding
according to a bottom-up scheme.

It starts from a set of |C| leaves (here {a,b,c,d,e,f}) and it computes a series of mergers to build
the final tree.

More info can be found here --> https://en.wikipedia.org/wiki/Huffman_coding
*/

struct bin_tree {
    char character;
    int occurrence_frequency;
    struct bin_tree *right, *left, *parent;
};
typedef struct bin_tree node;

/* In order display */
void print_inorder(node* tree) {
    if (tree) {
        print_inorder(tree->left);
        printf("%c\t",tree->character);
        printf("%d\n",tree->occurrence_frequency);
        print_inorder(tree->right);
    }
}

/* Search the minimum value, not considering the left child and the ones already analyzed, i.e. those with a parent node */
node* search_min(node** actual_nodes, int excluded_value) {
    int occurrences[MAX_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0};
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (actual_nodes[i]->occurrence_frequency != excluded_value && actual_nodes[i]->parent == NULL) {
            occurrences[i] = actual_nodes[i]->occurrence_frequency;
        }
    }

    int min_value;
    if (occurrences[0] != 0) {
        min_value = occurrences[0];
    } else {
        min_value = 100000;
    }
    for (int i = 1; i < MAX_LENGTH; i++) {
        if (occurrences[i] < min_value && occurrences[i] != 0) {
            min_value = occurrences[i];
        }
    }

    for (int i = 0; i < MAX_LENGTH; i++) {
        if (actual_nodes[i]->occurrence_frequency == min_value) {
            return actual_nodes[i];
        }
    }
    return NULL;
}

void huffman(node** actual_nodes) {
    for (int i = 0; i < MAX_LENGTH/2; i++) {
        node* left = search_min(actual_nodes, -1); // -1 since here it does not matter
        node* right = search_min(actual_nodes, left->occurrence_frequency); // exclude the left child

        printf("left: %d\n", left->occurrence_frequency);
        printf("right: %d\n", right->occurrence_frequency);

        /* Create a new node, parent, with value the sum of left and right */
        node* parent = (node*)malloc(sizeof(node));
        parent->left = left;
        parent->right = right;
        parent->parent = NULL;
        parent->occurrence_frequency = left->occurrence_frequency + right->occurrence_frequency;
        left->parent = parent;
        right->parent = parent;
    
        /* Insert the new node into actual_nodes */
        int empty_index;
        for (int i = 0; i < MAX_LENGTH; i++) {
            if (actual_nodes[i]->occurrence_frequency == 0) {
                empty_index = i;
            }
        }
        actual_nodes[empty_index] = parent;

        /*for (int i = 0; i < MAX_LENGTH; i++) {
            printf("%d\t", actual_nodes[i]->occurrence_frequency);
        }*/

        /* If this is the last iteration, then print the final tree */
        if (i == MAX_LENGTH/2 - 1) {
            printf("\nIn order display:\n");
            print_inorder(parent);
        }
    }
}

void main()
{
    node* leaves[MAX_LENGTH];

    for (int i = 0; i < MAX_LENGTH; i++) {
        leaves[i] = (node*)malloc(sizeof(node));
        leaves[i]->left = NULL;
        leaves[i]->right = NULL;
        leaves[i]->parent = NULL;
    }

    leaves[0]->character = 'a';
    leaves[0]->occurrence_frequency = 45;
    leaves[1]->character = 'b';
    leaves[1]->occurrence_frequency = 13;
    leaves[2]->character = 'c';
    leaves[2]->occurrence_frequency = 12;
    leaves[3]->character = 'd';
    leaves[3]->occurrence_frequency = 16;
    leaves[4]->character = 'e';
    leaves[4]->occurrence_frequency = 9;
    leaves[5]->character = 'f';
    leaves[5]->occurrence_frequency = 5;

    huffman(leaves);
}