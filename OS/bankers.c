// Author: Gokul Raj, 235, R4A, CSE
// Implementation of Bankers Algorithm for Deadlock Detection
#include <stdio.h>
#include <stdlib.h>

struct Process{
    int *need; int done;
};

void bankersAlg(struct Process **needMat, int **allocMat, int *freeRes,
                int res_n, int proc_n){
    // Perform check for all process
    int safeCondition = 0;
    for(int i=0; i<proc_n; i++){
        safeCondition = 0;
        int selectedProc = -1;
        // Loop through all process to find one that can be done now
        for(int j=0; j<proc_n; j++){
            int match = 1;
            for(int k=0; k<res_n; k++){
                // printf("Need: %d, Free: %d\n", needMat[j]->need[k], freeRes[k]);
                if(needMat[j]->need[k] > freeRes[k]){
                    match = 0;
                    break;
                }
            }
            // If current process is do-able and not already done
            if(match && needMat[j]->done != 1){
                selectedProc = j;
                break;
            }
        }
        if(selectedProc > -1){
            safeCondition = 1;
            printf("Doing Process %d!!\n", selectedProc+1);
            needMat[selectedProc]->done = 1;
            // Release resources from this process to pool
            for(int k=0; k<res_n; k++)
                freeRes[k] += allocMat[selectedProc][k];
            // // Display free resources
            // printf("Free: ");
            // for(int k=0; k<res_n; k++)
            //     printf("%d, ",freeRes[k]);
            // putchar('\n');
        }
        else break;
    }
    if(safeCondition)
        printf("All done!! SAFE\n");
    else
        printf("No more processes can be satisfied!! UNSAFE.\n");
}

void main(){
    int res_n, proc_n;
    printf("Resource Count: ");
    scanf("%d", &res_n);
    int *freeRes = malloc(sizeof(int)*res_n);
    printf("Free Resources: ");
    for(int i=0; i<res_n; i++)
        scanf("%d", &freeRes[i]);
    
    printf("Process Count: ");
    scanf("%d", &proc_n);

    int **allocMat = malloc(sizeof(allocMat)*proc_n);
    for(int i=0; i<proc_n; i++)
        allocMat[i] = malloc(sizeof(int)*res_n);
    for(int i=0; i<proc_n; i++){
        printf("Allocation for Process %d: ", i+1);
        for(int j=0; j<res_n; j++)
            scanf("%d", &allocMat[i][j]);
    }

    struct Process **needMat = malloc(sizeof(needMat)*proc_n);
    for(int i=0; i<proc_n; i++){
        needMat[i] = malloc(sizeof(struct Process));
        needMat[i]->need = malloc(sizeof(int)*res_n);
    }
    for(int i=0; i<proc_n; i++){
        printf("Need for Process %d: ", i+1);
        for(int j=0; j<res_n; j++)
            scanf("%d", &needMat[i]->need[j]);
    }
    // Check safety with Bankers Algorithm
    bankersAlg(needMat, allocMat, freeRes, res_n, proc_n);
}