// Author: Gokul Raj, 235, R4A, CSE
// Disk Scheduling: Circular SCAN (C-SCAN)
#include <stdio.h>
#include <stdlib.h>

#define SEEK_TIME 2

int cscanDisk(int *requests, int start, int end, int n){
    int distance = 0, lastPos = start, done = 0;
    printf("\nResponse Order: ");
    // Do a circular sweep from start position until all requests satisfies
    for(int curr = start; done < n ; curr = (curr+1)%(end+1)){
        // If any waiting request is at current pos, do it!!
        for(int i=0; i<n; i++){
            if(requests[i] == curr){
                requests[i] = -1; done++;
                distance += abs(lastPos - curr);
                lastPos = curr;
                printf("%d ", curr);
            }
        }
    }
    putchar('\n');
    return distance;
}

void main(){
    int start, end, n;
    printf("Head Initial Position: ");
    scanf("%d", &start);
    printf("Cylinders: ");
    scanf("%d", &end);
    printf("Number of requests: ");
    scanf("%d", &n);

    int *requests = malloc(sizeof(int)*n);
    printf("Enter requested cylinders in order: ");
    for(int i=0; i<n; i++)
        scanf("%d", &requests[i]);
    
    // Perform Disk Scheduling Algorithm
    int seekDist = cscanDisk(requests, start, end, n);
    printf("\nAt %dms per unit seek\n\tAccess Time: %d ms\n\tSeek Distance: %d cylinders\n", SEEK_TIME, seekDist*SEEK_TIME, seekDist);
}