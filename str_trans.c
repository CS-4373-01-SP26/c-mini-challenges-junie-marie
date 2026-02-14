#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
TASK - Write a program that accepts a string input from stdio and
sends it to a function that transforms it according a transposition function passed in to it as an argument.
The function will print out the string, transform it, and then print out the result.
The transposition function, you can assume, simply shuffles the existing characters in the string.
Build a transposition function that reverses the string and apply it.
Where appropriate and possible, use dynamic allocation and pointer arithmetic to get the job done.
*/

typedef void (*transposition_fn)(char *str);

void transposition(char *input, transposition_fn func) {
    printf("Original string: %s\n", input);
    func(input);
    printf("Transformed string: %s\n", input);
}

void reverse_string(char *str) {
    if (!str) return;

    size_t len = strlen(str);
    char *start = str;
    char *end = str + len - 1;

    while (start < end) {
        // Swap characters using pointers
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

int main() {
    char buffer[1024];

    printf("Enter a string: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("Error reading input.\n");
        return 1;
    }

    size_t len = strlen(buffer);

    // Allocate dynamic memory for the string
    char *dyn_str = (char *)malloc((len + 1) * sizeof(char));
    if (!dyn_str) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Copy input into dynamically allocated memory using pointer arithmetic
    char *src = buffer;
    char *dst = dyn_str;
    while (*src) {
        *dst = *src;
        src++;
        dst++;
    }
    *dst = '\0'; // null-terminate

    transposition(dyn_str, reverse_string);
    free(dyn_str);

    return 0;
}
