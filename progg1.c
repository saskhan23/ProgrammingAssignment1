// Safwat Khan
// 113551208

#include <stdio.h>

#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/shm.h>

#include <stdlib.h>

#include <unistd.h>

#include <errno.h>

// Shared Memory

typedef struct

{

    int value;

} shared_mem;

shared_mem *total;

// /* Following function can increase 
// the value of the shared variable total*/

void process1();

void process2();

void process3();

void process4();

int main()

{

    int shmid, pid1, pid2, pid3, pid4;

    int ID;

    int status;

    key_t ShmKEY;

    char *shmadd;

    shmadd = (char *)0;

    ShmKEY = ftok(".", 'x');

/* Create a shared memory segment to connect to*/

    if ((shmid = shmget(ShmKEY, sizeof(int), IPC_CREAT | 0666)) < 0)

    {

        perror("shmget");

        exit(1);

    }

    if ((total = (shared_mem *)shmat(shmid, shmadd, 0)) == (shared_mem *)-1)

    {

        perror("shmat");

        exit(0);

    }

// Set shared memory to 0

total->value = 0;

/* Create 4 processes */

    if ((pid1 = fork()) == 0)

    process1();

    if ((pid1 != 0) && (pid2 = fork()) == 0)

    process2();

    if ((pid1 != 0) && (pid2 != 0) && (pid3 = fork()) == 0)

    process3();

    if ((pid1 != 0) && (pid2 != 0) && (pid3 = fork()) == 0)

    process3();

    if ((pid1 != 0) && (pid2 != 0) && (pid3 != 0) && (pid4 = fork()) == 0)

    process4();

/* Child processes finish while parents wait*/

    waitpid(pid1, status, 0);

    waitpid(pid2, status, 0);

    waitpid(pid3, status, 0);

    waitpid(pid4, status, 0);

if ((pid1 != 0) && (pid2 != 0) && (pid3 != 0) && (pid4 != 0))

{

    waitpid(pid1);

    printf(" Child with ID %d has just exited. ", pid1);

    waitpid(pid2);

    printf(" Child with ID %d has just exited. ", pid2);

    waitpid(pid3);

    printf(" Child with ID %d has just exited. ", pid3);

    waitpid(pid4);

    printf(" Child with ID %d has just exited. ", pid4);

// detaching shared memory

if (shmdt(total) == -1) {

    perror("shmdt");

    exit(-1);

}

// Removing shared memory

shmctl(shmid, IPC_RMID, NULL);

printf("End of Program ");

}

}

/*Follwing function will increase the value of shared variable "total"

by one with target of 100000*/

void process1()

{

int p = 0;

while (p < 100000)

{

total->value = total->value + 1;

p++;

}

printf(" From process1 total = %dn", total->value);

}

/*Following function will increase the value of shared memory variable "total"

 by one with a target 200000*/

void process2()

{

    int p = 0;

    while (p < 200000)

    {

total->value = total->value + 1;

p++;

}

printf(" From process1 total = %dn", total->value);

}

/* Following function increases the value of shared memory variable "total"

 by one with a target 300000*/

void process3()

{

int p = 0;

while (p < 300000)

{

total->value = total->value + 1;

p++;

}

printf(" From process1 total = %dn", total->value);

}

/*Following function increases the vakue of shared memory variable "total"

by one with a target 500000.*/

void process4()

  {

    int p = 0;

    while (p < 500000)

  {

        total->value = total->value + 1;

        p++;

    }

    printf(" From process4 total = %dn", total->value);

}
