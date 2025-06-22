//Question 01:
#include <stdio.h>
#include <pthread.h>

void* threadFunc(void* arg) {
    int threadNum = *(int*)arg;
    printf("Thread %d is running.\n", threadNum);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int t1_id = 1, t2_id = 2;

    pthread_create(&t1, NULL, threadFunc, &t1_id);
    pthread_create(&t2, NULL, threadFunc, &t2_id);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads finished.\n");
    return 0;
}
//Question 02:
#include <stdio.h>
#include <pthread.h>

void* printThreadID(void* arg) {
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu\n", tid);
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

    printf("All 5 threads have finished.\n");
    return 0;
}
//Question 03:
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* printNumbers(void* arg) {
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", i);
        sleep(1);  // Sleep for 1 second
    }
    return NULL;
}

int main() {
    pthread_t t;

    pthread_create(&t, NULL, printNumbers, NULL);
    pthread_join(t, NULL);

    printf("Number printing thread finished.\n");
    return 0;
}
//Question 04:
#include <stdio.h>
#include <pthread.h>

int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < 1000; i++) {
        counter++;
    }
    return NULL;
}

void* decrement(void* arg) {
    for (int i = 0; i < 1000; i++) {
        counter--;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, decrement, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", counter);
    return 0;
}
//Question 05:
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* square(void* arg) {
    int num = *(int*)arg;
    int* result = malloc(sizeof(int)); //Allocate memory on the heap to store an integer.result points to this allocated memory.
    *result = num * num;  //Store the result in the allocated memory.
	//function used by a thread to terminate itself and optionally return a value (retval) to any thread that joins it.
    pthread_exit(result); //Exit the thread and return the pointer result to the caller.
}

int main() {
    pthread_t t;
    int num = 5;

    pthread_create(&t, NULL, square, &num);

    int* res; //Declare a pointer res to receive the result
    pthread_join(t, (void**)&res);//pthread_join stores the thread's return value (a void*) in res.

    printf("Square of %d is %d\n", num, *res);
    free(res); //Free the memory allocated by the thread to avoid memory leaks.
    return 0;
}

