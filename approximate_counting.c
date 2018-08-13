#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int counter = 1;

// Generate [value of counter] numbers between 0 and 1
int* generate_random_bits(int counter) {
    int* bits = (int*)malloc(sizeof(int)*counter);
    for (int i = 0; i < counter; i++) {
        bits[i] = rand() % 2;
    }
    return bits;
}

int main() {
    time_t t;
    srand((unsigned)time(&t));

    while(1) {
        // Generate [value of counter] bits
        int* bits = (int*)malloc(sizeof(int)*counter); 
        bits = generate_random_bits(counter);

        // Logic AND
        int and = 1;
        for (int i = 0; i < counter; i++) {
            and = and & bits[i];
        }

        // Sum up the AND result to the counter
        counter += and;
        // Print the counter only if changed
        if (and)
            printf("%d\n", counter);
    }
}