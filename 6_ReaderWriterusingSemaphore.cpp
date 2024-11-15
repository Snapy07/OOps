#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

//sample input 
//3
//2
//2

// Semaphore to control access to the shared resource
sem_t resource_sem;  // Binary semaphore for controlling the resource
sem_t reader_sem;    // Semaphore for controlling reader access (limits concurrent readers)
int read_count = 0;  // Counter for active readers
int shared_data = 10; // Shared resource data initialized to 10

void* reader(void* arg) {
    int reader_id = *((int*)arg);

    // First, wait for the reader semaphore to control the number of concurrent readers
    sem_wait(&reader_sem);

    // Critical section for updating read_count
    read_count++;
    if (read_count == 1) {
        // First reader locks the resource (writer can't enter when the first reader is inside)
        sem_wait(&resource_sem);
    }
    sem_post(&reader_sem); // Release the reader semaphore

    // Reading the shared resource
    cout << "Reader " << reader_id << " is reading the resource. Data: " << shared_data << endl;
    sleep(2); // Simulate reading time

    // Critical section for updating read_count
    sem_wait(&reader_sem);
    read_count--;
    if (read_count == 0) {
        // Last reader releases the resource lock (allows writers to enter)
        sem_post(&resource_sem);
    }
    sem_post(&reader_sem); // Release the reader semaphore

    cout << "Reader " << reader_id << " is leaving the resource." << endl;

    pthread_exit(NULL);
}

void* writer(void* arg) {
    int writer_id = *((int*)arg);

    cout << "Writer " << writer_id << " is trying to access the resource..." << endl;

    // Wait for the resource semaphore to gain exclusive access to the resource
    sem_wait(&resource_sem);

    // Writing to the shared resource
    cout << "Writer " << writer_id << " is writing to the resource." << endl;
    shared_data += writer_id * 10;
    cout << "Writer " << writer_id << " has written new data: " << shared_data << endl;
    sleep(2); // Simulate writing time

    // Release the resource lock after writing
    sem_post(&resource_sem);
    cout << "Writer " << writer_id << " has finished writing and unlocked the resource." << endl;

    pthread_exit(NULL);
}

int main() {
    int num_readers, num_writers, max_concurrent_readers;

    // Take user input for the number of readers, writers, and max concurrent readers
    cout << "Enter the number of readers: " << endl;
    cin >> num_readers;
    cout << "Enter the number of writers: "  << endl;
    cin >> num_writers;
    cout << "Enter the maximum number of concurrent readers: "  << endl;
    cin >> max_concurrent_readers;

    // Initialize the semaphores
    sem_init(&resource_sem, 0, 1);  // Resource semaphore (initial value = 1, binary semaphore)
    sem_init(&reader_sem, 0, max_concurrent_readers);  // Reader semaphore with user-defined limit

    pthread_t readers[num_readers], writers[num_writers];
    int reader_ids[num_readers], writer_ids[num_writers];

    // Create reader threads
    for (int i = 0; i < num_readers; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, (void*)&reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, (void*)&writer_ids[i]);
    }

    // Join reader threads
    for (int i = 0; i < num_readers; ++i) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < num_writers; ++i) {
        pthread_join(writers[i], NULL);
    }

    // Destroy the semaphores
    sem_destroy(&resource_sem);
    sem_destroy(&reader_sem);

    return 0;
}
