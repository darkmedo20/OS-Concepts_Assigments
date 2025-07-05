#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    printf("Child process started\n");
  }
  return 0;
}
