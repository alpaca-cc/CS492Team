#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>

#define CHILD 0
#define EXIT_FAILURE 1

int spot_mistake(){
  for(int len = 0; len <7 ; len++) {
    write(STDOUT_FILENO,"I think", 7-len);
    write(STDOUT_FILENO,"\n", 1);
  }
  return 0;
}

int return_7(){
  return 7;
}

int return_1023(){
  return 1023;
}

void test_spot_mistake() {
    // Fork a process, which runs spot_mistake
    // In parent process, read from child process and checks..
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid == CHILD) {
      dup2(fd[1], STDOUT_FILENO);
      close(fd[0]);
      spot_mistake();
      exit(0);
    }else {
      dup2(fd[0], STDIN_FILENO);
      close(fd[1]);

      char* line = NULL;
      size_t size = 0;
      ssize_t getsize = 0;
      int count = 8, fail = 0;
      while ((getsize = getline(&line, &size, stdin)) > 0){
        if (count < 2){
          fail = 1;
          break;
        }else{
          if ((getsize != count) || (strncmp(line, "I think", count-1) != 0 && line[getsize-1] != '\n')){
            printf("getsize = %zd, %s", getsize, line);
            fail = 1;
            break;
          }
        }
        count--;
      }
      if (count == 1 && fail == 0){
        printf("test_spot_mistake passed\n");
      }else{
        printf("test_spot_mistake failed\n");
      }
      if (waitpid(pid, NULL, 0) == -1){
        perror("waitpid failed");
        exit(EXIT_FAILURE);
      }
    }
}

void test_return_7() {
    // Fork a process, which runs return_7
    // In parent process, child process execl student code and parent check return value
    pid_t pid = fork();
    if(pid == CHILD) {
      execl("/bin/sh", "bin/sh", "-c", "./return_7", "NULL");
      exit(EXIT_FAILURE);
    }else {
      int status;
      if (waitpid(pid, &status, 0) == -1){
        perror("waitpid failed");
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(status)){
        int ret_val = WEXITSTATUS(status);
        if (ret_val == 7){
          printf("test_return_7 passed\n");
        }else{
          printf("test_return_7 failed\n");
        }
      }
    }
}

void test_return_1023() {
    // Fork a process, which runs return_1023(should return 255)
    // In parent process, child process execl student code and parent check return value
    pid_t pid = fork();
    if(pid == CHILD) {
      execl("/bin/sh", "bin/sh", "-c", "./return_1023", "NULL");
      exit(EXIT_FAILURE);
    }else {
      int status;
      if (waitpid(pid, &status, 0) == -1){
        perror("waitpid failed");
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(status)){
        int ret_val = WEXITSTATUS(status);
        //printf("ret_val = %d;", ret_val);
        if (ret_val == 255){
          printf("test_return_1023 passed\n");
        }else{
          printf("test_return_1023 failed\n");
        }
      }
    }
}


int main(){
  test_spot_mistake();
  test_return_7();
  test_return_1023();
  return 0;
}
