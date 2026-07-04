#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int x1=2, x2=3, x3=4, x4=5, x5=6, x6=7;
int w, v, y, z, ans;

sem_t sem_v;
sem_t sem_w;
sem_t sem_y;
sem_t sem_z;

void *calc_w(void *arg) {
    w = x1 * x2;
    printf("w = %d\n", w);
    sem_post(&sem_w);
    sem_post(&sem_w);
    return NULL;
}

void *calc_v(void *arg) {
    v = x3 * x4;
    printf("v = %d\n", v);
    sem_post(&sem_v);
    sem_post(&sem_v);
    return NULL;
}

void *calc_y(void *arg) {
    sem_wait(&sem_v);
    y = v * x5;
    printf("y = v*x5 = %d\n", y);
    sem_wait(&sem_w);
    y = w * y;
    printf("y = w*y = %d\n", y);
    sem_post(&sem_y);
    return NULL;
}

void *calc_z(void *arg) {
    sem_wait(&sem_v);
    z = v * x6;
    printf("z = v*x6 = %d\n", z);
    sem_wait(&sem_w);
    z = w * z;
    printf("z = w*z = %d\n", z);
    sem_post(&sem_z);
    return NULL;
}

void *calc_ans(void *arg) {
    sem_wait(&sem_y);
    sem_wait(&sem_z);
    ans = y + z;
    printf("ans = y + z = %d\n", ans);
    return NULL;
}

int main() {
    pthread_t tw, tv, ty, tz, tans;
    sem_init(&sem_v, 0, 0);
    sem_init(&sem_w, 0, 0);
    sem_init(&sem_y, 0, 0);
    sem_init(&sem_z, 0, 0);
    pthread_create(&tans, NULL, calc_ans, NULL);
    pthread_create(&ty, NULL, calc_y, NULL);
    pthread_create(&tz, NULL, calc_z, NULL);
    pthread_create(&tw, NULL, calc_w, NULL);
    pthread_create(&tv, NULL, calc_v, NULL);
    pthread_join(tw, NULL);
    pthread_join(tv, NULL);
    pthread_join(ty, NULL);
    pthread_join(tz, NULL);
    pthread_join(tans, NULL);
    sem_destroy(&sem_v);
    sem_destroy(&sem_w);
    sem_destroy(&sem_y);
    sem_destroy(&sem_z);
    return 0;
}
