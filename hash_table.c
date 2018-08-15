#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _list_t_ {
    char* str;
    struct _list_t_ *next;
} list_t;

typedef struct _hash_table_t_ {
    int size; 
    list_t** table;
} hash_table_t;

hash_table_t* create_hash_table(int size) {
    hash_table_t* new_table;

    if (size < 1) return NULL; 

    // Attempt to allocate memory for the hash_table struct
    if ((new_table = malloc(sizeof(hash_table_t))) == NULL) {
        return NULL;
    }

    // Attempt to allocate memory for the table
    if ((new_table->table = malloc(sizeof(list_t*) * size)) == NULL) {
        return NULL;
    }

    // Initialize the elements of the table
    for(int i = 0; i < size; i++) new_table->table[i] = NULL;

    new_table->size = size;

    return new_table;
}

// BERNSTEIN HASH //
unsigned int hash(hash_table_t *hashtable, char *str) {
    unsigned int hashval;

    /* We start our hash out at 0 */
    hashval = 0;

    /* For each character, we multiply the old hash by 31 and add the current
    * character. Remember that shifting a number left is equivalent to 
    * multiplying it by 2 raised to the number of places shifted. So we 
    * are in effect multiplying hashval by 32 and then subtracting hashval. 
    * Why do we do this? Because shifting and subtraction are much more 
    * efficient operations than multiplication.
    */
    for(; *str != '\0'; str++) hashval = *str + (hashval << 5) - hashval;

    /* We then return the hash value mod the hashtable size so that it will
    * fit into the necessary range
    */
    return hashval % hashtable->size;
}

list_t* lookup_string(hash_table_t* hashtable, char* str) {
    list_t* list;
    unsigned int hashval = hash(hashtable, str);

    for (list = hashtable->table[hashval]; list != NULL; list = list->next) {
        if (!strcmp(str, list->str)) return list;
    }
    return NULL;
}

int add_string(hash_table_t* hashtable, char* str) {
    list_t* new_list;
    list_t* current_list;
    unsigned int hashval = hash(hashtable, str);

    // Attempt to allocate memory for list
    if ((new_list = malloc(sizeof(list_t))) == NULL) return 1;

    // Check if the string already exists
    current_list = lookup_string(hashtable, str);
    
    if (current_list != NULL) return 2;
    
    new_list->str = strdup(str);
    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;

    return 0;
}

int delete_string(hash_table_t* hashtable, char* str) {
    int i;
    list_t* list, *prev;
    unsigned int hashval = hash(hashtable, str);

    // Search the string
    for (prev = NULL, list = hashtable->table[hashval];
    list != NULL && strcmp(str, list->str);
    prev = list,
    list = list->next);

    // If string does not exist
    if (list == NULL) return 1;

    // Otherwise, remove it from the table
    if (prev == NULL) hashtable->table[hashval] = list->next;
    else prev->next = list->next; 

    free(list->str);
    free(list);

    return 0;
}

int count_strings(hash_table_t* hashtable) {
    int i, count = 0;
    list_t* list;

    if (hashtable == NULL) return -1;

    // Count items
    for (i = 0; i < hashtable->size; i++) {
        for (list = hashtable->table[i]; list != NULL; list = list->next) count++;
    }

    return count;
}

void display_table(hash_table_t* hashtable){
  int i;
  list_t *t;
  for (i = 0; i < hashtable->size; i++) {
    if (hashtable->table[i] == NULL) printf("()\n");
    else {
        t = hashtable->table[i];
        for (;t != NULL; t = t->next) printf("%s\n",t->str);
    }
  }
}

int main (void) {

    /* TESTING */
    hash_table_t* my_hash_table;
    int size_of_table = 12;

    my_hash_table = create_hash_table(size_of_table);

    add_string(my_hash_table, "test");

    display_table(my_hash_table);

    list_t *item = lookup_string(my_hash_table, "test");
    printf("Found: %s\n", item->str);

    printf("The hashtable contains %i elements.\n", count_strings(my_hash_table));

    delete_string(my_hash_table, "test");
    
    display_table(my_hash_table);

    printf("The hashtable contains %i elements.\n", count_strings(my_hash_table));
}