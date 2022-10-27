#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

int main(){
    int shm_fd;
    int * table;

    //Create the shared memory store in description
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666)

    ftruncate(shm_fd, sizeof(int));

    //Map the shared memory to my function
    table = mmap(0, sizeof(int), PROT_READ | PROD_WRITE, MAP_SHARED, shm_fd, 0);
}