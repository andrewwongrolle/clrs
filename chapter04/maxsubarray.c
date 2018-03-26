/* maxsubarray.c 
 * Computes the maximum subarray of an array of integers.
 * The maxiumum subarray is defined as the contiguous 
 * subarray with the greatest element-wise sum.
 * */

#include <stdio.h>
#include <stdlib.h>

#define MAXSZ 1000 

/* custom type for returning subarrays */
struct subarray {
    int first;
    int last;
};

struct subarray maxsubarray(int array[], struct subarray s);
struct subarray maxcrossingsubarray(int array[], struct subarray s);
int sumsubarray(int array[], struct subarray s);

int main(int argc, char* argv[]) {
    char line[MAXSZ];
    int A[MAXSZ];
    int i = 0;
    int len, n;
    printf("Enter array: ");
    if (fgets(line, sizeof(line), stdin)) {
        char* lp = line;
        while (i < MAXSZ && (sscanf(lp, "%d %n", &A[i], &n) == 1)) {
            lp += n;
            i++;
        }
        if (i < 1) {
            printf("Error: unable to parse array\n");
            return -1;
        }
        len = i;
        struct subarray s = {0, len - 1};
        struct subarray max = maxsubarray(A, s);
        printf("Array: [ ");
        for (int j = 0; j < len; j++) 
            printf("%d ", A[j]);
        printf("]\n");
        printf("has the max subarray [ ");
        for (int j = max.first; j <= max.last; j++) 
            printf("%d ", A[j]);
        printf("]\n");
    }
    else {
        printf("Unable to parse input line\n");
        return -1;
    }
}

struct subarray maxsubarray(int A[], struct subarray s) {
    // base case: the max subarray of a size 1 array is itself
    if (s.first == s.last)
        return s;
    int mid = (s.first+ s.last) / 2;
    struct subarray left = {s.first, mid};
    struct subarray right = {mid + 1, s.last};
    // recursively find max subarrays of left and right halves
    left = maxsubarray(A, left);
    right = maxsubarray(A, right);
    // find max subarray that crosses between left and right halves
    struct subarray crossing = maxcrossingsubarray(A, s);
    // return the subarray with the max sum
    int leftsum = sumsubarray(A, left); 
    int rightsum = sumsubarray(A, right);
    int crosssum = sumsubarray(A, crossing);
    struct subarray max;
    if (leftsum >= rightsum && leftsum >= crosssum)
        max = left;
    else if (rightsum >= leftsum && rightsum >= crosssum)
        max = right;
    else
        max = crossing;
    return max;
}

struct subarray maxcrossingsubarray(int A[], struct subarray s) {
    int mid = (s.first+ s.last) / 2;
    int leftsum, rightsum, leftind, rightind, i, sum;
    for (i = mid, sum = 0; i >= s.first; i--) {
        sum += A[i];
        if (i == mid || sum > leftsum) {
            leftsum = sum;
            leftind = i;
        }
    }
    for (i = mid + 1, sum = 0; i <= s.last; i++) {
        sum += A[i];
        if (i == mid + 1 || sum > rightsum) {
            rightsum = sum;
            rightind = i;
        }
    }
    struct subarray max = {leftind, rightind};
    return max;
}

int sumsubarray(int A[], struct subarray s) {
    int sum = 0;
    for (int i = s.first; i <= s.last; i++) 
        sum += A[i];
    return sum;
}
