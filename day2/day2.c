#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Check if first half equals second half

bool invalid(char string[64], int n) {
    char string2[64] = "";           // initialize
    char substring[n+1];

    strncpy(substring, string, n);
    substring[n] = '\0';             // terminate before using

    int count = strlen(string) / n;

    for (int i = 0; i < count; i++) {
        strcat(string2, substring);
    }

    // Debug for small n
 

    return strcmp(string, string2) == 0;
}

int main() {
    FILE *filePointer = fopen("input.txt", "r");
    if (filePointer == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    char line[1024];
    long long p1 = 0;
    long long p2 = 0;
    while (fgets(line, sizeof(line), filePointer)) {
        // Remove newline if present
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ",");
        while (token != NULL) {
            long long num1, num2;
            if (sscanf(token, "%lld-%lld", &num1, &num2) == 2) {
                // printf("Range: %lld to %lld\n", num1, num2);
                for (long long i = num1; i <= num2; i++) {
                    char string[64];
                    sprintf(string, "%lld", i);
                    int length = strlen(string);
                    length /= 2;
                    bool found = false;
                    for (int l = length; l>0; l--){
                        if ((strlen(string)) % l != 0){
                            continue;
                        }
                        bool valid = invalid(string,l);
                        if (strlen(string) % 2 == 0 && l == length && valid){
                            p1 += i;
                        }
                        if (!found && valid){
                            // printf("Valid number: %s\n", string);
                            found = true;
                            p2 += valid ? i : 0;
                        }
                    }
                }
            }
            token = strtok(NULL, ",");
        }
    }

    printf("Part 1: %lld\n", p1);
    printf("Part 2: %lld\n", p2);
    fclose(filePointer);
    return 0;
}
