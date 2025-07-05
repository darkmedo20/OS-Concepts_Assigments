/*
5- Write a program where the child process exits immediately, and the 
parent sleeps for 10 seconds before calling wait(). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>  // For signal()
#include <sys/types.h> // For pid_t (though often included by other headers)
#include <sys/wait.h>

int main()
{
    pid_t pid;
    if (pid < 0) {
        // Error handling for fork() failure
        printf("Error in process creattion");
        exit(-1);
    } else if(pid == 0){
        exit(0);
    } else {
        sleep(10);
        wait(NULL);
        printf("I've waited for 10 secs!");
    }
    
      
      
  return 0;
}
