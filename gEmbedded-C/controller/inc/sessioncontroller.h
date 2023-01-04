//
// Created by sondahi on 04.01.23.
//

#ifndef GEMBEDDED_C_SESSIONCONTROLLER_H
#define GEMBEDDED_C_SESSIONCONTROLLER_H

#include "session.h"

typedef enum {
    SESSION_SUCCESS = 0,
    SESSION_PASSIVE_ERROR = 1,
    SESSION_LOCK_ERROR =2,
    SESSION_UNLOCK_ERROR=3
} SESSION_STATUS;

SESSION_STATUS lockConfig(struct session * session);
SESSION_STATUS unlockConfig (struct session * session);
SESSION_STATUS lockIO(struct session * session);
SESSION_STATUS unlockIO (struct session * session);

#endif //GEMBEDDED_C_SESSIONCONTROLLER_H
