#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int N;  // Declare N globally so it's accessible in philosopher function
sem_t *forks;  // Declare forks globally

//sample input 
//5

void* philosopher(void* arg);
void start_philosophers();

int main() {
    start_philosophers();  // Start the philosophers' simulation
    return 0;
}

void* philosopher(void* arg) {
    int id = *((int*) arg);
    
    for (int i = 0; i < 3; i++) {
        printf("Philosopher %d is thinking.\n", id);
        usleep(100000);  // Thinking

        // Deadlock prevention: Odd philosophers pick up right fork first
        if (id % 2 == 0) {
            sem_wait(&forks[id]);  // Pick up left fork
            sem_wait(&forks[(id + 1) % N]);  // Pick up right fork
        } else {
            sem_wait(&forks[(id + 1) % N]);  // Pick up right fork
            sem_wait(&forks[id]);  // Pick up left fork
        }

        printf("Philosopher %d is eating.\n", id);
        usleep(100000);  // Eating

        // Put down forks
        sem_post(&forks[id]);  // Put down left fork
        sem_post(&forks[(id + 1) % N]);  // Put down right fork

        printf("Philosopher %d finished eating.\n", id);
        usleep(100000);  // Resting
    }

    return NULL;
}

void start_philosophers() {
    printf("Enter the number of philosophers: ");
    scanf("%d", &N); // Take user input for the number of philosophers

    forks = new sem_t[N]; // Dynamically allocate memory for forks

    pthread_t philosophers[N];
    int ids[N];

    // Initialize semaphores for each fork (each fork is initially available)
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;  // Assigning unique ID to each philosopher
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all philosopher threads to finish
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    delete[] forks;  // Free dynamically allocated memory for forks
}
