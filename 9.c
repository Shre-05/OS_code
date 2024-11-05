#include <stdio.h>

#define MAX_PAGES 10   // Maximum number of pages
#define FRAME_SIZE 3   // Minimum frame size as per problem statement

// Function prototypes
void FIFO(int pages[], int page_count);
void LRU(int pages[], int page_count);
void Optimal(int pages[], int page_count);
int isPageInFrames(int frames[], int page);

int main() {
    int pages[MAX_PAGES];
    int page_count;

    // Input page reference string
    printf("Enter number of pages (max %d): ", MAX_PAGES);
    scanf("%d", &page_count);
    
    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < page_count; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }

    // Menu for page replacement algorithms
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: FIFO(pages, page_count); break;
            case 2: LRU(pages, page_count); break;
            case 3: Optimal(pages, page_count); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to check if a page is in the frames
int isPageInFrames(int frames[], int page) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        if (frames[i] == page) return 1; // Page found
    }
    return 0; // Page not found
}

// FIFO Page Replacement Algorithm
void FIFO(int pages[], int page_count) {
    int frames[FRAME_SIZE] = {-1, -1, -1};
    int next_frame = 0;
    int faults = 0;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < page_count; i++) {
        printf("Page %d: %d ", i + 1, pages[i]);
        
        if (!isPageInFrames(frames, pages[i])) {
            frames[next_frame] = pages[i]; // Replace the page
            next_frame = (next_frame + 1) % FRAME_SIZE; // Move to the next frame
            faults++;
            printf("-> Page Fault! Frames: ");
        } else {
            printf("-> No Page Fault. Frames: ");
        }
        
        for (int j = 0; j < FRAME_SIZE; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", faults);
}

// LRU Page Replacement Algorithm
void LRU(int pages[], int page_count) {
    int frames[FRAME_SIZE] = {-1, -1, -1};
    int faults = 0;

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < page_count; i++) {
        printf("Page %d: %d ", i + 1, pages[i]);
        
        if (!isPageInFrames(frames, pages[i])) {
            int least_recent = 0; // Find LRU page
            for (int j = 1; j < FRAME_SIZE; j++) {
                if (frames[j] == -1) {
                    least_recent = j; // Find an empty frame
                    break;
                }
            }

            if (frames[least_recent] != -1) { // If no empty frame
                least_recent = (i - 1) % FRAME_SIZE; // Replace the last used frame
            }
            
            frames[least_recent] = pages[i]; // Replace the page
            faults++;
            printf("-> Page Fault! Frames: ");
        } else {
            printf("-> No Page Fault. Frames: ");
        }
        
        for (int j = 0; j < FRAME_SIZE; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", faults);
}

// Optimal Page Replacement Algorithm
void Optimal(int pages[], int page_count) {
    int frames[FRAME_SIZE] = {-1, -1, -1};
    int faults = 0;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < page_count; i++) {
        printf("Page %d: %d ", i + 1, pages[i]);
        
        if (!isPageInFrames(frames, pages[i])) {
            int replace_index = -1;
            for (int j = 0; j < FRAME_SIZE; j++) {
                if (frames[j] == -1) {
                    replace_index = j; // Use empty frame if available
                    break;
                }
            }

            if (replace_index == -1) { // If all frames are full
                int farthest = -1; // Track farthest used page
                for (int j = 0; j < FRAME_SIZE; j++) {
                    int k;
                    for (k = i + 1; k < page_count; k++) {
                        if (frames[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                replace_index = j;
                            }
                            break;
                        }
                    }
                    if (k == page_count) { // If page not found
                        replace_index = j;
                        break;
                    }
                }
            }

            frames[replace_index] = pages[i]; // Replace the page
            faults++;
            printf("-> Page Fault! Frames: ");
        } else {
            printf("-> No Page Fault. Frames: ");
        }
        
        for (int j = 0; j < FRAME_SIZE; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total Page Faults: %d\n", faults);
}
