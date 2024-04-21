import time

def fcfs(processes):
    processes.sort(key=lambda x: x['arrival_time'])
    start_time = 0
    for process in processes:
        process['start_time'] = start_time
        process['completion_time'] = start_time + process['burst_time']
        start_time = process['completion_time']
    return processes

def sjf(processes):
    processes.sort(key=lambda x: x['burst_time'])
    start_time = 0
    for process in processes:
        process['start_time'] = start_time
        process['completion_time'] = start_time + process['burst_time']
        start_time = process['completion_time']
    return processes

def round_robin(processes, quantum):
    time_slice = 0
    while True:
        for process in processes:
            if process['burst_time'] > 0:
                if process['burst_time'] > quantum:
                    process['burst_time'] -= quantum
                    time_slice += quantum
                else:
                    time_slice += process['burst_time']
                    process['burst_time'] = 0
                    process['completion_time'] = time_slice
                process['start_time'] = time_slice - process['burst_time']
                break
        if all(process['burst_time'] == 0 for process in processes):
            break
    return processes

def priority_scheduling(processes):
    processes.sort(key=lambda x: x['priority'])
    start_time = 0
    for process in processes:
        process['start_time'] = start_time
        process['completion_time'] = start_time + process['burst_time']
        start_time = process['completion_time']
    return processes

if __name__ == "__main__":
    num_processes = int(input("Enter the number of processes: "))
    processes = []
    for i in range(num_processes):
        arrival_time = int(input(f"Enter the arrival time for process {i+1}: "))
        burst_time = int(input(f"Enter the burst time for process {i+1}: "))
        priority = int(input(f"Enter the priority for process {i+1}: "))
        processes.append({'name': f'P{i+1}', 'arrival_time': arrival_time, 'burst_time': burst_time, 'priority': priority})

    print("FCFS:")
    fcfs_processes = fcfs(processes.copy())
    for process in fcfs_processes:
        print(f"Process {process['name']}: Start Time - {process['start_time']}, Completion Time - {process['completion_time']}")

    print("\nSJF:")
    sjf_processes = sjf(processes.copy())
    for process in sjf_processes:
        print(f"Process {process['name']}: Start Time - {process['start_time']}, Completion Time - {process['completion_time']}")

    print("\nRound Robin (Quantum = 2):")
    rr_processes = round_robin(processes.copy(), 2)
    for process in rr_processes:
        print(f"Process {process['name']}: Start Time - {process['start_time']}, Completion Time - {process['completion_time']}")

    print("\nPriority Scheduling:")
    priority_processes = priority_scheduling(processes.copy())
    for process in priority_processes:
        print(f"Process {process['name']}: Start Time - {process['start_time']}, Completion Time - {process['completion_time']}")