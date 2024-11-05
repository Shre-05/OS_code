#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, totalMovement = 0;
    int requests[20]; // Array for storing disk requests
    int completed[20] = {0}; // Tracks completed requests

    // Input the number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    // Input the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Input the requests sequence
    printf("Enter the requests sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // SSTF Logic: Find closest request each time
    for (int count = 0; count < n; count++) {
        int minDistance = 10000, closestIndex = -1;

        // Find the closest uncompleted request
        for (int i = 0; i < n; i++) {
            if (!completed[i]) { // if request not yet serviced
                int distance = abs(requests[i] - head);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestIndex = i;
                }
            }
        }

        // Move head to the closest request and mark it as completed
        totalMovement += minDistance;
        head = requests[closestIndex];
        completed[closestIndex] = 1;

        printf("Servicing request at %d\n", requests[closestIndex]);
    }

    printf("Total head movement for SSTF: %d\n", totalMovement);
    return 0;
}
