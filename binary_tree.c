#include <stdlib.h>
#include <stdio.h>

struct bin_tree {
    int data;
    struct bin_tree *right, *left, *parent;
};
typedef struct bin_tree node;

/* Insert a new node */
void insert(node** tree, int val) {
    node *temp = NULL;
    if (!(*tree)) {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if (val < (*tree)->data) {
        insert(&(*tree)->left, val);
        (*tree)->left->parent = *tree;
    }
    else if (val > (*tree)->data) {
        insert(&(*tree)->right, val);
        (*tree)->right->parent = *tree;
    }
}

/* In order display */
void print_inorder(node* tree) {
    if (tree) {
        print_inorder(tree->left);
        printf("%d\n",tree->data);
        print_inorder(tree->right);
    }
}

/* Delete the entire tree */
void deltree(node* tree) {
    if (tree) {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

/* Search the node with value <val> in the tree */
node* search(node** tree, int val) {
    if (!(*tree)) {
        return NULL;
    }
    if (val < (*tree)->data) {
        search(&((*tree)->left), val);
    }
    else if (val > (*tree)->data) {
        search(&((*tree)->right), val);
    }
    else if (val == (*tree)->data) {
        return *tree;
    }
}

/* Search the node with the minimum value */
node* tree_minimum(node* tree) {
    if (!tree) { return NULL; }
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

/* Search the node with the maximum value */
node* tree_maximum(node* tree) {
    if (!tree) { return NULL; }
    while (tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}

/* If all the keys are distinct, the successor of a node x is the node with the smallest key that is greater than x.key */
node* tree_successor(node* tree, int key) {
    node* searched_node = search(&tree, key);
    printf("Computing the successor of %d...\n", searched_node->data);
    if (searched_node->right) {
        return tree_minimum(searched_node->right);
    }
    node *y = searched_node->parent;
    while (y && searched_node->data == y->right->data) {
        searched_node = y;
        y = y->parent;
    }
    return y;
}

void main()
{
    node *root;
    node *tmp;

    root = NULL;
    /* Inserting nodes into tree */
    insert(&root, 15);
    insert(&root, 6);
    insert(&root, 18);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 17);
    insert(&root, 20);
    insert(&root, 2);
    insert(&root, 4);
    insert(&root, 13);
    insert(&root, 9);

    /* Printing nodes of tree */
    printf("In order display:\n");
    print_inorder(root);

    /* Printing minimum and maximum element of the tree */
    printf("Min value: %d\n", tree_minimum(root)->data);
    printf("Max value: %d\n", tree_maximum(root)->data);

    /* Successor of a node in the order determined by a symmetric crossing */
    printf("Successor: %d\n", tree_successor(root, 13)->data);

    int nodo;
    printf("Insert the node you want to search: ");
	scanf("%i", &nodo);

    /* Search node into tree */
    tmp = search(&root, nodo);
    if (tmp) { printf("Node found. Searched node = %d\n", tmp->data); }
    else { printf("Element not found in the tree.\n"); }

    /* Deleting all nodes of tree */
    deltree(root);
}