#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/wait.h>

bool identical(char * first,char * second);
bool similar (char * first, char * second);
int main(int argc, char *argv[]) {
    if(argc!=3){
        perror("bad arguments");
        exit(-1);
    }
     bool x=identical(argv[1],argv[2]);
    if (x==true){
        return 1;
    }

        x=similar(argv[1],argv[2]);
        if(x==true){
            return 3;
        }
        else{
            return 2;
        }


    if (x == true) {
        return 1;
    }

    x = similar(argv[1], argv[2]);
    if (x == true) {
        return 3;
    }

    return 2;
}
bool identical(char * first,char * second){
     int fd1 = open(first, O_RDONLY);
    int fd2 = open(second, O_RDONLY);
      if (fd1 == -1) {
          perror("Error opening file");
          exit(-1);
      }
    if (fd2 == -1) {
        perror("Error opening file");
        close(fd1);
        exit(-1);
    }
      char byte1, byte2;
      while (1){

          ssize_t count1 = read(fd1, &byte1, 1);
          if  (count1==-1){
              close(fd1);
              close(fd2);
              perror("Error in: read");
              exit(-1);
          }
          ssize_t count2 = read(fd2, &byte2, 1);
          if (count2==-1){
              close(fd1);
              close(fd2);
              perror("Error in: read");
              exit(-1);
          }
          if(count1==0&&count2==0){
              close(fd1);
              close(fd2);
              return true;
          }
          if(byte1!=byte2){
              close(fd1);
              close(fd2);
              return false;
          }
      }

}
//return 1 if they are similar if not return 0
bool similar (char * first, char * second) {
    int fd1 = open(first, O_RDONLY);
    int fd2 = open(second, O_RDONLY);
    if (fd1 == -1) {
        perror("Error opening file");
        exit(-1);
    }
    if (fd2 == -1) {
        perror("Error opening file");
        close(fd1);
        exit(-1);
    }
    char byte1, byte2;
    while (1) {

        ssize_t count1 = read(fd1, &byte1, 1);
        if (count1 == -1) {
            close(fd1);
            close(fd2);
            perror("Error in: read");
            exit(-1);
        }
        while (byte1 == '\n' || byte1 == '\r' || byte1 == ' ' || byte1 == '\f' || byte1 == '\t' || byte1 == '\v') {
            count1 = read(fd1, &byte1, 1);
            if (count1 == -1) {
                close(fd1);
                close(fd2);
                perror("Error in: read");
                exit(-1);
            }
            if (count1==0){
                break;
            }

        }

        ssize_t count2 = read(fd2, &byte2, 1);
        if (count2 == -1) {
            close(fd1);
            close(fd2);
            perror("Error in: read");
            exit(-1);
        }
        while (byte2 == '\n' || byte2 == '\r' || byte2 == ' ' || byte2 == '\f' || byte2 == '\t' || byte2 == '\v') {
            count2 = read(fd2, &byte2, 1);
            if (count2 == -1) {
                close(fd1);
                close(fd2);
                perror("Error in: read");
                exit(-1);
            }
            if (count2==0){
                break;
            }
        }
        if (count1 == 0 && count2 == 0) {
            return true;
        }

        if (isalpha(byte1)) {
            byte1 = tolower(byte1);
        }
        if (isalpha(byte2)) {
            byte2 = tolower(byte2);
        }
        if (byte1 != byte2) {
            close(fd1);
            close(fd2);
            return false;
        }

    }
}






