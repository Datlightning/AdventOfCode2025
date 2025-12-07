#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        perror("fopen");
        return 1;
    }

    char buffer[4096];
    char *token;
    char **data = NULL;
    int y = 0;
    int word = 5;
    while (fgets(buffer, sizeof(buffer), file))
    {
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
            buffer[--len] = '\0';

        data = realloc(data, sizeof(char *) * (y + 1));
        data[y] = malloc(sizeof(char) * (len + 1));
        strcpy(data[y], buffer);

        y++;
    }
    int length = strlen(data[y - 1]);
    int *words = NULL;
    int x = 0;
    int p = 0;
    for (int i = 0; i <= length; i += 1)
    {

        if (data[y - 1][i] == '+' || data[y - 1][i] == '*' || data[y - 1][i] == '\0')
        {
            words = realloc(words, sizeof(int) * (x + 1));
            words[x] = i;
            x++;
            // printf("Word %d\n", i);
        }
    }
    words = realloc(words, sizeof(int) * (x + 1));
    words[x] = length + 2;

    int psn = 0;
    long long p1 = 0;
    long long p2 = 0;

    while (psn < x)
    {
        int add = 0;
        long long mul = 0;

        int add2 = 0;
        long long mul2 = 0;

        int len = words[psn + 1] - words[psn] + 1;
        int p2nums[len];                   // VLA
        memset(p2nums, 0, sizeof(p2nums)); // initialize all elements to 0
        for (int i = 0; i < y; i++)
        {
            char *substring = malloc(sizeof(char) * (words[psn + 1] - words[psn] + 1));
            strncpy(substring, data[i] + words[psn], words[psn + 1] - words[psn]);
            substring[words[psn + 1] - words[psn]] = '\0'; // null terminate
            // printf("%s`\n", substring);
            for (int j = 0; j < strlen(substring); j++)
            {
                
                int value = substring[j] - '0';
                if (substring[j] < '0' || substring[j] > '9')
                    continue;
                p2nums[j] *= 10;
                p2nums[j] += value;
            }
            if (substring[0] == '*')
            {
                for (int k = 0; k < len - 1; k++)
                {   
                    if (mul2 == 0)
                        mul2 = 1;
                    if (p2nums[k] == 0)
                        continue;
                    mul2 *= p2nums[k];
                    p2nums[k] = 0;
                }
                p1 += mul;
                p2 += mul2;
            }
            else if (substring[0] == '+')
            {
                for (int k = 0; k < len - 1; k++)
                {
                    if (p2nums[k] == 0)
                        continue;
                    add2 += p2nums[k];
                    p2nums[k] = 0;
                }
                p1 += add;
                p2 += add2;
            }
            else
            {
                int val = atoi(substring);
                add += val;
                if (mul == 0)
                    mul = val;
                else
                    mul *= val;
            }
            // printf("%s`\n", substring);

            // printf("\n");
        }

        psn++;
    }
    printf("Part 1: %lld\n", p1);
    printf("Part 2: %lld\n", p2);

    fclose(file);
    return 0;
}
// 4046911022458491734 is to high