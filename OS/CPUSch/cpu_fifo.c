#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GANTT_SIZE 80

struct Process{
    int arrivalTime;
    int burstTime;
    int start;
    int end;
};

char* numToStr(int n, int *size){
    int digits = 1;
    if(n > 0)
        digits = log10(n) + 1;
    char *op = malloc(digits+1);
    if(n == 0)
        op[0] = '0';
    int i = 0;
    while(n>0){
        op[digits-i-1] = (n%10)+'0';
        n /= 10;
        i++;
    }
    op[digits] = 0;
    *size = digits;
    return op;
}

void makeGantt(struct Process **processList, int *runOrder, int n, int runtime){
    char *chart = malloc(GANTT_SIZE+10), *label = malloc(GANTT_SIZE+10), *title = malloc(GANTT_SIZE+10);
    for(int i=0; i<GANTT_SIZE+10; i++)
        chart[i] = label[i] = title[i] = ' ';
    chart[GANTT_SIZE+9] = label[GANTT_SIZE+9] = title[GANTT_SIZE+9] = 0;

    for(int i=0; i<n; i++){
        int start = (int) processList[runOrder[i]]->start*GANTT_SIZE/runtime;
        int end = (int) processList[runOrder[i]]->end*GANTT_SIZE/runtime;
        chart[start] = chart[end] = '|';
        for(int j=start+1; j<end; j++)
            chart[j] = '-';

        int k = 0, len;
        char *procStr = numToStr(runOrder[i]+1, &len);
        len = start+1;
        title[start] = 'P';
        while(procStr[k] != 0)
            title[len++] = procStr[k++];
        k = 0;
        char *startStr = numToStr(processList[runOrder[i]]->start, &len);
        len /= 2;
        while(startStr[k] != 0)
            label[start++ - len] = startStr[k++];

        k = 0;
        char *endStr = numToStr(processList[runOrder[i]]->end, &len);
        len /= 2;
        while(endStr[k] != 0)
            label[end++ - len] = endStr[k++];
        free(startStr); free(endStr); free(procStr);
    }
    printf("\n%s\n%s\n%s\n", title, chart, label);
}

void fifoCPU(struct Process **processList, int n){
    int time = 0, wt, tat;
    int avgWait = 0, avgTurnaround = 0;
    int *runOrder = malloc(sizeof(int)*n);
    printf("\nPID\tWait\tTurnAround\n");
    // Perform each process in order
    for(int i=0; i<n; i++){
        if(processList[i]->arrivalTime <= time){
            processList[i]->start = time;
            wt = time - processList[i]->arrivalTime;
            time += processList[i]->burstTime;
            tat = time - processList[i]->arrivalTime;
        }
        else{
            processList[i]->start = processList[i]->arrivalTime;
            time = processList[i]->arrivalTime + processList[i]->burstTime;
            // Wait is 0, Turnaround is same as BurstTime
            wt = 0; tat = processList[i]->burstTime;
        }
        processList[i]->end = time;
        runOrder[i] = i;
        avgWait += wt; avgTurnaround+= tat;
        printf("P%d\t%d\t%d\n", i+1, wt, tat);
    }
    avgWait /= n; avgTurnaround /= n;
    printf("\nAverage Waiting Time: %d ms\n", avgWait);
    printf("Average TurnAround Time: %d ms\n", avgTurnaround);
    printf("Runtime: %d ms\n", time);

    makeGantt(processList, runOrder, n, time);
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
    
    // Perform scheduling
    fifoCPU(processList, n);
}