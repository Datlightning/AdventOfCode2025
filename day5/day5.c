#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct RangeNode {
    long long start;
    long long end;
    struct RangeNode* next;
} RangeNode;

int main() {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    char buffer[128];
    RangeNode* head = NULL;
    RangeNode* tail = NULL;

    // --- Load ranges ---
    while (fgets(buffer, sizeof(buffer), file)) {
        if (buffer[0] == '\n') break;

        long long d1, d2;
        sscanf(buffer, "%lld-%lld", &d1, &d2);

        RangeNode* node = malloc(sizeof(RangeNode));
        node->start = d1;
        node->end = d2;
        node->next = NULL;

        if (!head) head = node;
        else tail->next = node;
        tail = node;
    }

    // --- Part 1: check numbers ---
    long long p1 = 0;
    long long current;
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%lld", &current);
        for (RangeNode* cur = head; cur; cur = cur->next) {
            if (cur->start <= current && current <= cur->end) {
                p1++;
                break;
            }
        }
    }

    bool change = true;
 while (change) {
    change = false;
    RangeNode* cur = head;

    while (cur) {
        long long d1 = cur->start;
        long long d2 = cur->end;

        RangeNode* runner = cur;

        while (runner->next) {
            RangeNode* next_node = runner->next;
            long long e1 = next_node->start;
            long long e2 = next_node->end;

            // Correct overlap check using your variables
            if (!(e1 > d2 || e2 < d1)) {
                // merge
                if (e1 < d1) d1 = e1;
                if (e2 > d2) d2 = e2;

                cur->start = d1;
                cur->end = d2;

                // Remove node safely
                runner->next = next_node->next;
                free(next_node);

                change = true;
            } else {
                runner = runner->next; // move only if no removal
            }
        }

        cur = cur->next;
    }
}

    long long p2 = 0;
    for (RangeNode* cur = head; cur; cur = cur->next) {
        p2 += cur->end - cur->start + 1;
    }

    printf("Part 1: %lld\n", p1);
    printf("Part 2: %lld\n", p2);

    while (head) {
        RangeNode* tmp = head;
        head = head->next;
        free(tmp);
    }

    fclose(file);
    return 0;
}
