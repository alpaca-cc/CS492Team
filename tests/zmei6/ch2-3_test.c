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

// takes a string argument and print out its chars and values of the chars
void print_char_values(char* str){
	char* cur_char = str;
	while(*cur_char){
		printf("%c %d\n", *cur_char, *cur_char);
		cur_char++;
	}
}

// takes a string argument and print in reverse order
void print_reverse(char* str){
	int length = strlen(str);
	char* cur_char = str+length-1;
	while(cur_char != str){
		printf("%c",*cur_char);
		cur_char--;
	}
	printf("%c",*cur_char);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// testing:
// 1. Use print("%c %d\n", *ptr, *ptr) to print out the characters
// and their integer values of the message "A B C 0123"
// the message "A B C 0123" (one character and its integer value per line)?
// 2. write a C program that uses char* pointers to print a 
// message in revers? e.g. "dlroW olleH" should be printed as "Hello World"

#define CHILD 0

void test_print_char_values(){
    int fd[2];
    char buffer[512];
    memset(buffer, 0, 512);
    pipe(fd);
    pid_t pid = fork();
    if(pid == CHILD) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        char* str = "A B C 0123";
        print_char_values(str);
        exit(0);
    }
    else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        char* test_str = "A B C 0123";
		int failed = 0;
        while(fgets(buffer,512,stdin)!=NULL){
        	char test_output[30];
        	sprintf(test_output,"%c %d\n",*test_str,*test_str);
        	test_str++;
          	if(strcmp(buffer,test_output)!=0){
        		failed = 1;
        		break;
        	}
        }
        if (failed){
        	printf("test_print_char_values failed\n");
        }else{
        	printf("test_print_char_values passed\n");
        }
        waitpid(pid, NULL, 0);
    }
}


void test_print_reverse(){
    int fd[2];
    char buffer[512];
    memset(buffer, 0, 512);
    pipe(fd);
    pid_t pid = fork();
    if(pid == CHILD) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        char* str = "Hello World";
        print_reverse(str);
        exit(0);
    }
    else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        fgets(buffer, 512, stdin);
        if(strcmp(buffer, "dlroW olleH") == 0)
            printf("test_print_reverse passed\n");
        else{
            printf("test_print_reverse failed\n");
        }
        waitpid(pid, NULL, 0);
    }
}


int main(){
	test_print_reverse();
	test_print_char_values();
	return 0;
}







