#include <stdio.h>

#define MAX_PARTITIONS 10
#define MAX_JOBS 10

// Structure to represent a memory partition
typedef struct {
    char name;
    int capacity;
    int left;
} Partition;

// Structure to represent a job
typedef struct {
    char name;
    int cost;
    char allocated_to;
} Job;

// Function to initialize partitions
void init_partitions(Partition partitions[], int num_partitions) {
    for (int i = 0; i < num_partitions; i++) {
        partitions[i].name = 'A' + i;
        printf("Enter capacity for partition %c: ", partitions[i].name);
        scanf("%d", &partitions[i].capacity);
        partitions[i].left = partitions[i].capacity;
    }
}

// Function to initialize jobs
void init_jobs(Job jobs[], int num_jobs) {
    for (int i = 0; i < num_jobs; i++) {
        jobs[i].name = 'A' + i;
        printf("Enter cost for job %c: ", jobs[i].name);
        scanf("%d", &jobs[i].cost);
        jobs[i].allocated_to = '\0';
    }
}

// Function for First Fit strategy
void first_fit(Job jobs[], int num_jobs, Partition partitions[], int num_partitions) {
    for (int i = 0; i < num_jobs; i++) {
        for (int j = 0; j < num_partitions; j++) {
            if (partitions[j].left >= jobs[i].cost && jobs[i].allocated_to == '\0') {
                partitions[j].left -= jobs[i].cost;
                jobs[i].allocated_to = partitions[j].name;
                break;
            }
        }
    }
}

// Function for Worst Fit strategy
void worst_fit(Job jobs[], int num_jobs, Partition partitions[], int num_partitions) {
    for (int i = 0; i < num_jobs; i++) {
        int worst_index = -1;
        int max_left = -1;
        for (int j = 0; j < num_partitions; j++) {
            if (partitions[j].left >= jobs[i].cost && partitions[j].left > max_left) {
                worst_index = j;
                max_left = partitions[j].left;
            }
        }
        if (worst_index != -1) {
            partitions[worst_index].left -= jobs[i].cost;
            jobs[i].allocated_to = partitions[worst_index].name;
        }
    }
}

// Function for Best Fit strategy
void best_fit(Job jobs[], int num_jobs, Partition partitions[], int num_partitions) {
    for (int i = 0; i < num_jobs; i++) {
        int best_index = -1;
        int min_left = __INT_MAX__;
        for (int j = 0; j < num_partitions; j++) {
            if (partitions[j].left >= jobs[i].cost && partitions[j].left < min_left) {
                best_index = j;
                min_left = partitions[j].left;
            }
        }
        if (best_index != -1) {
            partitions[best_index].left -= jobs[i].cost;
            jobs[i].allocated_to = partitions[best_index].name;
        }
    }
}

// Function to display the results
void display_results(const char *strategy, Partition partitions[], int num_partitions, Job jobs[], int num_jobs) {
    printf("\n%s Strategy Results:\n", strategy);
    printf("Partitions:\n");
    for (int i = 0; i < num_partitions; i++) {
        printf("Partition %c - Leftover: %d\n", partitions[i].name, partitions[i].left);
    }
    printf("\nJobs:\n");
    for (int i = 0; i < num_jobs; i++) {
        printf("Job %c - Allocated to partition: %c\n", jobs[i].name, jobs[i].allocated_to);
    }
}

int main() {
    int num_partitions, num_jobs;

    // Get user input for the number of partitions and jobs
    printf("Enter number of partitions: ");
    scanf("%d", &num_partitions);
    Partition partitions[MAX_PARTITIONS];
    init_partitions(partitions, num_partitions);

    printf("\nEnter number of jobs: ");
    scanf("%d", &num_jobs);
    Job jobs[MAX_JOBS];
    init_jobs(jobs, num_jobs);

    // Apply and display the results for each strategy
    Partition temp_partitions[MAX_PARTITIONS];
    Job temp_jobs[MAX_JOBS];

    // First Fit strategy
    for (int i = 0; i < num_partitions; i++) {
        temp_partitions[i] = partitions[i];
    }
    for (int i = 0; i < num_jobs; i++) {
        temp_jobs[i] = jobs[i];
    }
    first_fit(temp_jobs, num_jobs, temp_partitions, num_partitions);
    display_results("First Fit", temp_partitions, num_partitions, temp_jobs, num_jobs);

    // Worst Fit strategy
    for (int i = 0; i < num_partitions; i++) {
        temp_partitions[i] = partitions[i];
    }
    for (int i = 0; i < num_jobs; i++) {
        temp_jobs[i] = jobs[i];
    }
    worst_fit(temp_jobs, num_jobs, temp_partitions, num_partitions);
    display_results("Worst Fit", temp_partitions, num_partitions, temp_jobs, num_jobs);

    // Best Fit strategy
    for (int i = 0; i < num_partitions; i++) {
        temp_partitions[i] = partitions[i];
    }
    for (int i = 0; i < num_jobs; i++) {
        temp_jobs[i] = jobs[i];
    }
    best_fit(temp_jobs, num_jobs, temp_partitions, num_partitions);
    display_results("Best Fit", temp_partitions, num_partitions, temp_jobs, num_jobs);

    return 0;
}
