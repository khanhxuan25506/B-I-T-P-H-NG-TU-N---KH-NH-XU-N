#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_sell;
sem_t sem_make;
int sells = 0;
int products = 0;

void *processA(void *arg) {
    while(1) {
        sem_wait(&sem_sell);
        sells++;
        printf("Sells: %d, Products: %d\n", sells, products);
        sleep(1);
    }
}

void *processB(void *arg) {
    while(1) {
        products++;
        printf("Products: %d, Sells: %d\n", products, sells);
        sem_post(&sem_sell);
        if(products - sells >= 42)
            sem_wait(&sem_make);
        sleep(1);
    }
}

int main() {
    pthread_t tA, tB;
    sem_init(&sem_sell, 0, 0);
    sem_init(&sem_make, 0, 0);
    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    sem_destroy(&sem_sell);
    sem_destroy(&sem_make);
    return 0;
}
