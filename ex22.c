#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

#define MAXLENGTH 400
void readLine(char * arr, char *pathToConf, int lineNum);
void enterSubFolder(char *firstLine);
void compile(char *pathToCompile, char *sfileName);
void runPrograms(char *firstLine,char *secondLine, int fdAnswer,char *thirdLine);
void alarm_handler(int sig);
void  compare(char *nameoffile,int fdAnswer,char *thirdLine);
void removefiles(char *firstLine);

int main(int argc, char *argv[]){
if(argc!=2){
    perror("not valid arguments");
}

    int error= open("errors.txt",O_RDWR|O_CREAT ,S_IRWXU);
    dup2(error,2);
    int fdAnswer = open("results.csv", O_RDWR|O_CREAT ,S_IRWXU );
    int oldDup = dup(1);
    dup2(fdAnswer, 1);
    write(1, "\n", 1);
    dup2(oldDup, 1);
    char firstLine[MAXLENGTH];
    memset(firstLine, '\0', MAXLENGTH);
    char secondLine[MAXLENGTH];
    memset(secondLine, '\0', MAXLENGTH);
    char thirdLine[MAXLENGTH];
    memset(thirdLine, '\0', MAXLENGTH);
    readLine(firstLine,argv[1],1);

    enterSubFolder(firstLine);


    readLine(secondLine,argv[1],2);
    readLine(thirdLine,argv[1],3);
    runPrograms(firstLine,secondLine,fdAnswer,thirdLine);
    removefiles(firstLine);
    dup2(fdAnswer, 1);
    write(1, "\n", 1);
    dup2(oldDup, 1);
}
void readLine(char *arr, char *pathToConf, int lineNumber) {
    int fd = open(pathToConf, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(-1);
    }

    int currentLineNumber = 1;
    int i = 0;

    while (currentLineNumber < lineNumber) {
        char c;
        ssize_t count = read(fd, &c, 1);

        if (count == -1) {
            perror("Error in read");
            exit(-1);
        }

        if (c == '\n') {
            currentLineNumber++;
        }
    }

    while (i < MAXLENGTH) {
        ssize_t count = read(fd, &arr[i], 1);
        if (count == -1) {
            perror("Error in read");
            exit(-1);
        }

        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
        i++;
    }

    close(fd);
}


void enterSubFolder(char *firstLine) {

    DIR *pDir;
    struct dirent *pDirent;
    if ((pDir = opendir(firstLine)) == NULL) {
        perror("Error opening directory");
        exit(1);
    }
    while ((pDirent = readdir(pDir)) != NULL) {
        if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0) {
            continue;
        }
        char path[MAXLENGTH];
        snprintf(path, sizeof(path), "%s/%s", firstLine, pDirent->d_name);
        struct stat sb;
        //if its a folder and its contain something...
        if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {

            DIR *subDir;
            struct dirent *subDirent;

            if ((subDir = opendir(path)) == NULL) {
                perror("Error opening subdirectory");
                exit(1);
            }
            while ((subDirent = readdir(subDir)) != NULL) {
                if (subDirent->d_type == DT_REG) {
                    //check c files.
                    char *ext = strrchr(subDirent->d_name, '.');
                    if (ext != NULL && strcmp(ext, ".c") == 0) {

                        //here need to fork and compile








                   compile(path,subDirent->d_name);

                    }
                }
            }
            closedir(subDir);
        }



        else if (stat(path, &sb) != 0){
            printf("problem");
        }
    }
    closedir(pDir);
}


void removefiles(char *firstLine){
    DIR *pDir;
    struct dirent *pDirent;
    if ((pDir = opendir(firstLine)) == NULL) {
        perror("Error opening directory");
        exit(1);
    }
    while ((pDirent = readdir(pDir)) != NULL) {
        if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0) {
            continue;
        }
        char buffer[MAXLENGTH];
        memset(buffer,'\0',MAXLENGTH);
        snprintf(buffer, sizeof(buffer), "%s.txt", pDirent->d_name);
        if (access(buffer, F_OK) == 0) {
            // file exists
          int  ret = remove(buffer);

            if(ret == 0) {
     //not error in delete
            } else {
               //error in delete
            }
        } else {
     //file not exists
        }





    }
    closedir(pDir);
}









void runPrograms(char *firstLine, char *secondLine, int fdAnswer,char *thirdLine) {
    DIR *pDir;
    struct dirent *pDirent;

    if ((pDir = opendir(firstLine)) == NULL) {
        perror("Error opening directory");
        exit(1);
    }

    while ((pDirent = readdir(pDir)) != NULL) {
        if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0) {
            continue;
        }

        char path[MAXLENGTH];
        snprintf(path, sizeof(path), "%s/%s", firstLine, pDirent->d_name);
        struct stat sb;

        // here i go inside each subfolder
        if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
            DIR *subDir;
            struct dirent *subDirent;

            if ((subDir = opendir(path)) == NULL) {
                perror("Error opening subdirectory");
                exit(1);
            }

            int foundCFile = 0;
            int foundOutFile = 0;
            while ((subDirent = readdir(subDir)) != NULL) {
                // check for a.out file
                if (strcmp(subDirent->d_name, "a.out") == 0) {
                    foundOutFile = 1;
                }

                // check for .c file
                char *ext = strrchr(subDirent->d_name, '.');
                if (ext != NULL && strcmp(ext, ".c") == 0) {
                    foundCFile = 1;
                }
            }
            if(!foundCFile &&!foundOutFile){

                int oldDup = dup(1);
                dup2(fdAnswer, 1);

                char output[MAXLENGTH];
                memset(output,'\0',MAXLENGTH);
                snprintf(output, sizeof(output), "%s,0,NO_C_FILE\n", pDirent->d_name);
                write(1, output, strlen(output));
                dup2(oldDup, 1);


            }


            //if there is c file and not .out file
            if (foundCFile && !foundOutFile) {

                int oldDup = dup(1);
                dup2(fdAnswer, 1);

                char output[MAXLENGTH];
                memset(output,'\0',MAXLENGTH);
                snprintf(output, sizeof(output), "%s,10,COMPILATION_ERROR\n", pDirent->d_name);
                write(1, output, strlen(output));
                dup2(oldDup, 1);
            }

//here is if  I find .out file in the sub folder
            else if (foundOutFile) {

                int fdInput = open(secondLine, O_RDONLY);
                pid_t pid = fork();
                //error
                if (pid == -1) {
                    perror("Fork failed\n");
                    exit(EXIT_FAILURE);
                }
                //son

                else if (pid == 0) {
                    char filename[100];

                    //runing all the .a.out from the subdirctorys
                    snprintf(filename, sizeof(filename), "%s.txt", pDirent->d_name);






                        int fdanswer2 = open(filename, O_RDWR | O_CREAT, S_IRWXU);





                    dup2(fdanswer2, 1);
                    close(fdanswer2);
                    // Redirect stdin to the input file
                    dup2(fdInput, STDIN_FILENO);
                    close(fdInput);
                    chdir(path);
                    char *args[] = {"./a.out", NULL};
                    // Run the program with input from the file
                    signal(SIGALRM, alarm_handler);
                    alarm(5); // Set timer for 5 seconds

                    int ret = execvp(args[0], args);
                    if (ret == -1) {
                        perror("execvp() failed");
                        exit(EXIT_FAILURE);
                    }

                }
                //father
                else {
                      int  status;
                       waitpid(pid,  &status, 0);


                    //this is if its take less than 5 seconds.
                    if (WIFEXITED(status)) {

                        int exit_status = WEXITSTATUS(status);
                        //add here the comp function..
                        char filename[100];
                        //asuming that there is no EtaiEtai.txt files in that dirctory before i create them

                        snprintf(filename, sizeof(filename), "%s.txt", pDirent->d_name);
                        compare(filename,fdAnswer,thirdLine);




                    }


                    //this is if  its take more than 5 seconds
                    else if (WIFSIGNALED(status)) {
                        int signal_num = WTERMSIG(status);









                        int oldDup = dup(1);
                        dup2(fdAnswer, 1);

                        char output[MAXLENGTH];
                        memset(output,'\0',MAXLENGTH);
                        snprintf(output, sizeof(output), "%s,20,TIMEOUT\n", pDirent->d_name);
                        write(1, output, strlen(output));
                        dup2(oldDup, 1);
                        close(oldDup);


                    }


                }

            }


            closedir(subDir);
        }



        else if (stat(path, &sb) != 0) {

            printf("problem");


        }
    }
    closedir(pDir);
}


void  compare (char *nameoffile, int fdAnswer,char *thirdLine){

    pid_t pid = fork();
    int status;
    if (pid==-1) {
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) {

        char *args[] = {"./comp.out", nameoffile, thirdLine, NULL};
        int ret = execv("./comp.out", args);
        if (ret == -1) {
            perror("execvp() failed");
            exit(EXIT_FAILURE);
        }
    }
    else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            int oldDup = dup(1);
            dup2(fdAnswer, 1);

            char output[MAXLENGTH];
            memset(output,'\0',MAXLENGTH);
            char fileWithout_txt[strlen(nameoffile) - 4];
            for (int i = 0; i < strlen(nameoffile) - 4; i++) {
                fileWithout_txt[i] = nameoffile[i];
            }
            fileWithout_txt[strlen(nameoffile) - 4] = '\0';

            if (exit_status == 1) {


                snprintf(output, sizeof(output), "%s,100,EXCELLENT\n", fileWithout_txt);
                write(1, output, strlen(output));


            } else if (exit_status == 2) {

                snprintf(output, sizeof(output), "%s,50,WRONG\n", fileWithout_txt);
                write(1, output, strlen(output));


            } else if (exit_status == 3) {
                snprintf(output, sizeof(output), "%s,75,SIMILAR\n", fileWithout_txt);
                write(1, output, strlen(output));

            }
            dup2(oldDup, 1);



        }

    }


}









void alarm_handler(int sig) {

    exit(EXIT_FAILURE);
}















void compile(char *pathToCompile,char * fileName){
    pid_t pid = fork();
    int status;
    if (pid==-1) {
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        char filePath[MAXLENGTH];
        sprintf(filePath, "%s/%s", pathToCompile, fileName);

        char *args[] = {"gcc", filePath, "-o", "a.out", NULL};


        // Compile file using gcc
        int ret = execvp("gcc", args);
        if (ret == -1) {
            perror("execvp() failed");
            exit(EXIT_FAILURE);
        }
    }
    else {
        waitpid(pid, &status, 0);


    }

}


