Producer-Consumer Project
This is a simple producer-consumer project in C that demonstrates inter-process communication using shared memory and semaphores. In this project, a producer thread writes data into a shared buffer, and a consumer thread reads data from the same buffer.

Project Components
The project consists of the following files:

sharedmemory.h: This header file defines the necessary data structures, including semaphores, shared memory, and the shared buffer.

producer.c: This file contains the producer code, which creates a shared memory segment, initializes semaphores, and pushes data into the shared buffer.

consumer.c: This file contains the consumer code, which attaches to the same shared memory segment, consumes data from the shared buffer, and performs necessary synchronization with semaphores.

To compile and run the project, follow these steps:

Compile the producer and consumer programs separately:

Copy code
$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & 
$ ./consumer &


Execute the producer and consumer programs in separate terminal windows:
The producer will push data into the shared buffer, and the consumer will consume it. Both the producer and consumer will use semaphores to synchronize their actions.
