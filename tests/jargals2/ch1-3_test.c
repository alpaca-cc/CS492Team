#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void test_message_file(){
    char* file_name = "message.txt";
    struct stat file_stat;
    
    if(stat(file_name,&file_stat)==0){
        if(file_stat.st_mode & S_IRGRP){
            printf("Readable by group. Please set file permission only readable by the user\n");
            return;
        }
        if(file_stat.st_mode & S_IWGRP){
            printf("Writable by group. Please set file permission to only readable by the user\n");
            return;
        }
        if(file_stat.st_mode & S_IXGRP){
            printf("Executable by group. Please set file permission to only readable by the user\n");
            return;
        }
        if(file_stat.st_mode & S_IROTH){
            printf("Readable by others. Please, set file permission to only readable by the user\n");
            return;
        }
        if(file_stat.st_mode & S_IWOTH){
            printf("Writable by others. Please, set file permission to only readable by the user\n");
            return;
        }
        if(file_stat.st_mode & S_IXOTH){
            printf("Executable by others. Please, set file permission to only readable by the user\n");
            return;
        }
        if(!(file_stat.st_mode & S_IRUSR)){
            printf("Is not readable by the user\n");
            return;
        }
        else{
            FILE *file = fopen(file_name,"r+");
            int length=0;
            char *buffer;
            if(file){
                fseek(file,0,SEEK_END);
                length = ftell(file);
                fseek(file,0,SEEK_SET);
                buffer = malloc(length+1);
                if(buffer) fread(buffer,1,length,file);
                char *content = "hello!";
                if(length!=0 && length<=7 &&(strncmp(buffer,content,6)==0)){
                    printf("CORRECT\n");
                    
                }else{
                    printf("Your file content is not correct\n");
                }
                free(buffer);
            }
            fclose(file);

        }

    }else{
        printf("message.txt does not exist\n"); 
    }
}

int main(){
    test_message_file();
    return 0;
}
