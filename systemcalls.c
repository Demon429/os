#include <stdio.h>
#include <unistd.h>  // For fork, getpid, getppid
#include <sys/types.h>  // For pid_t
#include <sys/wait.h>  // For wait, waitpid
#include <stdlib.h>  // For exit

int main() {
    // Create a child process using fork
    pid_t pid = fork();

    if (pid < 0) {
        // Error occurred while forking
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // In the child process
        printf("Child process:\n");
        printf("  PID = %d\n", getpid());
        printf("  Parent PID = %d\n", getppid());

        // Perform some task in the child process
        printf("Child process is exiting.\n");
        // Child process exits
        exit(0);
    } else {
        // In the parent process
        printf("Parent process:\n");
        printf("  PID = %d\n", getpid());
        printf("  Child PID = %d\n", pid);

        // Use waitpid to wait for the child process to terminate
        int status;
        pid_t wpid = waitpid(pid, &status, 0);
        if (wpid == -1) {
            perror("waitpid");
            return 1;
        }

        // Check the termination status of the child process
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process was terminated by signal %d\n", WTERMSIG(status));
        }

        // Parent process performs other tasks if needed
        printf("Parent process is exiting.\n");
        return 0;
    }
}
