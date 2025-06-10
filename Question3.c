#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int is_palindrome(char *str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--)
        if (str[i] != str[j]) return 0;
    return 1;
}

int main() {
    int p1[2], p2[2];
    char str[100];

    pipe(p1);
    pipe(p2);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        while (1) {
            char buffer[100];
            read(p1[0], buffer, sizeof(buffer));
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline

            if (strcmp(buffer, "quit") == 0) break;

            if (is_palindrome(buffer))
                write(p2[1], "YES", 4);
            else
                write(p2[1], "NO", 3);
        }
        exit(0);
    } else {
        // Parent process
        while (1) {
            printf("Enter string: ");
            fgets(str, sizeof(str), stdin);
            write(p1[1], str, strlen(str) + 1);

            if (strncmp(str, "quit", 4) == 0) break;

            char response[10];
            read(p2[0], response, sizeof(response));
            printf("Palindrome: %s\n", response);
        }

        wait(NULL);
    }

    return 0;
}
