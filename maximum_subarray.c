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

int* find_max_crossing_subarray(int* array, int low, int mid, int high) {
    int left_sum = -1000;
    int right_sum = -1000;
    int max_left, max_right;
    int sum = 0;

    for (int i = mid; i >= low; i--) {
        sum += array[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    sum = 0;
    for (int j = mid + 1; j <= high; j++) {
        sum += array[j];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }
    int* result = (int*)malloc(sizeof(int)*3);;
    result[0] = max_left;
    result[1] = max_right;
    result[2] = left_sum + right_sum;
    return result;
}

int* find_maximum_subarray(int* array, int low, int high) {
    int left_low, left_high, left_sum, right_low, right_high, right_sum, cross_low, cross_high, cross_sum;

    // If array with 1 element
    if (high == low) {
        int* result = (int*)malloc(sizeof(int)*3);
        result[0] = low;
        result[1] = high;
        result[2] = array[low];
        return result;
    } else {
        int mid = trunc((low + high) / 2);

        // Find the maximum subarrays left and right recursively
        int* left_result = (int*)malloc(sizeof(int)*3);
        left_result = find_maximum_subarray(array, low, mid);
        left_low = left_result[0];
        left_high = left_result[1];
        left_sum = left_result[2];

        int* right_result = (int*)malloc(sizeof(int)*3);
        right_result = find_maximum_subarray(array, mid + 1, high);
        right_low = right_result[0];
        right_high = right_result[1];
        right_sum = right_result[2];
        
        // Find the maximum subarray which contains the mid point
        int* cross_result = (int*)malloc(sizeof(int)*3);
        cross_result = find_max_crossing_subarray(array, low, mid, high);
        cross_low = cross_result[0];
        cross_high = cross_result[1];
        cross_sum = cross_result[2];

        if (left_sum >= right_sum && left_sum >= cross_sum) return left_result;
        else if (right_sum >= left_sum && right_sum >= cross_sum) return right_result;
        else return cross_result;
    }
}

int main() {

    // Seed to avoid getting the same sequence of random numbers
    time_t t;
    srand((unsigned)time(&t));

    // Fill our array with ten numbers from -50 to 50
    for (int i = 0; i < 10; i++) {
        array[i] = rand() % 100 - 50;
    }

    // Print the generated numbers
    printf("Generated array: \n");
    print_array(array);

    // Find the maximum subarray
    int* result = (int*)malloc(sizeof(int)*3);
    result = find_maximum_subarray(array, 0, 9);

    // Print the maximum subarray array
    printf("\nSubarray from %i to %i\n", result[0], result[1]);
    printf("Sum = %i\n", result[2]);

}