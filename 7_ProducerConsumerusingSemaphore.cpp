#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>

using namespace std;
//sample input
//5
//5
//3

vector<int> buffer;
sem_t empty_slots, full_slots;
sem_t mutex;

void print_buffer() {
    cout << "Buffer state: [";
    for (size_t i = 0; i < buffer.size(); ++i) {
        cout << buffer[i];
        if (i != buffer.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void* producer(void* arg) {
    int* params = (int*)arg;
    int num_operations = params[0];
    int buffer_size = params[1];

    for (int i = 0; i < num_operations; ++i) {
        // Wait for an empty slot
        sem_wait(&empty_slots);

        // Enter critical section
        sem_wait(&mutex);

        // Produce item
        int item = i + 1;
        buffer.push_back(item);
        cout << "Producer produced item " << item << " at position " << buffer.size() - 1 << endl;

        // Print current buffer state
        print_buffer();

        // Leave critical section
        sem_post(&mutex);

        // Notify consumer that there is an item to consume
        sem_post(&full_slots);

        // Simulate work delay
        usleep(100000);  // Simulate work
    }

    return nullptr;
}

void* consumer(void* arg) {
    int* num_operations_ptr = (int*)arg;  // Cast the void pointer to an int pointer
    int num_operations = *num_operations_ptr;  // Dereference to get the value

    for (int i = 0; i < num_operations; ++i) {
        // Wait for a full slot
        sem_wait(&full_slots);

        // Enter critical section
        sem_wait(&mutex);

        // Consume item
        int item = buffer.front();
        buffer.erase(buffer.begin());
        cout << "Consumer consumed item " << item << endl;

        // Print current buffer state
        print_buffer();

        // Leave critical section
        sem_post(&mutex);

        // Notify producer that there is an empty slot
        sem_post(&empty_slots);

        // Simulate work delay
        usleep(200000);  // Simulate work
    }

    return nullptr;
}

int main() {
    int num_producer_ops, num_consumer_ops, buffer_size;

    // Taking inputs for number of operations and buffer size
    cout << "Enter number of producer operations: "<< endl;
    cin >> num_producer_ops;
    cout << "Enter number of consumer operations: " << endl;
    cin >> num_consumer_ops;
    cout << "Enter buffer size: " << endl;
    cin >> buffer_size;

    // Initialize semaphores
    sem_init(&empty_slots, 0, buffer_size);  // Initially, the buffer has 'buffer_size' empty slots
    sem_init(&full_slots, 0, 0);  // No items in the buffer initially
    sem_init(&mutex, 0, 1);  // Mutex for mutual exclusion in the critical section

    // Prepare producer and consumer parameters
    int producer_params[2] = {num_producer_ops, buffer_size};

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, nullptr, producer, (void*)producer_params);

    // Pass a pointer to num_consumer_ops for the consumer thread
    pthread_create(&consumer_thread, nullptr, consumer, (void*)&num_consumer_ops);

    // Wait for threads to finish
    pthread_join(producer_thread, nullptr);
    pthread_join(consumer_thread, nullptr);

    // Destroy semaphores
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    sem_destroy(&mutex);

    return 0;
}
