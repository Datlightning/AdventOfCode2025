#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

long long getmax(char line[1024], int length){
    int maxs[length];
    for (int i = 0; i < length; i++){
        maxs[i] = 0;
    }
    int n = strlen(line);
    int start = 0;
    for (int i = 0; i < n; i++) {
        int digit = line[i] - '0';   // convert char → int
        bool larger = false;
        if (n - i - 1 < length){
            start = length - (n-i - 1);
        }
        for (int j = start; j < length; j++){
            if (!larger){
                if (digit > maxs[j]){
                    larger = true;
                    maxs[j] = digit;
                }
            }else{
                maxs[j] = 0;
            }
        }
    }

    long long powers[length];
    long long power = 1;
    for (int i = length - 1; i>=0; i--){
        powers[i] = power;
        power *= 10;
    }
    long long output = 0;
    for (int i = 0; i < length; i++){
        output += maxs[i] * powers[i];
    }
    // printf("Output: %lld\n", output);

    return output;
}

int main(){
    FILE *filePointer = fopen("input.txt", "r");
    if (filePointer == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }
    char line[1024];
    long long p1 = 0, p2 = 0;

    while (fgets(line, sizeof(line), filePointer)) {
        // printf("Processing line: %s", line);
        p1 += getmax(line, 2);
        p2 += getmax(line, 12);
        
    }
    printf("Part 1: %lld\n", p1);
    printf("Part 2: %lld\n", p2);
    return 0;
}