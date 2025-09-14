#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    // First child: ls -l
    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(fd[0]);             // Close read end
        dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(fd[1]);             // Close original write end

        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls failed");
        exit(1);
    }

    // Second child: grep txt
    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(fd[1]);             // Close write end
        dup2(fd[0], STDIN_FILENO);  // Redirect stdin from pipe
        close(fd[0]);             // Close original read end

        execlp("grep", "grep", "txt", NULL);
        perror("execlp grep failed");
        exit(1);
    }

    // Parent closes both ends
    close(fd[0]);
    close(fd[1]);

    // Wait for both children
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
