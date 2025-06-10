#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void show_menu() {
    printf("\n1. ls\n2. pwd\n3. uname\n4. exit\n");
    printf("Enter choice: ");
}

int main() {
    int choice;
    char *args1[] = {"/bin/ls", NULL};
    char *args2[] = {"/bin/pwd", NULL};
    char *args3[] = {"/bin/uname", NULL};

    while (1) {
        show_menu();
        scanf("%d", &choice);

        if (choice == 4)
            break;

        pid_t pid = fork();

        if (pid == 0) {
            switch (choice) {
                case 1: execv("/bin/ls", args1); break;
                case 2: execv("/bin/pwd", args2); break;
                case 3: execv("/bin/uname", args3); break;
                default: printf("Invalid choice\n"); exit(1);
            }
            perror("execv failed");
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("Fork failed");
        }
    }

    return 0;
}
