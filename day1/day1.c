#include <stdio.h>

int main() {
    FILE *filePointer;
    filePointer = fopen("input.txt", "r");
    if (filePointer == NULL) {
        printf("Error: Could not open file.\n");
        return 1; // Indicate an error
    }
    int start = 50;
    int p1 = 0;
    int p2 = 0;
    char line[256];
    while (fgets(line, sizeof(line), filePointer)) {
        char letter = line[0];
        int number;
        sscanf(line + 1, "%d", &number);
        if(letter == 'R'){
            for (int i = 0; i < number; i++){
                start++;
                start %= 100;
                p2 += start == 0 ? 1 : 0;
            }
        }
        else if(letter == 'L'){
           for (int i = 0; i < number; i++){
                start--;
                start %= 100;
                p2 += start == 0 ? 1 : 0;
            }
        }
        p1 += start == 0 ? 1 : 0;
    }
    printf("Part 1: %d\n", p1);
    printf("Part 2: %d\n", p2);
    fclose(filePointer);
    return 0;
}
