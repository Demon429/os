#include <stdio.h>
#include <stdlib.h>

int main() {
    // File pointer
    FILE *file;

    // Open the file in write mode
    file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    // Write data to the file using fprintf
    fprintf(file, "This is an example of writing to a file.\n");
    fprintf(file, "Another line of text.\n");

    // Close the file
    fclose(file);
    printf("Data has been written to example.txt.\n");

    // Re-open the file in read mode
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    // Read data from the file and display it
    printf("Reading from example.txt:\n");
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);

    return 0;
}
