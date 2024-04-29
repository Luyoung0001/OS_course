#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

#define gettid() syscall(__NR_gettid)

pthread_t ntid;

void *printids(void *s) {
    pid_t pid;
    pid_t ktid;
    pthread_t utid;
    pid = getpid();
    ktid = gettid();
    utid = pthread_self();
    printf("%s pid %lu ktid %lu utid %lu(0x%lx)\n", (char *)s,
           (unsigned long)pid, (unsigned long)ktid,
           (unsigned long)utid, (unsigned long)utid);
    pause();
    return NULL;
}

int main(void) {
    pthread_create(&ntid, NULL, printids, (void *)" new thread:");
    printids("main thread:");
    sleep(1);
    pthread_join(ntid, NULL); // 等待新线程结束
    return 0;
}
