//
// Created by sondahi on 29.12.22.
//

#include "session.h"

SESSION_STATUS lockSession(struct session *const session) {

    if (session->status == FALSE) {
        return SESSION_ERROR;
    }

    const int lockResult = pthread_mutex_lock(&session->lock);
    if (lockResult != 0) {
        return SESSION_ERROR;
    } else {
        return SESSION_SUCCESS;
    }

}

SESSION_STATUS unlockSession(struct session *const session) {

    if (session->status == FALSE) {
        return SESSION_ERROR;
    }

    const int unlockResult = pthread_mutex_unlock(&session->lock);
    if (unlockResult != 0) {
        return SESSION_ERROR;
    } else {
        return SESSION_SUCCESS;
    }

}