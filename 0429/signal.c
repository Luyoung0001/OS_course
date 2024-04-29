#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5

sem_t mutex, producer_sem, consumer_sem;
int buffer[N] = {0};
int in = 0, out = 0;

void *producer(void *arg) {
    while (1) {
        sleep(5);
        int item = rand() % 100; // 产生一个随机物品
        sem_wait(&consumer_sem); // 等待有空缓冲区
        sem_wait(&mutex);        // 互斥访问缓冲区
        buffer[in] = item;
        in = (in + 1) % N;

        printf("Produced item: %d\n", item);
        sem_post(&mutex);
        sem_post(&producer_sem); // 发出信号给消费者
    }
}

void *consumer(void *arg) {
    while (1) {
        sleep(4);
        sem_wait(&producer_sem); // 等待有物品可消费
        sem_wait(&mutex);        // 互斥访问缓冲区
        int item = buffer[out];
        out = (out + 1) % N;
        printf("Consumed item: %d\n", item);
        sem_post(&mutex);
        sem_post(&consumer_sem); // 释放空缓冲区信号给生产者
    }
}

int main() {
    (void)sem_init(&mutex, 0, 1);
    (void)sem_init(&producer_sem, 0, 0);
    (void)sem_init(&consumer_sem, 0, 3);
    int mutex_val, producer_sem_val, consumer_sem_val;
    sem_getvalue(&mutex, &mutex_val);
    sem_getvalue(&producer_sem, &producer_sem_val);
    sem_getvalue(&consumer_sem, &consumer_sem_val);

    printf("Mutex value: %d, Producer Semaphore value: %d, Consumer Semaphore value: %d\n", mutex_val, producer_sem_val, consumer_sem_val);
    printf("%d %d %d\n", mutex, producer_sem, consumer_sem);

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    (void)sem_destroy(&mutex);
    (void)sem_destroy(&producer_sem);
    (void)sem_destroy(&consumer_sem);

    return 0;
}
