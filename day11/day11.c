#include <stdio.h>

int main(){
    FILE* file = fopen("input.txt", "r");
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)){
        printf("%s", buffer);
    }
    return 0;
}