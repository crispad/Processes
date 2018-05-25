// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write 
// the three messages to the parent and have the parent print out 
// the messages. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 16

char* msg1 = "hello world #1";
char* msg2 = "hello world #2";
char* msg3 = "hello world #3";

int main()
{
   int p[2];

   if (pipe(p) < 0) {
       printf("Pipe failed.\n");
       exit(1);
   } 
    
    int rc = fork();
    char buff[MSGSIZE];

    if (rc < 0) {
        printf("Fork failed.\n");
        exit(1);
    }else if (rc == 0) {
        printf("This is where the child writes.\n");
        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);
    }else {
        int wc = waitpid(rc, NULL, 0);
        close(p[1]);
        printf("This is where the parent reads.\n");
        for (int i = 0; i < 3; i++) {
            read(p[0], buff, MSGSIZE);
            printf("%s\n", buff);
        }
    }
    
    return 0;
}
