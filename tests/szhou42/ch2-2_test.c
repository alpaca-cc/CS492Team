/*
** Promp for this challenge, used as value for "code",
** do not include in "testcode"
*/
#include <stdio.h>

void print_array();
void print_swapped_array();

void print_array() {
	// Write your solution here
}

void print_swapped_array() {
	// Write your solution here
}

// Uncomment the test functions and check run tests if you would like to run your code with provided tests
int main() {
    print_array();
    print_swapped_array();
    // test_print_array();
    // test_print_swapped_array();
    return 0;
}


/*
** Solutions for the tests, do not include in "testcode"
*/
void print_array() {
    int data[5] = {10, 30, 60, 50, 40};
    int * copy = data;
    int i;
    for (i = 0; i < 5; i++) {
        if (i == 4)
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
    int i;
    for (i = 0; i < 5; i++) {
        if (i == 4)
            printf("%d\n", *copy);
        else
            printf("%d ", *copy);
        copy++;
    }
}


/*
** Actually tests
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define CHILD 0

void print_array();
void print_swapped_array();
void test_print_array();
void test_print_swapped_array();

void test_print_array() {
    // Fork a process, which runs print_array
    // In parent process, read from child process and check result
    
    int fd[2];
    char buffer[512];
    memset(buffer, 0, 512);
    pipe(fd);
    pid_t pid = fork();
    if (pid == CHILD) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        print_array();
        printf("\n");
        exit(0);
    }
    else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        
        fgets(buffer, 512, stdin);
        if (strcmp(buffer, "10 30 60 50 40\n") == 0)
            printf(ANSI_COLOR_GREEN "test_print_array passed" ANSI_COLOR_RESET "\n");
        else {
            printf(ANSI_COLOR_RED "test_print_array failed" ANSI_COLOR_RESET "\n");
            printf("Your Output: %s", buffer);
            printf("Expected Output: 10 30 60 50 40\n");
        }
        // waitpid(pid, NULL, 0); // Cannot #include <sys/wait.h>, no resource.h file
    }
}

void test_print_swapped_array() {
    int fd[2];
    char buffer[512];
    memset(buffer, 0, 512);
    pipe(fd);
    pid_t pid = fork();
    if (pid == CHILD) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        print_swapped_array();
        exit(0);
    }
    else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        
        fgets(buffer, 512, stdin);
        if (strcmp(buffer, "40 30 60 50 10\n") == 0)
            printf(ANSI_COLOR_GREEN "test_print_swapped_array passed" ANSI_COLOR_RESET "\n");
        else {
            printf(ANSI_COLOR_RED "test_print_swapped_array failed" ANSI_COLOR_RESET "\n");
            printf("Your Output: %s\n", buffer);
            printf("Expected Output: 40 30 60 50 10\n");   
        }
        // waitpid(pid, NULL, 0);
    }
}
