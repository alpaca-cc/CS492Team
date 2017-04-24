#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>


#define CHILD 0

void print_array() {
    int data[5] = {10, 30, 60, 50, 40};
    int * copy = data;
    for(int i = 0; i < 5; i++) {
        if(i == 4)
            printf("%d\n", *copy);
        else
            printf("%d ", *copy);
        copy++;
    }
}

void print_swapped_array() {
    int data[5] = {10, 30, 60, 50, 40};
    
    int t = data[0];
    data[0] = data[4];
    data[4] = t;
    
    int * copy = data;
    for(int i = 0; i < 5; i++) {
        if(i == 4)
            printf("%d\n", *copy);
        else
            printf("%d ", *copy);
        copy++;
    }
}

void test_print_array() {
    // Fork a process, which runs print_array
    // In parent process, read from child process and checks..
    
    int fd[2];
    char buffer[512];
    memset(buffer, 0, 512);
    pipe(fd);
    pid_t pid = fork();
    if(pid == CHILD) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        print_array();
        exit(0);
    }
    else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        
        fgets(buffer, 512, stdin);
        //printf("buffer: %s", buffer);
        if(strcmp(buffer, "10 30 60 50 40\n") == 0)
            printf("test_print_array passed\n");
        else
            printf("test_print_array failed\n");
        waitpid(pid, NULL, 0);
    }
}

void test_print_swapped_array() {
    int fd[2];
    char buffer[512];
    memset(buffer, 0, 512);
    pipe(fd);
    pid_t pid = fork();
    if(pid == CHILD) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        print_swapped_array();
        exit(0);
    }
    else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        
        fgets(buffer, 512, stdin);
        //printf("buffer: %s", buffer);
        if(strcmp(buffer, "40 30 60 50 10\n") == 0)
            printf("test_print_array passed\n");
        else
            printf("test_print_array failed\n");
        waitpid(pid, NULL, 0);
    }
}

int main() {
    //print_swapped_array();
    //test_print_array();
    test_print_array();
    test_print_swapped_array();
    return 0;
}
