#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 101
sem_t n;
sem_t s;
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int consumerValue;
int value;

void produce()
{
    value = rand() % 100;
    printf("생산자 생산값: %d\n", value);
}

void append()
{
    buffer[in] = value;
    in = (in + 1) % BUFFER_SIZE;
}

void consume()
{
    printf("소비자 소비 값: %d\n", consumerValue);
}

void take()
{
    consumerValue = buffer[out];
    buffer[out] = 0;
    out = (out + 1) % BUFFER_SIZE;
}
int produced;

void *producer(void *arg)
{
    while (produced < 100)
    {
        sem_wait(&s);
        produce();
        append();
        produced++;
        sem_post(&s);
        sem_post(&n);
    }
    return NULL;
}
int consumed;
void *consumer(void *arg)
{
printf("produced%d\n",produced);
    while (consumed < 100)
    {
        sem_wait(&n);
        sem_wait(&s);
        take();
        consume();
        consumed++;
        sem_post(&s);
	printf("counsumed%d\n",consumed);
    }

    return NULL;
}

int main()
{
    produced=0;
    consumed=0;
    sem_init(&n, 0, 0);
    sem_init(&s, 0, 1);

    pthread_t TP, TC_1, TC_2;

    pthread_create(&TP, NULL, producer, NULL);
    pthread_create(&TC_1, NULL, consumer, NULL);
    pthread_create(&TC_2, NULL, consumer, NULL);

    pthread_join(TP, NULL);
    pthread_join(TC_1, NULL);
    pthread_join(TC_2, NULL);
    sem_destroy(&n);
    sem_destroy(&s);

    printf("Here's result:\n");
    int count = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        count += buffer[i];
    }
    if (count == 0)
    {
        printf("Successfully Done!\n");
    }
    else
    {
        printf("Error...\n");
    }

    return 0;
}
