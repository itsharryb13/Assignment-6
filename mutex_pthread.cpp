#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int dataVariable = 0;
pthread_mutex_t mutex;

void* writer(void* arg) {
    int i = 0;
    do {
        pthread_mutex_lock(&mutex);
        dataVariable = i;
        printf("Writer: Wrote %d to shared_data\n", dataVariable);
        pthread_mutex_unlock(&mutex); 
        i++;
        sleep(1);
    } while (i < 10);
    return NULL;
}

void* reader(void* arg) {
    int i = 0;
    do {
        pthread_mutex_lock(&mutex); 
        int d = dataVariable;   
        printf("Reader: Read %d from shared_data\n", d);
        pthread_mutex_unlock(&mutex);
        i++;
        sleep(1); 
    } while (i < 10);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, writer, NULL);
    pthread_create(&thread2, NULL, reader, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
