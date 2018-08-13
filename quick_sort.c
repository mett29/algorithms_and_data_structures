#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Array of 10 elements
int array[10];

void print_array(int* array) {
    for (int i = 0; i < 10; i++) {
        printf("%i\n", array[i]);
    }
}

int random_number(int min, int max) {
    return (rand() % (max + 1 - min)) + min;
}

int partition(int* array, int p, int r) {
    int pivot = array[r];
    int i = p - 1;

    for (int j = p; j <= r - 1; j++) {
        if (array[j] <= pivot) {
            i++;
            // Swap
            int tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
        }
    }
    // Swap
    int tmp2 = array[i + 1];
    array[i + 1] = array[r];
    array[r] = tmp2;

    return i + 1;
}

// Instead of always using array[r] as pivot, we choose it randomly from the subarray array[p...r]
int randomized_partition(int* array, int p, int r) {
    int i = random_number(p, r);
    int tmp = array[r];
    array[r] = array[i];
    array[i] = tmp;
    return partition(array, p, r);
}

void quick_sort(int* array, int p, int r) {
    if (p < r) {
        int q = partition(array, p, r);
        quick_sort(array, p, q - 1);
        quick_sort(array, q + 1, r);
    }
}

void randomized_quick_sort(int* array, int p, int r) {
    if (p < r) {
        int q = randomized_partition(array, p, r);
        randomized_quick_sort(array, p, q - 1);
        randomized_quick_sort(array, q + 1, r);
    }
}

int main() {

    time_t t;
    srand((unsigned)time(&t));
    
    // Fill our array with ten numbers from 0 to 100
    for (int i = 0; i < 10; i++) {
        array[i] = rand() % 100;
    }

    // Print the generated numbers
    printf("Generated array: \n");
    print_array(array);

    // Run the quick sort algorithm
    randomized_quick_sort(array, 0, 9);

    // Print the sorted array
    printf("\nSorted array: \n");
    print_array(array);

}