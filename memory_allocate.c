#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Define the maximum number of memory blocks and processes
#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

// Structure to represent a memory block
typedef struct {
    int size;
    bool isAllocated;  // True if the block is allocated, false otherwise
} MemoryBlock;

// Structure to represent a process
typedef struct {
    int size;  // Size of the process
} Process;

// Arrays to hold memory blocks and processes
MemoryBlock blocks[MAX_BLOCKS];
Process processes[MAX_PROCESSES];

// Function to perform First-Fit allocation
void firstFit(int processIndex) 
{
    int processSize = processes[processIndex].size;

    for (int i = 0; i < MAX_BLOCKS; i++)
     {
        if (!blocks[i].isAllocated && blocks[i].size >= processSize)//TWO CONDITION BLOCK MUST NOT BE ALLOCATED AND IT SHOULD BE GREATER THAN PROCESS SIZE
         {
            blocks[i].isAllocated = true;
            printf("Process %d allocated to block %d (First-Fit)\n", processIndex + 1, i + 1);
            return;
        }
    }
    printf("Process %d not allocated (First-Fit)\n", processIndex + 1);
}

// Function to perform Best-Fit allocation
void bestFit(int processIndex) {
    int processSize = processes[processIndex].size;
    int bestBlockIndex = -1;
    int minWaste = INT_MAX;  // Start with the maximum possible waste

    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (!blocks[i].isAllocated && blocks[i].size >= processSize) {
            int waste = blocks[i].size - processSize;
            if (waste < minWaste) {
                minWaste = waste;
                bestBlockIndex = i;
            }
        }
    }

    if (bestBlockIndex != -1) {
        blocks[bestBlockIndex].isAllocated = true;
        printf("Process %d allocated to block %d (Best-Fit)\n", processIndex + 1, bestBlockIndex + 1);
    } else {
        printf("Process %d not allocated (Best-Fit)\n", processIndex + 1);
    }
}

// Function to perform Worst-Fit allocation
void worstFit(int processIndex) {
    int processSize = processes[processIndex].size;
    int worstBlockIndex = -1;
    int maxWaste = -1;  // Start with the minimum possible waste

    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (!blocks[i].isAllocated && blocks[i].size >= processSize) {
            int waste = blocks[i].size - processSize;
            if (waste > maxWaste) {
                maxWaste = waste;
                worstBlockIndex = i;
            }
        }
    }

    if (worstBlockIndex != -1) {
        blocks[worstBlockIndex].isAllocated = true;
        printf("Process %d allocated to block %d (Worst-Fit)\n", processIndex + 1, worstBlockIndex + 1);
    } else {
        printf("Process %d not allocated (Worst-Fit)\n", processIndex + 1);
    }
}

// Main program flow
int main() {
    int numBlocks, numProcesses;

    // Prompt the user to enter the number of memory blocks and processes
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    // Get memory block sizes from the user
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blocks[i].size);
        blocks[i].isAllocated = false;
    }

    printf("\nEnter the number of processes: ");
    scanf("%d", &numProcesses);

    // Get process sizes from the user
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processes[i].size);
    }

    // Perform First-Fit allocation
    printf("\nFirst-Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++) {
        firstFit(i);
    }

    // Reset the allocation status of blocks
    for (int i = 0; i < numBlocks; i++) {
        blocks[i].isAllocated = false;
    }

    // Perform Best-Fit allocation
    printf("\nBest-Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++) {
        bestFit(i);
    }

    // Reset the allocation status of blocks
    for (int i = 0; i < numBlocks; i++) {
        blocks[i].isAllocated = false;
    }

    // Perform Worst-Fit allocation
    printf("\nWorst-Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++) {
        worstFit(i);
    }

    return 0;
}
