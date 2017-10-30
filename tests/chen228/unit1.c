#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>

#define CHILD 0
#define EXIT_FAILURE 1

void test_1() {
  // Fork a process, which runs return_7
  // In parent process, child process execl student code and parent check return value
  int fd[2];
  char buffer[512];
  int flag = 0;
  memset(buffer, 0, 512);
  pipe(fd);
  pid_t pid = fork();
  if(pid == CHILD) {
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    execl("/bin/sh", "bin/sh", "-c", "./task", "NULL");
    exit(EXIT_FAILURE);
  }
  else {
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    int status;

    fgets(buffer, 512, stdin);
    //printf("buffer: %s", buffer);
    if(strlen(buffer) != 0)
      flag = 1;
    if (waitpid(pid, &status, 0) == -1){
      perror("waitpid failed");
      exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)){
      int ret_val = WEXITSTATUS(status);
      //printf("ret_val = %d;", ret_val);
      if (ret_val == 0 && flag == 1){
        printf("test_1 passed\n");
      }else{
        printf("test_1 failed\n");
      }
    }
  }
}

int main(){
  test_1();
  return 0;
}
