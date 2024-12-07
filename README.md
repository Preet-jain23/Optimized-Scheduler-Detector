# Optimized-Scheduler-Detector
An optimized detector in an operating system dynamically selects the best scheduling algorithm (FCFS, SJF,SRTF, or RR) based on give system. It evaluates based on waiting time and turnaround time to improve CPU utilization and ensure efficient process handling. This helps balance fairness, responsiveness, and performance in different scenarios.


1. input()
Purpose: Collects process details like arrival time and burst time interactively.
How it works: Recursively adds process details until the user decides to stop adding more.
2. fcfs()
Purpose: Implements the First Come First Serve (FCFS) scheduling algorithm.
How it works:
Sorts processes by arrival time.
Executes each process in the order they arrive, without preemption.
Creates a Gantt chart for the process execution.
3. sjf()
Purpose: Implements the Shortest Job First (SJF) scheduling algorithm.
How it works:
Selects the process with the shortest burst time among processes that have arrived.
Generates a Gantt chart for process execution.
Non-preemptive in nature.
4. srtf()
Purpose: Implements the Shortest Remaining Time First (SRTF) algorithm.
How it works:
A preemptive version of SJF.
Continuously selects the process with the shortest remaining burst time as new processes arrive.
Builds a Gantt chart showing the execution.
5. rr()
Purpose: Implements the Round Robin (RR) scheduling algorithm.
How it works:
Each process is given a fixed time quantum.
If a process isn’t finished within its quantum, it’s moved to the back of the queue.
Creates a Gantt chart reflecting process switching.
6. process_best_set() and process_of_shortest_burst_time()
Purpose: Helper functions to find the next process to execute in SJF and SRTF.
How they work: Compare burst times and arrival times to decide the best candidate for execution.
7. gant_chart_compression()
Purpose: Simplifies the Gantt chart for SRTF and RR by merging consecutive time slots for the same process.
How it works: Scans through the Gantt chart and combines segments for each process.
8. turnaround_time_and_waiting_time()
Purpose: Calculates Turnaround Time (TAT) and Waiting Time (WT).
How it works:
TAT = Finish Time - Arrival Time
WT = TAT - Burst Time
Averages the metrics across all processes.
How the Program Works
Input Process Details: Enter the arrival time and burst time for each process.
Select Algorithms: The program runs FCFS, SJF, SRTF, and RR.
Generate Gantt Charts: Visualize the execution order of processes.
Calculate Metrics: Computes the average turnaround and waiting times for each algorithm.
Best Algorithm Selection: Compares all algorithms and selects the one with the lowest turnaround and waiting times.
