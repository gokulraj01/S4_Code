#include <stdio.h>
#include <stdlib.h>

#define SEEK_TIME 2

int fcfsDisk(int *requests, int start, int end, int n){
    // Satisfy each request in turn
    int distance = 0, currentPos = start;
    printf("\nResponse Order: ");
    for(int i=0; i<n; i++){
        distance += abs(currentPos - requests[i]);
        currentPos = requests[i];
        printf("%d ", currentPos);
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
    int seekDist = fcfsDisk(requests, start, end, n);
    printf("\nAt %dms per unit seek\n\tAccess Time: %d ms\n\tSeek Distance: %d cylinders\n", SEEK_TIME, seekDist*SEEK_TIME, seekDist);
}