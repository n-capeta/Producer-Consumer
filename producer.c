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
    const char * name = "shared_memory";

    const char * sema1= "fill";
    const char * sema2= "avail";
    const char * sema3="mutex";


    //Open the shared mem
    shm_fd = shm_open(name, O_RDWR, 0666);

    //Map the shared map
    table = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    //Open semaphores
    fill = sem_open(sema1, O_CREAT,0666,0);
    avail = sem_open(sema2, O_CREAT, 0666, 3);
    mutex = sem_open(sema3,O_CREAT,0666,1);



    //Unlink & Close semaphores
    sem_close(fill);
    sem_close(avail);
    sem_close(mutex);
    sem_unlink(sema1);
    sem_unlink(sema2);
    sem_unlink(sema3);


    //Removing shared mem
    munmap(table, sizeof(int));
    close(shm_fd);
    shm_unlink(name);
    return 0;
}