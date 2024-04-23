#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to read the list of disk requests from the user
void read_requests(int requests[], int num_requests) {
    printf("Enter disk requests: ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }
}

// Function to apply FCFS disk scheduling
void fcfs_scheduling(int requests[], int num_requests, int initial_position) {
    printf("\nFCFS Scheduling:\n");
    int current_position = initial_position;
    int total_seek_time = 0;
    
    for (int i = 0; i < num_requests; i++) {
        int seek_time = abs(requests[i] - current_position);
        total_seek_time += seek_time;
        current_position = requests[i];
        printf("Move from %d to %d (Seek Time: %d)\n", initial_position, requests[i], seek_time);
        initial_position = requests[i];
    }
    
    printf("Total Seek Time: %d\n", total_seek_time);
}

// Function to apply SSTF disk scheduling
void sstf_scheduling(int requests[], int num_requests, int initial_position) {
    printf("\nSSTF Scheduling:\n");
    int current_position = initial_position;
    int total_seek_time = 0;
    int processed[MAX_REQUESTS] = {0}; // Track processed requests
    
    for (int i = 0; i < num_requests; i++) {
        int closest_request_index = -1;
        int closest_request_distance = 1000000; // Initialize to a large number
        
        // Find the closest request to the current position
        for (int j = 0; j < num_requests; j++) {
            if (!processed[j]) {
                int distance = abs(requests[j] - current_position);
                if (distance < closest_request_distance) {
                    closest_request_distance = distance;
                    closest_request_index = j;
                }
            }
        }
        
        // Process the closest request
        if (closest_request_index != -1) {
            total_seek_time += closest_request_distance;
            printf("Move from %d to %d (Seek Time: %d)\n", current_position, requests[closest_request_index], closest_request_distance);
            current_position = requests[closest_request_index];
            processed[closest_request_index] = 1;
        }
    }
    
    printf("Total Seek Time: %d\n", total_seek_time);
}

// Function to apply Elevator (SCAN) disk scheduling
void scan_scheduling(int requests[], int num_requests, int initial_position) {
    printf("\nSCAN Scheduling:\n");
    
    // Sort requests in ascending order
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = i + 1; j < num_requests; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
    
    int current_position = initial_position;
    int total_seek_time = 0;
    int i = 0;
    
    // Find the starting point in the sorted list
    while (i < num_requests && requests[i] < current_position) {
        i++;
    }
    
    // Process requests in ascending order from the initial position
    for (int j = i; j < num_requests; j++) {
        int seek_time = abs(requests[j] - current_position);
        total_seek_time += seek_time;
        printf("Move from %d to %d (Seek Time: %d)\n", current_position, requests[j], seek_time);
        current_position = requests[j];
    }
    
    // Process requests in descending order
    for (int j = i - 1; j >= 0; j--) {
        int seek_time = abs(requests[j] - current_position);
        total_seek_time += seek_time;
        printf("Move from %d to %d (Seek Time: %d)\n", current_position, requests[j], seek_time);
        current_position = requests[j];
    }
    
    printf("Total Seek Time: %d\n", total_seek_time);
}

int main() {
    int initial_position;
    int num_requests;
    int requests[MAX_REQUESTS];
    
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &initial_position);
    
    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);
    
    // Read the list of disk requests
    read_requests(requests, num_requests);
    
    // Apply each scheduling algorithm and display results
    fcfs_scheduling(requests, num_requests, initial_position);
    sstf_scheduling(requests, num_requests, initial_position);
    scan_scheduling(requests, num_requests, initial_position);
    
    return 0;
}
