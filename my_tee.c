#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFF 1000

void exitErr();
void writeToFile(int fd);


int main(int argc, char *argv[]){


    if (argc < 2){
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1],
        O_WRONLY | O_CREAT | O_TRUNC,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
    );

    if(fd == -1){
        exitErr();
    }

    writeToFile(fd);

    if((close(fd)) == -1){
        exitErr();
    }

    exit(EXIT_SUCCESS);
}


void exitErr(){
    fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
}



void writeToFile(int fd){
    int c;
    int index = 0;
    int numByte;
    char buff[BUFF];
    while((c = getchar()) != EOF){
            if (c != 10 || index >= BUFF){
                buff[index++] = c;
            }else{
                buff[index++] = c;
                printf("%s", buff);
                numByte = write(fd, buff, index);
                if (numByte != index){
                    exitErr();
                }
                index = 0;
            }
        }


}


