#include "core.h"
#include "system.h"
#include "memory.h"
#include "exception.h"
#include "process.h"

// dataCopy
int dataInt = 1;
char dataChar1 = 2;
short dataShort = 3;
char dataChar2 = 4;

// bssFill
int bssInt;
char bssChar1;
short bssShort;
char bssChar2;

static struct process_t process1;
static struct process_t process2;
static struct process_t process3;
static struct process_t process4;

extern void processHandler(void );

int volatile sharedData;
int volatile mainData;

void runner1(void *args){
    uint32_t *ptr = (uint32_t *)args;
    uint32_t localVar = *ptr;

    while (1){
        sharedData=localVar;
    }

}

void runner2(void *args){

    uint32_t *ptr = (uint32_t *)args;
    uint32_t localVar = *ptr;

    while (1){
        sharedData = *ptr;
    }

}

int arg1 = -10;
int arg2 = 10;

int a = 5;
int b = 10;
int c = 0;

void run2(void){
    
    c = a+b;

    while (1);
    

}

uint32_t functionTest[30];

__attribute__((naked)) void run(uint32_t address){

    __asm volatile("mov r1, r0");
    __asm volatile("bx r1");

}

int main(void ){

    //run2();

    functionTest[0]= 0xaf00b480;
    functionTest[1]= 0x681a4b03;
    functionTest[2]= 0x681b4b03;
    functionTest[3]= 0x4a034413;
    functionTest[4]= 0xe7fe6013;
    functionTest[5]= &a;
    functionTest[6]= &b;
    functionTest[7]= &c;

    uint32_t addres = (uint32_t) &functionTest;

    run(addres+1);

    while (1);    


/*
    
    createProcess (1024,&process1,&processHandler,20,&runner1,&arg1,1);

    createProcess (1024,&process2,&processHandler,20,&runner2,&arg2,1);

    //createProcess (&process3,runner1,1024);
    //createProcess (&process4,runner2,1024);

    while (1){sharedData=0;}
        sharedData++;
        */

}



