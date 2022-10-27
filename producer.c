#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include<sys/shm.h>


int main(){
    //Hold where process is attached w/ shared memory
    void *shared_memory;
    int shmid;

    shmid = shmget((key_t)1122, 1024, 0666);
    shared_memory = shmat(shmid, NULL, 0);
}