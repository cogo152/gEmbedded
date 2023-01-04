//
// Created by sondahi on 04.01.23.
//

#include <pthread.h>

#include "sessioncontroller.h"

SESSION_STATUS lockConfig(struct session * session){

    if(session->configActive == FALSE){
        return SESSION_PASSIVE_ERROR;
    }

    const int mutexResult = pthread_mutex_lock(&session->configLock);
    if(mutexResult != 0){
        return SESSION_LOCK_ERROR;
    }

    return SESSION_SUCCESS;

}

SESSION_STATUS unlockConfig (struct session * session){

    const int mutexResult = pthread_mutex_unlock(&session->configLock);
    if(mutexResult != 0){
        return SESSION_UNLOCK_ERROR;
    }

    return SESSION_SUCCESS;

}


SESSION_STATUS lockIO(struct session * session){

    if(session->ioActive == FALSE){
        return SESSION_PASSIVE_ERROR;
    }

    const int mutexResult = pthread_mutex_lock(&session->ioLock);
    if(mutexResult != 0){
        return SESSION_LOCK_ERROR;
    }

    return SESSION_SUCCESS;

}

SESSION_STATUS unlockIO (struct session * session){

    const int mutexResult = pthread_mutex_unlock(&session->ioLock);
    if(mutexResult != 0){
        return SESSION_UNLOCK_ERROR;
    }

    return SESSION_SUCCESS;

}