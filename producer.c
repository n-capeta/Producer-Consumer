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

    const char * sema1 = "fill";
    const char * sema2 = "available";
    const char * sema3 = "mutex";
    sem_t * fill, * available, * mutex;

    //Create the shared memory store in description
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, sizeof(2));

    //Map the shared memory to my function
    table = mmap(0, sizeof(2), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    //Creating semaphores
    //Consumer post filling the table
    fill = sem_open(sema1, O_CREAT, 0666, 0);

    //Producer post avail after grabbing from consumer
    available = sem_open(sema2, O_CREAT, 0666, 3);

    //Mutex for the mutal exclusion on the table
    mutex = sem_open(sema3, O_CREAT, 0666, 1);

    //Not sure if loop is the solution here. Need to do more learning about pthreads then circle back
    int loop = 5; // Loop to run a couple times

    printf("\n Producer: I have started producing. \n");
    while(loop--){
        sem_wait(available);
        sleep(rand()%2+1);
        sem_wait(mutex);
        (* table)++;
        sem_post(mutex);
        printf("Producer: Produced, there are %d produced now\n", * table);
        sem_post(fill);
    }

    printf("Producer: Time is up. I produced 2. %d are left.\n", * table);


    //Unlinking & Closing semaphores
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
