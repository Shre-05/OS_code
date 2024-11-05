#include <stdio.h>

int P, R;  // Number of Processes and Resources
int available[10], max[10][10], allocation[10][10], need[10][10];  // Declare matrices

// Input matrices and calculate need matrix
void input() {
    printf("Enter available resources:\n");
    for (int i = 0; i < R; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    printf("\nEnter maximum resource needs for each process:\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d\n", i);
        for (int j = 0; j < R; j++) {
            printf("Max Resource %d: ", j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter allocated resources for each process:\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d\n", i);
        for (int j = 0; j < R; j++) {
            printf("Allocated Resource %d: ", j + 1);
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];  // Calculate need
        }
    }
}

// Check if system is in a safe state
int check_safe() {
    int work[10], finish[10] = {0}, safe_seq[10], count = 0;

    for (int i = 0; i < R; i++) work[i] = available[i];  // Copy available to work

    while (count < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int can_allocate = 1;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {  // Check if resources needed exceed available
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < R; j++) work[j] += allocation[i][j];  // Free resources
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++) printf("P%d ", safe_seq[i]);
    printf("\n");
    return 1;
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);

    input();
    check_safe();

    return 0;
}
