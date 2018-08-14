#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* next;
};

typedef struct node node;

void display_list(node* head) {
    if (head == NULL) return;
    printf("%i -> ", head->value);
    display_list(head->next);
    printf("\n");
}

node* insert_top(node* head, int value) {
    
    // Create a new node
    node* new_node = (node*)malloc(sizeof(node));

    if (new_node == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }

    new_node->value = value;
    // Prepend the new node
    new_node->next = head;
    // Head is now pointing to the new node
    head = new_node;
 
    return head;
}

void insert_bottom(node* head, int value) {

    // Go to the tail of the list
    node *cursor = head;
    while(cursor->next != NULL)
        cursor = cursor->next;
    
    // Create a new node
    node* new_node = (node*)malloc(sizeof(node));

    if (new_node == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }

    // Append the new node
    new_node->value = value;
    cursor->next = new_node;
}

node* search_node(node* head, int value) {
    node* cursor = head;
    while(cursor->value != value) {
        cursor = cursor->next;
        if (cursor == NULL) break;
    }
    
    return cursor;
}

node* delete_node(node* head, int value) {

    // If the value does not exist
    if (search_node(head, value) == NULL) {
        printf("The element does not exist.\n");
        return head;
    }

    // If the node is the head
    if (head->value == value) {
        head = head->next; 
        return head;
    }

    // Else
    node* cursor = head;
    while(cursor->next->value != value)
        cursor = cursor->next;

    // If the node is at the end
    if (cursor->next->next == NULL) {
        cursor->next = NULL;
        return head;
    }

    // Else if the node is in the middle
    node* tmp = cursor->next;
    cursor->next = tmp->next;
    tmp->next = NULL;
    free(tmp);

    return head;
}

int main() {

    node* head;

    // Some tests
    head = insert_top(head, 42);
    display_list(head);
    insert_bottom(head, 3);
    insert_bottom(head, 27);
    display_list(head);
    head = delete_node(head, 3);
    display_list(head);
    insert_bottom(head, 50);
    display_list(head);
    head = delete_node(head, 42);
    display_list(head);
    head = insert_top(head, 42);
    display_list(head);
    head = delete_node(head, 50);
    display_list(head);
    head = delete_node(head, 12);
}