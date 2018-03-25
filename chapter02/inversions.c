/* inversions.c 
 * Counts the number of inversions in an array of integers
 * Inversions are defined as pairs of elements A[i] > A[j] with i < j
 * Algorithm based on merge sort
 * */

#include <stdio.h>
#include <stdlib.h>

#define MAXSZ 1000 

int inversions(int array[], int left, int right);

int main(int argc, char* argv[]) {
    char line[MAXSZ];
    int perm[MAXSZ];
    int i = 0;
    int len, n;
    printf("Enter permutation: ");
    if (fgets(line, sizeof(line), stdin)) {
        char* lp = line;
        while ((sscanf(lp, "%d %n", &perm[i], &n) == 1) && i < MAXSZ) {
            lp += n;
            i++;
        }
        len = i;
        printf("Array: ");
        for (int j = 0; j < len; j++) 
            printf("%d ", perm[j]);
        printf("has %d inversions\n", inversions(perm, 0, len-1));
    }
    else {
        printf("Unable to parse input line\n");
        return -1;
    }
}

int inversions(int array[], int left, int right) {
    // base case: an array of size 1 has no inversions
    if (left == right)
        return 0;
    int mid, numi, n1, n2;
    mid = (left + right) / 2;
    numi = inversions(array, left, mid) + inversions(array, mid + 1, right);
    // create temporary arrays
    n1 = mid - left + 1; // length of left array
    n2 = right - mid; // length of right array
    int larray[n1];
    int rarray[n2];
    for (int i = 0; i < n1; i++) 
        larray[i] = array[left + i];
    for (int i = 0; i < n2; i++) 
        rarray[i] = array[mid + 1 + i];
    // merge left and right arrays in sorted order
    int j = 0;
    int k = 0;
    for (int i = 0, n = right - left + 1; i < n; i++) {
        // taking from left array
        if ((larray[j] < rarray[k]) || k == n2) {
            array[left + i] = larray[j++];
        }
        // taking from right array
        else if ((rarray[k] < larray[j]) || j == n1) {
            array[left + i] = rarray[k++]; 
            numi += (n1 - j); 
        }
    }
    return numi;
}
