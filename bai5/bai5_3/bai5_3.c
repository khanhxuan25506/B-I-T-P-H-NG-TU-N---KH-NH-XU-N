#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;

void *processA(void *arg) {
    while(1) {
        x = x + 1;
        if(x == 20)
            x = 0;
        printf("A: x = %d\n", x);
    }
}

void *processB(void *arg) {
    while(1) {
        x = x + 1;
        if(x == 20)
            x = 0;
        printf("B: x = %d\n", x);
    }
}

int main() {
    pthread_t tA, tB;
    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    return 0;
}
