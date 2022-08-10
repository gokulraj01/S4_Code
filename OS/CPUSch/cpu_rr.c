#include <stdio.h>
#include <stdlib.h>

struct Process{
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

void rrCPU(struct Process **processList, int q, int n){
    int running = 1, timeout = 0;
    int time = 0, avgWait = 0, avgTurnaround = 0;
    printf("\nPID\tWait\tTurnAround\n");
    while(running){
        running = 0;
        for(int i=0; i<n; i++){
            // If some process is incomplete
            if(processList[i]->remainingTime > 0){
                running = 1;
                // If that process has arrived and is runnable
                if(processList[i]->arrivalTime <= time){
                    timeout = 0;
                    // If process will end in this quantum, run and display stats
                    if(processList[i]->remainingTime <= q){
                        time += processList[i]->remainingTime;
                        processList[i]->remainingTime = 0;
                        int tat = time - processList[i]->arrivalTime;
                        int wt = tat - processList[i]->burstTime;
                        avgWait += wt; avgTurnaround+= tat;
                        printf("P%d\t%d\t%d\n", i+1, wt, tat);
                    }
                    // Else, do one quantum and continue
                    else{
                        time += q;
                        processList[i]->remainingTime -= q;
                    }
                }
                // To know when no more processes are left to do now,
                // but some will arrive later in time
                else timeout = 1;
            }
        }
        // Nothing to do now... check in next time slot
        if(running && timeout) time ++;
    }
    avgWait /= n; avgTurnaround /= n;
    printf("\nAverage Waiting Time: %d ms\n", avgWait);
    printf("Average TurnAround Time: %d ms\n", avgTurnaround);
    printf("Runtime: %d ms\n", time);
}

void main(){
    int n, quantum;
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
    for(int i=0; i<n; i++){
        scanf("%d", &processList[i]->burstTime);
        processList[i]->remainingTime = processList[i]->burstTime;
    }

    printf("Time Quantum: ");
    scanf("%d", &quantum);

    // Perform scheduling
    rrCPU(processList, quantum, n);
}