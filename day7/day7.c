#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void add(int y, int x, int ***active, int *active_length)
{

    *active = realloc(*active, sizeof(int[2]) * (*active_length + 1));
    (*active)[*active_length] = malloc(sizeof(int) * 2);
    (*active)[*active_length][0] = y;
    (*active)[*active_length][1] = x;
    (*active_length)++;
}
int main()
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        perror("fopen");
        return 1;
    }
    char buffer[1024];
    char **lines = NULL;
    int height = 0;
    int width = 0;
    int **active = NULL;
    int active_length = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        lines = realloc(lines, sizeof(char *) * (height + 1));
        lines[height] = malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(lines[height], buffer);
        int length = strlen(buffer);
        if (length > width)
        {
            width = length;
        }
        lines[height][length] = '\0';
        for (int i = 0; i < length; i++)
        {
            if (lines[height][i] == 'S')
            {
                add(height, i, &active, &active_length);
            }
        }
        height++;
    }
    bool changed = true;
    int p1 = 0;
    printf("Width: %d, Height: %d\n", width, height);

    for (int i = 0; i < active_length; i++)
    {
        int y = active[i][0];
        int x = active[i][1];

        char current = lines[y][x];

        if (current == '^')
        {
            int x1 = x - 1;
            int x2 = x + 1;
            if (x1 >= 0)
            {
                add(y, x1, &active, &active_length);
            }
            if (x2 < width)
            {
                add(y, x2, &active, &active_length);
            }
            p1 += 1;
        }
        else
        {
            lines[y][x] = '|';

            y += 1;
            if (y != height)
            {
                add(y, x, &active, &active_length);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        printf("%s", lines[i]);
        free(lines[i]);
    }
    printf("\nPart 1: %d\n", p1);
}