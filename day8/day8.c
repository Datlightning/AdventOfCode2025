#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int distance(int p1[5], int p2[5])
{
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]) + abs(p1[2] - p2[2]);
}
int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    int **psn = NULL;
    size_t row_count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int row[5] = {0, 0, 0, 1, row_count};
        sscanf(line, "%d,%d,%d", &row[0], &row[1], &row[2]);
        psn = realloc(psn, (row_count + 1) * sizeof(int *));
        psn[row_count] = malloc(5 * sizeof(int));
        memcpy(psn[row_count], row, 5 * sizeof(int));
        row_count++;
    }
    long long p1 = 0;
    int connections = 10;

    fclose(file);
    for (int c = 0; c < connections; c++)
    {
        long long min_distance = 1000000;
        int min_i = -1;
        int min_j = -1;
        for (size_t i = 0; i < row_count; i++)
        {
            for (size_t j = i; j < row_count; j++)
            {
                if (psn[i][4] != psn[j][4])
                {
                    int dist = distance(psn[i], psn[j]);
                    if (dist < min_distance)
                    {
                        min_distance = dist;
                        min_i = i;
                        min_j = j;
                    }
                }
            }
            printf("Row %zu: %d %d %d. Circuit id: %d, length: %d\n", i, psn[i][0], psn[i][1], psn[i][2], psn[i][4], psn[i][3]);
        }
        if (min_i != -1){
            psn[min_i][4] = psn[min_j][4];
        }
    }

    printf("Part 1: %lld\n", p1);
    free(psn);

    return 0;
}