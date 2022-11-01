# Producer-Consumer
Producer-Consumer Lab OS Fall 2022
Nathaniel Capeta

This is a program for a Producer & Consumer using shared memory, pthread, & semaphores.
Written in C in files producer.c & consumer.c
Compiled as follows:
  $ gcc producer.c -pthread -lrt -o producer
  $ gcc consumer.c -pthread -lrt -o consumer
  $ ./producer & ./consumer &

