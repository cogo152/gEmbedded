#include "system.h"
#include "exception.h"
#include "process.h"

void configureSystem(void ){
    configureExceptions();
    configureProcessContext();
}

void startTimer(void ){
    if(!ST->STK_CTRL.enable_rw){
        ST->STK_CTRL.enable_rw = HIGH;
    }
}