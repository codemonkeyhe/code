#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *Athread_function(void *arg);
void *Bthread_function(void *arg);

char message[] = "Hello World";


pthread_t a_thread;
pthread_t b_thread;



int main() {
    int res;
    void *thread_result;
    res = pthread_create(&a_thread, NULL, Athread_function, (void *)message);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&b_thread, NULL, Bthread_function, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    sleep(1);
    printf("Waiting for thread to finish...\n");
    //res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    sleep(100);
    /*printf("Thread joined, it returned %s\n", (char *)thread_result);*/
    printf("Message is now %s\n", message);
    exit(EXIT_SUCCESS);
}

void *Athread_function(void *arg) {
    printf("thread A is running. Argument was %s\n", (char *)arg);
    sleep(60);
    strcpy(message, "Bye!");
    pthread_exit("Thank you for the CPU time");
}

void *Bthread_function(void *arg) {
    printf("thread B is running. Argument was %s\n", (char *)arg);
    int res;
    void *thread_result;
    res = pthread_join(a_thread, &thread_result);
    printf("B Thread joined A, A returned %s\n", (char *)thread_result);
    pthread_exit(" BBB exit");
}
