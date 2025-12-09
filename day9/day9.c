#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int cmp_int(int a[3], int b[3]){
    
}
int main(){
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    char line[256];
    int** points = NULL;
    int row_count = 0;
    while (fgets(line, sizeof(line), file))
    {
        points = realloc(points, (row_count + 1) * sizeof(int *));
        points[row_count] = malloc(2 * sizeof(int));
        sscanf(line, "%d,%d", &points[row_count][0], &points[row_count][1]);
        row_count++;
    }
    long long p1 = 0;
    for (int i = 0; i < row_count; i++){
        for(int j = i+ 1; j < row_count; j++){
            long long area = (1 + llabs(points[i][0] - points[j][0])) * (1 + llabs( points[i][1] - points[j][1]));
            // printf("Points (%d,%d) and (%d,%d) have area: %lld\n", points[i][0], points[i][1], points[j][0], points[j][1], area);
            if (area > p1){
                p1 = area;
            }
        }
    }
    for (int i = 0; i < row_count; i++){

        free(points[i]);
    }
    free(points);
    fclose(file);
    

    printf("Part 1: %lld\n", p1);

    return 0;
}