Q1) write a C program that creates two threads each thread should printa message indicating it is running.
	The main thread should wait for both threads to finish before exiting
Q2) write a C program to create 5 threads .Each thtreads should print its thread ID and than exit.
	The main thread should join all threads and print a complection message 
Q3) Write a program that creates a thread which prints numbers from 1 to 10 with a 1-second delay between each number.
	The main thread should wait for this thread to finish.
Q4) Create two threads where one thread increments a global counter 100 times and the other thread decrements the 
	same counter 100 times.Print the final value of the counter after both threads finish
Q5) implement a thread function that take an integer argument, squares it, 
	and returns the result to the main thread using pthread_exit and pthread_join
	
	
#include <stdio.h>
#include <pthread.h>

void* threadFunction(void* arg) {
    printf("Thread %ld is running.\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, threadFunction, (void*)1);
    pthread_create(&t2, NULL, threadFunction, (void*)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads have finished.\n");
    return 0;
}





#include <stdio.h>
#include <pthread.h>

void* printThreadID(void* arg) {
    printf("Thread ID: %ld\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[5];

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, printThreadID, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");
    return 0;
}


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* countToTen(void* arg) {
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t counterThread;
    pthread_create(&counterThread, NULL, countToTen, NULL);
    pthread_join(counterThread, NULL);
    printf("Counting thread completed.\n");
    return 0;
}



#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock;

void* increment(void* arg) {
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* decrement(void* arg) {
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&lock);
        counter--;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t incThread, decThread;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&incThread, NULL, increment, NULL);
    pthread_create(&decThread, NULL, decrement, NULL);

    pthread_join(incThread, NULL);
    pthread_join(decThread, NULL);

    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", counter);
    return 0;
}





#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* square(void* arg) {
    int num = *(int*)arg;
    int* result = malloc(sizeof(int));
    *result = num * num;
    pthread_exit(result);
}

int main() {
    pthread_t thread;
    int num = 5;
    int* result;

    pthread_create(&thread, NULL, square, &num);
    pthread_join(thread, (void**)&result);

    printf("Square of %d is %d\n", num, *result);
    free(result);

    return 0;
}
