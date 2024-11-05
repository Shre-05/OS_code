#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, cylinders = 0; // Number of requests, head position, and cylinder movements
    int item[20]; // Array to hold disk request positions

    // Input the number of locations (requests)
    printf("Enter number of locations: ");
    scanf("%d", &n);

    // Input the initial position of the disk head
    printf("Enter position of head: ");
    scanf("%d", &head);

    // Input the disk request queue
    printf("Enter elements of disk queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &item[i]);
    }

    // Sort the disk requests based on their distance from the head position
    // Using a simple selection sort for clarity
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (item[j] < item[i]) { // Sorting in ascending order
                // Swap items
                int temp = item[i];
                item[i] = item[j];
                item[j] = temp;
            }
        }
    }

    // Find the position to start servicing requests
    int startIndex;
    for (startIndex = 0; startIndex < n; startIndex++) {
        if (item[startIndex] >= head) {
            break; // Found the first request greater than or equal to the head
        }
    }

    // Print the order of disk allocation and calculate total cylinder movements
    printf("\nOrder of disk allocation is as follows:\n");

    // Serve all requests from the start index to the end
    for (int i = startIndex; i < n; i++) {
        printf(" -> %d", item[i]);
        cylinders += abs(head - item[i]); // Calculate movement
        head = item[i]; // Move the head
    }

    // Serve remaining requests before the head position
    for (int i = startIndex - 1; i >= 0; i--) {
        printf(" -> %d", item[i]);
        cylinders += abs(head - item[i]); // Calculate movement
        head = item[i]; // Move the head
    }

    // Output total cylinder movements
    printf("\n\nTotal cylinder movement: %d\n\n", cylinders);
    
    return 0;
}
