//1.SJF_Preemptive


#include <stdio.h>

void SJF_Preemptive(int n, int arrival[], int burst[]) {
    int remainingTime[n], waitingTime[n], turnaroundTime[n];
    int complete = 0, time = 0, minIndex = -1, shortestTime = 9999;
    int totalWait = 0, totalTurnaround = 0;

    // Initialize remaining times
    for (int i = 0; i < n; i++) remainingTime[i] = burst[i];

    while (complete < n) {
        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && remainingTime[i] > 0 && remainingTime[i] < shortestTime) {
                shortestTime = remainingTime[i];
                minIndex = i;
            }
        }

        // If no process is found, increment time and continue
        if (minIndex == -1) {
            time++;
            shortestTime = 9999;
            continue;
        }

        // Process the shortest job
        remainingTime[minIndex]--;
        time++;
        shortestTime = remainingTime[minIndex];

        // If a process is finished
        if (remainingTime[minIndex] == 0) {
            complete++;
            int finishTime = time;
            turnaroundTime[minIndex] = finishTime - arrival[minIndex];
            waitingTime[minIndex] = turnaroundTime[minIndex] - burst[minIndex];
            totalWait += waitingTime[minIndex];
            totalTurnaround += turnaroundTime[minIndex];

            printf("P[%d]: Waiting Time = %d, Turnaround Time = %d\n", minIndex + 1, waitingTime[minIndex], turnaroundTime[minIndex]);
            shortestTime = 9999; // Reset the shortest time
        }
    }

    printf("Average Waiting Time: %.2f\n", (float)totalWait / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n];
    printf("Enter arrival and burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &burst[i]);
    }

    printf("\n--- Shortest Job First (Preemptive) Scheduling ---\n");
    SJF_Preemptive(n, arrival, burst);

    return 0;
}


//2.Round Robin

#include <stdio.h>

void RoundRobin(int n, int arrival[], int burst[], int quantum) {
    int remainingTime[n], waitingTime[n], turnaroundTime[n];
    int totalWait = 0, totalTurnaround = 0, time = 0, completed = 0;

    for (int i = 0; i < n; i++) remainingTime[i] = burst[i];

    while (completed < n) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && arrival[i] <= time) {
                done = 0; // Process is not yet complete

                if (remainingTime[i] > quantum) {
                    time += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    time += remainingTime[i];
                    waitingTime[i] = time - arrival[i] - burst[i];
                    turnaroundTime[i] = time - arrival[i];
                    totalWait += waitingTime[i];
                    totalTurnaround += turnaroundTime[i];
                    remainingTime[i] = 0;
                    completed++;
                    printf("P[%d]: Waiting Time = %d, Turnaround Time = %d\n", i + 1, waitingTime[i], turnaroundTime[i]);
                }
            }
        }

        if (done) time++;
    }

    printf("Average Waiting Time: %.2f\n", (float)totalWait / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaround / n);
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n];
    printf("Enter arrival and burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &burst[i]);
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    printf("\n--- Round Robin Scheduling ---\n");
    RoundRobin(n, arrival, burst, quantum);

    return 0;
}
