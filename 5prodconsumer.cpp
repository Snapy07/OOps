#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>

using namespace std;

// Shared buffer, mutex, and condition variables
vector<int> buffer;
pthread_mutex_t mtx;  // Mutex for synchronizing access to buffer
pthread_cond_t cv_producer, cv_consumer;  // Condition variables for producer and consumer

// Helper function to print the current state of the buffer
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

// Producer function
void* producer(void* arg) {
    int* params = (int*)arg;  // Retrieve producer parameters
    int num_operations = params[0];  // Number of items to produce
    int buffer_size = params[1];  // Maximum buffer capacity

    for (int i = 0; i < num_operations; ++i) {
        pthread_mutex_lock(&mtx);  // Lock mutex to enter critical section

        // Wait if buffer is full
        cout << "Producer waiting to produce item " << i + 1 << endl;
        while (buffer.size() >= buffer_size) {
            pthread_cond_wait(&cv_producer, &mtx);  // Wait for buffer space
        }
        cout << "Producer entered critical section to produce item " << i + 1 << endl;

        // Produce an item and add it to the buffer
        int item = i + 1;
        buffer.push_back(item);
        cout << "Producer produced item " << item << " at position " << buffer.size() - 1 << endl;

        // Print the current state of the buffer
        print_buffer();

        // Notify consumer that there's an item to consume
        pthread_cond_signal(&cv_consumer);

        cout << "Producer exited critical section after producing item " << item << endl;

        pthread_mutex_unlock(&mtx);  // Unlock mutex after producing

        // Simulate production delay
        usleep(100000);  // 100 ms delay
    }

    return nullptr;
}

// Consumer function
void* consumer(void* arg) {
    int* num_operations = (int*)arg;  // Retrieve number of items to consume
    int operations = *num_operations;

    for (int i = 0; i < operations; ++i) {
        pthread_mutex_lock(&mtx);  // Lock mutex to enter critical section

        // Wait if buffer is empty
        cout << "Consumer waiting to consume" << endl;
        while (buffer.empty()) {
            pthread_cond_wait(&cv_consumer, &mtx);  // Wait for items in buffer
        }
        cout << "Consumer entered critical section to consume" << endl;

        // Consume the first item in the buffer
        int item = buffer.front();
        buffer.erase(buffer.begin());
        cout << "Consumer consumed item " << item << endl;

        // Print the current state of the buffer
        print_buffer();

        // Notify producer that there's space in the buffer
        pthread_cond_signal(&cv_producer);

        cout << "Consumer exited critical section after consuming item " << item << endl;

        pthread_mutex_unlock(&mtx);  // Unlock mutex after consuming

        // Simulate consumption delay
        usleep(200000);  // 200 ms delay
    }

    return nullptr;
}

int main() {
    int num_producer_ops, num_consumer_ops, buffer_size;

    // Input for the number of operations and buffer size
    cout << "Enter number of producer operations: ";
    cin >> num_producer_ops;
    cout << "Enter number of consumer operations: ";
    cin >> num_consumer_ops;
    cout << "Enter buffer size: ";
    cin >> buffer_size;

    // Initialize mutex and condition variables
    pthread_mutex_init(&mtx, nullptr);
    pthread_cond_init(&cv_producer, nullptr);
    pthread_cond_init(&cv_consumer, nullptr);

    // Prepare parameters for the producer thread
    int producer_params[2] = {num_producer_ops, buffer_size};

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, nullptr, producer, (void*)producer_params);
    pthread_create(&consumer_thread, nullptr, consumer, (void*)&num_consumer_ops);

    // Wait for threads to finish execution
    pthread_join(producer_thread, nullptr);
    pthread_join(consumer_thread, nullptr);

    // Destroy mutex and condition variables after threads are done
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv_producer);
    pthread_cond_destroy(&cv_consumer);

    return 0;
}
