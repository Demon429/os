#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_REF_LEN 20

// Function to check if a page is in frames and return the index if found
int find_in_frames(int page, int frames[], int frame_size) {
    for (int i = 0; i < frame_size; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1;
}

// FIFO page replacement algorithm
void fifo(int ref[], int ref_len, int frame_size) {
    int frames[MAX_FRAMES] = {-1, -1, -1}; // Initialize frames
    int queue[MAX_FRAMES] = {0}; // Initialize queue
    int front = 0; // Queue front
    int rear = 0; // Queue rear
    int hit = 0, fault = 0;

    for (int i = 0; i < ref_len; i++) {
        int page = ref[i];

        // Check if page is in frames
        int index = find_in_frames(page, frames, frame_size);

        if (index != -1) {
            // Page is in frames, increment hit
            hit++;
        } else {
            // Page is not in frames, increment fault and replace oldest page
            fault++;
            frames[queue[front]] = page;
            front = (front + 1) % frame_size;
            rear = (rear + 1) % frame_size;
            queue[rear] = (rear + 1) % frame_size;
        }
    }

    printf("FIFO - Hits: %d, Faults: %d\n", hit, fault);
}

// LRU page replacement algorithm
void lru(int ref[], int ref_len, int frame_size) {
    int frames[MAX_FRAMES] = {-1, -1, -1}; // Initialize frames
    int queue[MAX_FRAMES] = {0}; // Initialize queue
    int hit = 0, fault = 0;

    for (int i = 0; i < ref_len; i++) {
        int page = ref[i];

        // Check if page is in frames
        int index = find_in_frames(page, frames, frame_size);

        if (index != -1) {
            // Page is in frames, increment hit
            hit++;
            // Update queue to move the page to the back (most recently used)
            for (int j = index; j > 0; j--) {
                queue[j] = queue[j - 1];
            }
            queue[0] = page;
        } else {
            // Page is not in frames, increment fault
            fault++;
            int lru_page = queue[frame_size - 1];
            // Replace least recently used page
            for (int j = 0; j < frame_size; j++) {
                if (frames[j] == lru_page) {
                    frames[j] = page;
                    break;
                }
            }
            // Update queue
            for (int j = frame_size - 1; j > 0; j--) {
                queue[j] = queue[j - 1];
            }
            queue[0] = page;
        }
    }

    printf("LRU - Hits: %d, Faults: %d\n", hit, fault);
}

// Optimal page replacement algorithm
void optimal(int ref[], int ref_len, int frame_size) {
    int frames[MAX_FRAMES] = {-1, -1, -1}; // Initialize frames
    int hit = 0, fault = 0;

    for (int i = 0; i < ref_len; i++) {
        int page = ref[i];

        // Check if page is in frames
        int index = find_in_frames(page, frames, frame_size);

        if (index != -1) {
            // Page is in frames, increment hit
            hit++;
        } else {
            // Page is not in frames, increment fault
            fault++;
            // Find the optimal page to replace
            int replace_index = -1;
            int furthest_index = -1;
            for (int j = 0; j < frame_size; j++) {
                int current_page = frames[j];
                int distance = -1;
                for (int k = i + 1; k < ref_len; k++) {
                    if (ref[k] == current_page) {
                        distance = k;
                        break;
                    }
                }
                if (distance == -1) {
                    replace_index = j;
                    break;
                } else if (distance > furthest_index) {
                    furthest_index = distance;
                    replace_index = j;
                }
            }
            // Replace the page in frames
            frames[replace_index] = page;
        }
    }

    printf("Optimal - Hits: %d, Faults: %d\n", hit, fault);
}

int main() {
    int page_number;
    printf("Number of frames: ");
    scanf("%d", &page_number);

    int ref[MAX_REF_LEN];
    int ref_len = 0;
    printf("Enter reference string (max 20 pages): ");
    while (ref_len < MAX_REF_LEN && scanf("%d", &ref[ref_len]) == 1) {
        ref_len++;
    }

    int choice = 0;
    while (choice != 4) {
        printf("\n1. FIFO\n2. LRU\n3. Optimal\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                fifo(ref, ref_len, page_number);
                break;
            case 2:
                lru(ref, ref_len, page_number);
                break;
            case 3:
                optimal(ref, ref_len, page_number);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }

    return 0;
}
