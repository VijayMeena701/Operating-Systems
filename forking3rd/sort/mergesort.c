#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//Merge Function
void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}
// Sort Function 
void mergeSort(int arr[], int l ,int r){
    if(l < r){
        int m = l + (r-l)/2;
        if(vfork() == 0){
            mergeSort(arr,l,m);
            exit(0);
        }
        else {
            mergeSort(arr,m+1,r);
            merge(arr,l,m,r);
        }
    }
}
// Print Function
void printArray(int A[], int size){
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
// Driver Function
int main(){
    int range;
    printf("Enter the size of the input : ");
    scanf("%d",&range);
    int arr[range]; 
    printf("Enter the input : \n");
    for(int i=0;i<range;i++){
        scanf("%d",&arr[i]);
    }
    
    printf("%d\n",range);
    printf("Given array is \n");
    printArray(arr, range);

    mergeSort(arr, 0, range - 1);

    printf("\nSorted array is \n");
    printArray(arr, range);
    return 0;
}