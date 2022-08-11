// Author: Gokul Raj, 235, R4A, CSE
// Page Replacement: Least Frequently Used (LFU)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FRAMES 4

struct Frame{
    int content;
    int arrivalTime;
    int hits;
};

void displayFrames(struct Frame **pages){
    printf("| ");
    for(int i=0; i<FRAMES; i++){
        if(pages[i]->content == -1)
            printf("  | ");
        else
            printf("%d | ", pages[i]->content);
    }
    putchar('\n');
}

int lfu(struct Frame **pages, int *refStr, int n){
    int time = -1, faults = 0;
    // Traverse Reference String
    for(int i=0; i<n; i++){
        time++;
        displayFrames(pages);
        // Check if page already exist
        int found = 0;
        for(int j=0; j<FRAMES; j++){
            if(pages[j]->content == refStr[i]){
                found = 1;
                pages[j]->hits += 1;
                break;
            }
        }
        if(found) continue; else faults++;

        // Check if gap exist
        found = 0;
        for(int j=0; j<FRAMES; j++){
            if(pages[j]->content == -1){
                found = 1;
                pages[j]->content = refStr[i];
                pages[j]->arrivalTime = time;
                pages[j]->hits = 1;
                break;
            }
        }
        if(found) continue;

        // Else, do replacement as per lfu
        // Find min hit count, for same do fifo
        int min_frame = -1, min_hit = INT_MAX, min_time = INT_MAX;
        for(int j=0; j<FRAMES; j++){
            // If accesstime is same, follow fifo
            if(pages[j]->hits < min_hit || (pages[j]->hits == min_hit && pages[j]->arrivalTime < min_time)){
                min_frame = j;
                min_time = pages[j]->arrivalTime;
                min_hit = pages[j]->hits;
            }
        }
        // Swap current page with victim frame
        pages[min_frame]->content = refStr[i];
        pages[min_frame]->arrivalTime = time;
        pages[min_frame]->hits = 1;
    }
    return faults;
}

void main(){
    struct Frame **pages = malloc(sizeof(pages)*FRAMES);
    for(int i=0; i<FRAMES; i++){
        pages[i] = malloc(sizeof(struct Frame));
        pages[i]->content = -1;
        pages[i]->arrivalTime = -1;
    }

    int n;
    printf("Length of reference string: ");
    scanf("%d", &n);
    int *refStr = malloc(sizeof(int)*n);

    printf("ReferenceString: ");
    for(int i=0; i<n; i++)
        scanf("%d", &refStr[i]);

    // Do algorithms
    int faults = lfu(pages, refStr, n);
    printf("Page Faults: %d\n", faults);
}
