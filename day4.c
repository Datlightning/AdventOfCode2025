#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char **read_lines(const char *filename, int *out_count) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;

    char **lines = NULL;
    int count = 0;

    char buffer[1024];
    size_t n = 0;

    // getline() reads any-length line and mallocs internally as needed
    while (fgets(buffer, sizeof(buffer), f)) 
        {
        // remove newline at end of line
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';

        // grow list of lines
        lines = realloc(lines, (count + 1) * sizeof(char*));
        lines[count] = strdup(buffer);   // copy the line
        count++;
    }

    fclose(f);

    *out_count = count;
    return lines;
}

int main(){
    int height;
    char **lines = read_lines("input.txt", &height);
    int directions[8][2] = {
        {1,0},
        {1,1},
        {0,1},
        {-1,0},
        {-1,-1},
        {0,-1},
        {1,-1},
        {-1,1}
    };
    int p1 = 0;
    int p2 = 0;
    int y = 0, x = 0;
    int width = strlen(lines[0]);
    int dy, dx;
    int ny, nx;
    int count;
    char value;
    int dp2 = -1;
    printf("Height: %d\n", height);
    printf("Width: %d\n", width);
    char **copy = malloc(height * sizeof(char*));
    bool first = true;
    while (dp2 != 0){
        dp2 = 0;
        y = 0, x = 0;

        for (int i = 0; i < height; i++) {
            copy[i] = strdup(lines[i]);  // allocate memory and copy string
            // printf("%s\n", copy[i]);
        }
        // printf("\n");
        while (y < height && x < width){
        
            count = 0;
            for(int i = 0; i < 8; i++){
                dy = directions[i][0];
                dx = directions[i][1];
                ny = y + dy;
                nx = x + dx;
                if (ny >= 0 && ny < height && nx >= 0 && nx < width){
                    value = copy[ny][nx];
                    count += value == '@' ? 1 : 0;
                    
                }
            }
            value = copy[y][x];
            bool condition = value == '@' && count < 4;
            if (first){
                p1 += condition ? 1 : 0;    
            }
            dp2 += condition ? 1 : 0;    
            if (condition){
                lines[y][x] = '.';    
            }  
            x += 1;
            x %= width;
            if (x == 0)
                y += 1;
            
        }
        p2 += dp2;
        first = false;
        // printf("dp2: %d\n", dp2);
    }
    for(int i = 0; i < height; i++){
        printf("%s\n", lines[i]);
        free(lines[i]);
        free(copy[i]);
    }
    free(lines);
    free(copy);
    printf("Part 1 %d:\n", p1);
    printf("Part 2 %d:\n", p2);
}