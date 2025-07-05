/* 3- Write a C program that creates a child process using fork(). The child 
process should sleep for 5 seconds and then print the message: 
"Hi! I'm the Child Process, I slept for 5 seconds." 
Meanwhile, the parent process should wait for the1 child to finish 
before printing its own message. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>  // For signal()
#include <sys/types.h> // For pid_t (though often included by other headers)
#include <sys/wait.h>

int main()
{
  pid_t pid;
  
  pid = fork();
  if(pid < 0){
    printf("Process creation failed.\n");
    exit(-1);
  }
  else if(pid > 0){
    wait(NULL);
    printf("Parent started");
    
  }
  else{
    sleep(5);
    printf("I slept for 5 seconds.\n");
  }
  return 0;
}
