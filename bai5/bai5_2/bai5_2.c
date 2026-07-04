#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 10
int a[MAX];
int count = 0;
sem_t sem_full;
sem_t sem_empty;

void *thread_add(void *arg) {
    while(1) {
        sem_wait(&sem_empty);
        int num = rand() % 100;
        a[count] = num;
        count++;
        printf("Them vao: %d | So phan tu: %d\n", num, count);
        sem_post(&sem_full);
        sleep(1);
    }
}

void *thread_remove(void *arg) {
    while(1) {
        sem_wait(&sem_full);
        if(count == 0) {
            printf("Nothing in array a\n");
        } else {
            count--;
            printf("Lay ra: %d | So phan tu: %d\n", a[count], count);
        }
        sem_post(&sem_empty);
        sleep(2);
    }
}

int main() {
    pthread_t t1, t2;
    sem_init(&sem_full, 0, 0);
    sem_init(&sem_empty, 0, MAX);
    pthread_create(&t1, NULL, thread_add, NULL);
    pthread_create(&t2, NULL, thread_remove, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&sem_full);
    sem_destroy(&sem_empty);
    return 0;
}
