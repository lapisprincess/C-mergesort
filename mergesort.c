/*
    "mergesort.c"
    Matilda Lerner
    CS 281, Adam Smith

    A simple mergesort implementation in C
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// prototypes
void printArray(int *array, int left, int right);
void merge(int *array, int left, int mid, int right);
void mergeSortHelper(int *array, int left, int right);
void mergeSort(int *array, int right);
int main(int argc, char *argv[]);

/*
    function which takes an array and prints a chunk of it,
    given left and right indices.

    input:
        int *array: array to print from
        int left: index of leftmost bound
        int right: index to stop at
*/
void printArray(int *array, int left, int right) {
    printf("[");
    for (int i = left; i < right-1; i++) 
        printf("%d, ", array[i]);
    printf("%d]\n", array[right-1]);
}

/*
    merge function which takes an array and "merges" the items
    between given indices. Merging entails incrementing through left
    and right chunks, pulling the smaller value of each index to
    put in the new array.

    input:
        MUTABLE int *array: array to do merge on
        int left: index of start of left array
        int mid: index indicating cutoff between left an right arrays
        int right: index demarking end of right half
*/
void merge(int *array, int left, int mid, int right) {
    int i, j, len;
    i = 0;
    j = mid - left;
    len = right - left;

    int *copy = (int*)malloc(len * sizeof(int));

    for (int k = 0; k < len; k++) copy[k] = array[k + left];

    for (int k = left; k < right; k++) {
        // either i or j are past their limit
        if (i >= mid - left)            array[k] = copy[j++];
        else if (j >= right - left)     array[k] = copy[i++];
        // or we do a direct comparison
        else if (copy[j] < copy[i])     array[k] = copy[j++];
        else                            array[k] = copy[i++];
    }

    free(copy);
}

/*
    recursive function which takes an array, a left index, and a right
    index, halves the array into two parts, recurses on those two parts,
    then merges them back together using merge(), an algorithm called
    merge-sorting.

    base case:
        either when left overlaps right, or the halfway marker matches
        the left index, indicating that there is only one item in the array

    inputs:
        MUTABLE int *array: array which is being merge-sorted
        int left: leftmost index within array
        int right: rightmost index within array
*/
void mergeSortHelper(int *array, int left, int right) {
    int half = left + (right - left) / 2;

    // array is as small as can be
    if ((right <= left) || (half == left)) return;

    mergeSortHelper(array, left, half);
    mergeSortHelper(array, half, right);

    merge(array, left, half, right);
}

// call to recursive function
void mergeSort(int *array, int size) { mergeSortHelper(array, 0, size); }


/*
    program main! 
    does a couple of things, including interpreting arguments,
    calling mergeSort(), randomizing the array and printing it 
    before and after sorting, and timing mergeSort(), outputting
    the total duration in ms to the command line.
*/
int main(int argc, char *argv[]) {
    int size, start, stop;

    // handle input
    if (argc != 2) {
        printf("Please input the length of the array!\n");
        return 0;
    }
    size = atoi(argv[1]);
    if (!size) {
        printf("Please input an integer!\n");
        return 0;
    }

    // allocate space for main array, then randomize items
    int *array = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) 
        array[i] = rand() % size;


    printf("Doing sort on array of size %d...\n", size);

    if (size <= 100) {
        printf("Before: ");
        printArray(array, 0, size);
    }
    
    // call to mergeSort with timers before and after
    time_t before = clock();
    mergeSort(array, size);
    time_t after = clock();
    int difference = (after - before) / 1000;

    if (size <= 100) {
        printf("After: ");
        printArray(array, 0, size);
    }

    printf("Time elapsed: %d ms\n", difference);

    free(array); 
    
    return 1; // program ran successfully :)
}