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

void merge(int* array, int p, int q, int r) {

    int n1 = q - p + 1;
    int n2 = r - q;

    int left[n1];
    int right[n2];

    int i, j, k;
    for (i = 0; i < n1; i++) {
        left[i] = array[p + i];
    }
    for (j = 0; j < n2; j++) {
        right[j] = array[q + j + 1];
    }

    i = 0; 
    j = 0; 
    k = p;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        array[k] = left[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        array[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int* array, int p, int r) {
    if (p < r) {
        int q = trunc((p + r) / 2);
        merge_sort(array, p, q);
        merge_sort(array, q + 1, r);
        merge(array, p, q, r);
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
    merge_sort(array, 0, 9);

    // Print the sorted array
    printf("\nSorted array: \n");
    print_array(array);

}