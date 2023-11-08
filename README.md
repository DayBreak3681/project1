# project1
In this code, we create the producer/consumer problem using 5 elements to be produced and consumed using shared memory buffer. 


Compilation:

run using 2 separate terminals (for producer and consumer respectively):

Producer terminal compile:
$gcc producer.c -pthread -lrt -o producer
$ ./producer & 

Consumer terminal Compile:
$ gcc consumer.c -pthread -lrt -o consumer
./consumer &
