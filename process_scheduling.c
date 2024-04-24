#include <stdio.h>

#define MAX_PROCESSES 10

// Structure to represent a process
typedef struct {
    char name;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to initialize processes
void initialize_processes(Process processes[], int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        processes[i].name = 'A' + i;
        printf("Enter arrival time for process %c: ", processes[i].name);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %c: ", processes[i].name);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %c: ", processes[i].name);
        scanf("%d", &processes[i].priority);
        processes[i].start_time = 0;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
}

// Function to calculate waiting time and turnaround time
void calculate_times(Process processes[], int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        // Calculate waiting time
        processes[i].waiting_time = processes[i].start_time - processes[i].arrival_time;
        // Calculate turnaround time
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    }
}

// Function to calculate average turnaround time
double calculate_average_turnaround_time(Process processes[], int num_processes) {
    double total_turnaround_time = 0;
    for (int i = 0; i < num_processes; i++) {
        total_turnaround_time += processes[i].turnaround_time;
    }
    return total_turnaround_time / num_processes;
}

// Function to apply FCFS scheduling
void fcfs_scheduling(Process processes[], int num_processes) {
    int start_time = 0;
    for (int i = 0; i < num_processes; i++) {
        processes[i].start_time = start_time;
        processes[i].completion_time = start_time + processes[i].burst_time;
        start_time = processes[i].completion_time;
    }
    calculate_times(processes, num_processes);
}

// Function to apply SJF scheduling
void sjf_scheduling(Process processes[], int num_processes) {
    int start_time = 0;
    // Sort processes based on burst time
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[j].burst_time < processes[i].burst_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    // Schedule processes
    for (int i = 0; i < num_processes; i++) {
        processes[i].start_time = start_time;
        processes[i].completion_time = start_time + processes[i].burst_time;
        start_time = processes[i].completion_time;
    }
    calculate_times(processes, num_processes);
}

// Function to apply Round Robin scheduling
void round_robin_scheduling(Process processes[], int num_processes, int quantum) {
    int time = 0;
    int remaining_burst_times[MAX_PROCESSES];
    for (int i = 0; i < num_processes; i++) {
        remaining_burst_times[i] = processes[i].burst_time;
    }
    int complete = 0;
    while (complete < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (remaining_burst_times[i] > 0) {
                if (remaining_burst_times[i] > quantum) {
                    remaining_burst_times[i] -= quantum;
                    time += quantum;
                } else {
                    time += remaining_burst_times[i];
                    remaining_burst_times[i] = 0;
                    processes[i].start_time = time - processes[i].burst_time;
                    processes[i].completion_time = time;
                    complete++;
                }
            }
        }
    }
    calculate_times(processes, num_processes);
}

// Function to apply Priority scheduling
void priority_scheduling(Process processes[], int num_processes) {
    int start_time = 0;
    // Sort processes based on priority
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = i + 1; j < num_processes; j++) {
            if (processes[j].priority < processes[i].priority) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    // Schedule processes
    for (int i = 0; i < num_processes; i++) {
        processes[i].start_time = start_time;
        processes[i].completion_time = start_time + processes[i].burst_time;
        start_time = processes[i].completion_time;
    }
    calculate_times(processes, num_processes);
}

// Function to display the results
void display_results(const char *strategy, Process processes[], int num_processes) {
    printf("\n%s Strategy:\n", strategy);
    for (int i = 0; i < num_processes; i++) {
        printf("Process %c: Start Time - %d, Completion Time - %d, Waiting Time - %d, Turnaround Time - %d\n",
               processes[i].name, processes[i].start_time, processes[i].completion_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }
    double avg_turnaround_time = calculate_average_turnaround_time(processes, num_processes);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

// Main function
int main() {
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    Process processes[MAX_PROCESSES];
    initialize_processes(processes, num_processes);

    // FCFS scheduling
    Process fcfs_processes[MAX_PROCESSES];
    for (int i = 0; i < num_processes; i++) {
        fcfs_processes[i] = processes[i];
    }
    fcfs_scheduling(fcfs_processes, num_processes);
    display_results("FCFS", fcfs_processes, num_processes);

    // SJF scheduling
    Process sjf_processes[MAX_PROCESSES];
    for (int i = 0; i < num_processes; i++) {
        sjf_processes[i] = processes[i];
    }
    sjf_scheduling(sjf_processes, num_processes);
    display_results("SJF", sjf_processes, num_processes);

    // Round Robin scheduling with quantum = 2
    Process rr_processes[MAX_PROCESSES];
    for (int i = 0; i < num_processes; i++) {
        rr_processes[i] = processes[i];
    }
    round_robin_scheduling(rr_processes, num_processes, 2);
    display_results("Round Robin (Quantum = 2)", rr_processes, num_processes);

    // Priority scheduling
    Process priority_processes[MAX_PROCESSES];
    for (int i = 0; i < num_processes; i++) {
        priority_processes[i] = processes[i];
    }
    priority_scheduling(priority_processes, num_processes);
    display_results("Priority", priority_processes, num_processes);

    return 0;
}
