//
// Created by sondahi on 04.02.23.
//

#include "gtest/gtest.h"

extern "C" {
#include "pin.h"
#include "pin_session.h"
}

#define LOCKER_SLEEP_IN_MILSEC (200)

static volatile int configValue = 0;
static volatile int sessionValue = 0;


static void changeConfigValue() {

    lockConfig();
    configValue = 1;
    unlockConfig();

}

static void changeSessionValue(pin_t *const pin) {

    lockSession(pin);
    sessionValue = 1;
    unlockSession(pin);

}

TEST(PinSessionTest, testConfigLockUnlock) {

    int status;

    status = lockConfig();
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);
    std::thread configValueChanger(changeConfigValue);
    std::this_thread::sleep_for(std::chrono::milliseconds(LOCKER_SLEEP_IN_MILSEC));
    ASSERT_EQ(configValue, 0);

    status = unlockConfig();
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);
    configValueChanger.join();
    ASSERT_EQ(configValue, 1);

}

TEST(PinSessionTest, testInitLockUnlockDestroySession) {

    int status;
    pin_t pin;

    status = initSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);

    status = lockSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);
    std::thread sessionValueChanger(changeSessionValue, &pin);
    std::this_thread::sleep_for(std::chrono::milliseconds(LOCKER_SLEEP_IN_MILSEC));
    ASSERT_EQ(sessionValue, 0);

    status = unlockSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);
    sessionValueChanger.join();
    ASSERT_EQ(sessionValue, 1);

    status = destroySession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);

    status = lockSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_LOCK_ERROR);

    status = unlockSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_UNLOCK_ERROR);

}