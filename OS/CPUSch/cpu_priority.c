// Author: Gokul Raj, 235, R4A, CSE
// CPU Scheduling: Priority
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process{
    int arrivalTime;
    int burstTime;
    int priority;
};

void priorityCPU(struct Process **processList, int n){
    int time = 0, avgWait = 0, avgTurnaround = 0;
    printf("\nPID\tWait\tTurnAround\n");
    // Do scheduling for each process
    for(int j=0; j<n; j++){
        int minPri = INT_MAX, chosenProcess = -1, minTime = INT_MAX;
        // Find process with lowest priority
        while(chosenProcess == -1){
            for(int i=0; i<n; i++){
                // IF ((current priority lower) OR (equal priority, but arrived earlier)
                //      AND already arrived)
                // AND not already done
                if(((processList[i]->priority < minPri || (processList[i]->priority == minPri && processList[i]->arrivalTime <= minTime)) && processList[i]->arrivalTime <= time) && processList[i]->burstTime != -1){
                    chosenProcess = i;
                    minPri = processList[i]->priority; minTime = processList[i]->arrivalTime;
                }
            }
            if(chosenProcess == -1) time += 1;
        }
        // Do the chosen process
        int wt = time - processList[chosenProcess]->arrivalTime;
        time += processList[chosenProcess]->burstTime;
        int tat = time - processList[chosenProcess]->arrivalTime;
        processList[chosenProcess]->burstTime = -1;
        avgWait += wt; avgTurnaround+= tat;
        printf("P%d\t%d\t%d\n", chosenProcess+1, wt, tat);
    }
}

void main(){
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);

    struct Process **processList = malloc(sizeof(processList) * n);
    for(int i=0; i<n; i++)
        processList[i] = malloc(sizeof(struct Process));

    printf("Enter details in order of arrival\n");
    printf("Arrival Times: ");
    for(int i=0; i<n; i++)
        scanf("%d", &processList[i]->arrivalTime);
    
    printf("Burst Times: ");
    for(int i=0; i<n; i++)
        scanf("%d", &processList[i]->burstTime);
    
    printf("Priorities: ");
    for(int i=0; i<n; i++)
        scanf("%d", &processList[i]->priority);

    // Perform scheduling
    priorityCPU(processList, n);
}