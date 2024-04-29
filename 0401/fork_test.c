#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    
    int pid = fork();
    if (pid == 0) {
        write(1, "hello ", 6);
    } else {
        int status;
        wait(&status);
        write(1, "world\n", 6);
    }
    return 0;
}