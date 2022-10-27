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

    //Open the shared mem
    shm_fd = shm_open(name, O_RDWR, 0666);

    //Map the shared map
    table = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

}