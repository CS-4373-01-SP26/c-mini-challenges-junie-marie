#include <stdio.h>

int main() {
    char name[50];
    printf("Enter your Name: ");

    scanf("%[^\n]", name);
    printf("Hello, %s\n", name);

    return 0;
}