#include <stdio.h>

int main(){
    FILE* file = fopen("input.txt", "r");
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), file)){
        printf("Line: %s", buffer);
    }
    return 0;
}