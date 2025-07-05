/* 4- Write a program that creates  10 child processes using fork(). Each 
child should print its process ID. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>  // For signal()
#include <sys/types.h> // For pid_t (though often included by other headers)
#include <sys/wait.h>

int main()
{
  pid_t pid;
  for (int i = 0; i < 10; i++) {
        pid = fork(); // Create a new process

        if (pid < 0) {
            // Error handling for fork() failure
            perror("fork failed");
            return 1; // Exit with an error code
        } else if (pid == 0) {
            // This code block is executed by the child process
            printf("Child process %d (PID: %d) created by parent.\n", i + 1, getpid());
            _exit(0); // Child exits immediately after printing its PID
                      // _exit() is used instead of exit() to avoid flushing parent's buffers
        }
        
    
        // If pid > 0, this code block is executed by the parent process
        // The parent continues the loop to create more children
    }
    printf("I am the parent my PID is %d\n", getpid());
      
      
  return 0;
}
