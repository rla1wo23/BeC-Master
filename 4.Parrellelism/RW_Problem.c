#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int readcount = 0;
sem_t wsem, x;

char buffer[5];

void WRITE_UNIT()
{
    printf("writing...\n");
    for (int i = 0; i < 5; i++)
    {
        buffer[i] = rand() % 126; // 랜덤하게 문자열을 자료에 넣는다.
    }
}

void READ_UNIT()
{
    printf("Reading...\nThe contents is: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%c", buffer[i]); // 문자열을 읽는다.
    }
    printf("\n");
}

void *writer(void *arg)
{
    while (1)
    {
        printf("writer is called\n");
        sem_wait(&wsem);
        printf("writer is in critical section!\n");
        WRITE_UNIT();
        sem_post(&wsem);
        printf("writer went out from critical section!\n");
    }
    return NULL;
}

void *reader(void *arg)
{
    while (1)
    {
        printf("reader is called\n");
        sem_wait(&x);
        readcount++;
        if (readcount == 1)
        {
            printf("read count == 1\n");
            sem_wait(&wsem);
        }
        sem_post(&x);

        READ_UNIT();

        sem_wait(&x);
        readcount--;
        if (readcount == 0)
        {
            sem_post(&wsem);
        }
        sem_post(&x);
    }
    return NULL;
}

int main()
{
    for (int i = 0; i < 5; i++)
    {
        buffer[i] = rand() % 126; // 랜덤하게 문자열을 자료에 넣는다.
    }
    for (int i = 0; i < 5; i++)
    {
        printf("%c", buffer[i]); // 현재 문자열을 읽는다.
    }
    printf("\n");

    sem_init(&wsem, 0, 1);
    sem_init(&x, 0, 0);
    readcount = 0;
    pthread_t writer_thread, reader_thread1, reader_thread2;

    pthread_create(&writer_thread, NULL, writer, NULL);
    pthread_create(&reader_thread1, NULL, reader, NULL);
    pthread_create(&reader_thread2, NULL, reader, NULL);

    pthread_join(writer_thread, NULL);
    pthread_join(reader_thread1, NULL);
    pthread_join(reader_thread2, NULL);

    sem_destroy(&x);
    sem_destroy(&wsem);

    return 0;
}