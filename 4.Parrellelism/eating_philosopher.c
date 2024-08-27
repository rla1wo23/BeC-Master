#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
int eatCount = 0;
#define NUM 5
sem_t forks[NUM]; // forks
sem_t room;
void pickup(int philosopher_num)
{
    sem_wait(&forks[philosopher_num % NUM]);
}
void putdown(int philosopher_num)
{
    sem_post(&forks[philosopher_num % NUM]);
}
void thinking(int philosopher_num)
{
    printf("philosopher %d is thinking\n", philosopher_num);
}
void eating(int philosopher_num)
{
    eatCount++;
    printf("philosopher %d is eating\n", philosopher_num);
}
void *philosopher(void *arg)
{
    int philosopher_num;
    philosopher_num = (unsigned long int)arg;
    while (eatCount < 10000)
    {
        sem_wait(&room);
        pickup(philosopher_num);
        printf("philosopher %d picks up the fork %d.\n", philosopher_num, philosopher_num);
        pickup(philosopher_num + 1);
        printf("philosopher %d picks up the fork %d.\n", philosopher_num, (philosopher_num + 1) % NUM);
        eating(philosopher_num);
        putdown(philosopher_num + 1);
        printf("philosopher %d puts down the fork %d.\n", philosopher_num, (philosopher_num + 1) % NUM);
        putdown(philosopher_num);
        printf("philosopher %d puts down the fork %d.\n", philosopher_num, philosopher_num);
        sem_post(&room);
        thinking(philosopher_num);
    }
}
int main()
{
    eatCount = 0;
    pthread_t threads[NUM];
    for (int i = 0; i < NUM; i++)
    {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&room, 0, 4);
    for (unsigned long int i = 0; i < NUM; i++)
    {
        pthread_create(&threads[i], NULL, philosopher, (void *)i);
    }
    for (int i = 0; i < NUM; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("NO DEADLOCK\n");
    return 0;
}