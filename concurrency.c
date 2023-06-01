#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_TOYS 5

int count = 0;
sem_t m, fullBox, emptyBox;

void getToyFromBox() {
    count--;
    printf("Child got a toy. Toys left in the box: %d\n", count);
}

void play() {
    printf("Child is playing with the toy.\n");
    sleep(1);
}

void refillToyBox(int numToys) {
    count += numToys;
    printf("Mother refilled the toy box. Toys in the box: %d\n", count);
}

void* motherThread(void* arg) {
    while (1) {
        sem_wait(&emptyBox);

        if(count==0){
            refillToyBox(MAX_TOYS);
        }

        sem_post(&fullBox);
    }

    return NULL;
}

void* childThread(void* arg) {
    while (1) {
        sem_wait(&fullBox);

        if (count > 0) {
            getToyFromBox();
            play();
        }
	sem_post(&emptyBox);
    }

    return NULL;
}

int main() {
    sem_init(&m, 0, 1);
    sem_init(&fullBox, 0, 0);
    sem_init(&emptyBox, 0, 1);

    pthread_t mother, child;
    pthread_create(&mother, NULL, motherThread, NULL);
    pthread_create(&child, NULL, childThread, NULL);

    while (1) {
        // The main thread can perform other tasks if needed
        // or it can simply sleep to prevent it from terminating immediately
        sleep(1);
    }

    sem_destroy(&m);
    sem_destroy(&fullBox);
    sem_destroy(&emptyBox);

    return 0;
}
