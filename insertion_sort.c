#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Array of 10 elements
int array[10];

void print_array(int* array) {
    for (int i = 0; i < 10; i++) {
        printf("%i\n", array[i]);
    }
}

void insertion_sort(int* array) {
    for (int j = 1; j <= 10; j++) {
        int key = array[j];
        int i = j - 1;
        while (i >= 0 && array[i] > key) {
            array[i + 1] = array[i];
            i--;
        }
        array[i + 1] = key;
    }
}

int main() {

    // Seed to avoid getting the same sequence of random numbers
    time_t t;
    srand((unsigned)time(&t));

    // Fill our array with ten numbers from 0 to 100
    for (int i = 0; i < 10; i++) {
        array[i] = rand() % 100;
    }

    // Print the generated numbers
    printf("Generated array: \n");
    print_array(array);

    // Run the insertion sort algorithm
    insertion_sort(array);

    // Print the sorted array
    printf("\nSorted array: \n");
    print_array(array);
}