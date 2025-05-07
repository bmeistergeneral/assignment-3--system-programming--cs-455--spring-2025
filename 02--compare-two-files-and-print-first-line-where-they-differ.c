#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    FILE *file1 = fopen(argv[1], "r");
    if (file1 == NULL) {
        perror("Error opening file 1");
        return 1;
    }

    FILE *file2 = fopen(argv[2], "r");
    if (file2 == NULL) {
        perror("Error opening file 2");
        fclose(file1);
        return 1;
    }

    char line1[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];
    int line_number = 1;

    while (fgets(line1, MAX_LINE_LENGTH, file1) != NULL && fgets(line2, MAX_LINE_LENGTH, file2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            printf("Files differ at line %d:\n", line_number);
            printf("< %s", line1);
            printf("> %s", line2);
            fclose(file1);
            fclose(file2);
            return 0;
        }
        line_number++;
    }

    // Check if one file is longer than the other
    if (fgets(line1, MAX_LINE_LENGTH, file1) != NULL || fgets(line2, MAX_LINE_LENGTH, file2) != NULL) {
        printf("Files differ starting from line %d (one file is longer):\n", line_number);
        if (fgets(line1, MAX_LINE_LENGTH, file1) != NULL) {
            printf("< %s", line1);
            // Try to read one more line from the other file for comparison
            if (fgets(line2, MAX_LINE_LENGTH, file2) != NULL) {
                printf("> %s", line2);
            } else {
                printf("> (end of file)\n");
            }
        } else {
            printf("< (end of file)\n");
            if (fgets(line2, MAX_LINE_LENGTH, file2) != NULL) {
                printf("> %s", line2);
            }
        }
    } else {
        printf("Files are identical.\n");
    }

    fclose(file1);
    fclose(file2);
    return 0;
}