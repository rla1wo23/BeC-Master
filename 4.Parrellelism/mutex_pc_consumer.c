#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 100
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int consumerValue;
int value;
int count = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void put(int value)
{
    buffer[in] = value;
    in = (in + 1) % BUFFER_SIZE;
    count++;
}

int get()
{
    int data = buffer[out];
    buffer[out] = 0;
    out = (out + 1) % BUFFER_SIZE;
    count--;
    return data;
}

void produce()
{
    value = rand() % 100;
    printf("생산자 생산값: %d\n", value);
}

void consume()
{
    printf("소비자 소비 값: %d\n", consumerValue);
}

void *producer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&m);
        while (count == BUFFER_SIZE){
		printf("buffer is fulled! i have to wait(producer)!\n"); 
            pthread_cond_wait(&empty, &m);
}
        produce();
        put(value);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&m);
        while (count == 0){
		printf("buffer is empty! i have to wait(consumer)!\n");
            pthread_cond_wait(&fill, &m);
	}
        consumerValue = get();
        consume();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main()
{
    pthread_t TP, TC, TC2;

    pthread_create(&TP, NULL, producer, NULL);
    pthread_create(&TC, NULL, consumer, NULL);
    pthread_create(&TC2, NULL, consumer, NULL);

    pthread_join(TP, NULL);
    pthread_join(TC, NULL);
    pthread_join(TC2, NULL);

    int totalCount = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        totalCount += buffer[i];
    }
    if (totalCount == 0)
    {
        printf("Successfully Done!\n");
    }
    else
    {
        printf("Error...\n");
    }
    return 0;
}
