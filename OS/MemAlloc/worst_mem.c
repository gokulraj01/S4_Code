// Author: Gokul Raj, 235, R4A, CSE
// Memory Allocation: Worst Fit
#include <stdio.h>
#include <stdlib.h>

void main(){
    int nm, np;
    printf("Enter memory segment count: ");
    scanf("%d", &nm);
    int *freeSpace = malloc(sizeof(int)*nm);
    printf("Sizes: ");
    for(int i=0; i<nm; i++)
        scanf("%d", &freeSpace[i]);
    
    printf("Enter process count: ");
    scanf("%d", &np);
    int *processList = malloc(sizeof(int)*np);
    int *allocationList = malloc(sizeof(int)*np);
    printf("Process Need: ");
    for(int i=0; i<np; i++){
        scanf("%d", &processList[i]);
        allocationList[i] = -1;    
    }
    
    // Do worst fit algorithm
    for(int i=0; i<np; i++){
        int diff = -1;
        int worstMem = -1;
        for(int j=0; j<nm; j++){
            if(freeSpace[j] >= processList[i] && freeSpace[j]-processList[i] > diff){
                worstMem = j;
                diff = freeSpace[j]-processList[i];
            }
        }
        if(worstMem > -1){
            freeSpace[worstMem] -= processList[i];
            allocationList[i] = worstMem;
        }
    }
    
    // Display Allocation List
    putchar('\n');
    for(int i=0; i<nm; i++){
        for(int j=0; j<np; j++){
            if(allocationList[j] == i)
                printf("P%d ", j+1);
        }
        printf("(%d) | ", freeSpace[i]);
    }
    printf("\nUnallocated: ");
    int allocFlag = 1;
    for(int j=0; j<np; j++){
        if(allocationList[j] == -1){
            allocFlag = 0;
            printf("P%d ", j+1);    
        }
    }
    if(allocFlag)
        printf("None");
    putchar('\n');
}
