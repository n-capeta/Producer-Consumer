#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>

int main(){
    int shm_fd;
    int * table;
    const char * name = "shared_memory";

    const char * sema1= "fill";
    const char * sema2= "avail";
    const char * sema3= "mutex";
    sem_t * fill, * available, * mutex;



    //Open the shared mem
    shm_fd = shm_open(name, O_RDWR, 0666);

    //Map the shared map
    table = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    //Open semaphores
    fill = sem_open(sema1, O_CREAT,0666,0);
    available = sem_open(sema2, O_CREAT, 0666, 3);
    mutex = sem_open(sema3,O_CREAT,0666,1);

    //Not sure if loop is the solution here. Need to do more learning about pthreads then circle back
    int loop = 2; // Size based off project requirement

    while(loop--){
        sem_wait(fill);
        sleep(rand()%2+1);
        sem_wait(mutex);
        (* table)--;
        sem_post(mutex);
        printf("Consumer: I am consuming\n");
        sem_post(available);
    }



    //Unlink & Close semaphores
    sem_close(fill);
    sem_close(available);
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