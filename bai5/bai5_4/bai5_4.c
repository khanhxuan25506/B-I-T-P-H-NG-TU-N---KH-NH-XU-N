#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;
pthread_mutex_t mutex;

void *processA(void *arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if(x == 20)
            x = 0;
        printf("A: x = %d\n", x);
        pthread_mutex_unlock(&mutex);
        usleep(1000);
    }
}

void *processB(void *arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if(x == 20)
            x = 0;
        printf("B: x = %d\n", x);
        pthread_mutex_unlock(&mutex);
        usleep(1000);
    }
}

int main() {
    pthread_t tA, tB;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}
