#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return 0;
    return 1;
}

void print_primes(int start, int end) {
    for (int i = start; i <= end; ++i)
        if (is_prime(i))
            printf("%d\n", i);
}

int main() {
    int range = 100000;
    for (int i = 0; i < 10; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            int start = i * range + 1;
            int end = (i + 1) * range;
            print_primes(start, end);
            exit(0);
        }
    }

    for (int i = 0; i < 10; i++)
        wait(NULL);

    return 0;
}
