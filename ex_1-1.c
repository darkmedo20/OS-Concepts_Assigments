#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
  pid_t pid;
  
  pid = fork();
  if(pid < 0){
    printf("Process creation failed.\n");
  }
  else if(pid == 0){
    printf("I’m the Child Process. my ID is %d \n", getpid());
  }
  else{
    printf("I’m the Parent Process, my ID is %d \n", getpid());
  }
  return 0;
}
