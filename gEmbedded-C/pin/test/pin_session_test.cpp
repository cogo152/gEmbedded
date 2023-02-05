//
// Created by sondahi on 04.02.23.
//

#include "gtest/gtest.h"

extern "C" {
#include "pin_session.h"
}

#define LOCKER_SLEEP_IN_MILSEC (200)

static volatile int configValue = 0;
static volatile int sessionValue = 0;


static void changeConfigValue() {

    lockPinConfigSession();
    configValue = 1;
    unlockPinConfigSession();

}

static void changeSessionValue(pin_t *const pin) {

    lockPinIOSession(pin);
    sessionValue = 1;
    unlockPinIOSession(pin);

}

TEST(PinSessionTest, testLockUnlockConfigSession) {

    int status;

    status = lockPinConfigSession();
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);
    std::thread configValueChanger(changeConfigValue);
    std::this_thread::sleep_for(std::chrono::milliseconds(LOCKER_SLEEP_IN_MILSEC));
    ASSERT_EQ(configValue, 0);

    status = unlockPinConfigSession();
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);
    configValueChanger.join();
    ASSERT_EQ(configValue, 1);

}

TEST(PinSessionTest, testInitLockUnlockDestroyIOSession) {

    int status;
    pin_t pin;

    status = initPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);

    status = lockPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);
    std::thread sessionValueChanger(changeSessionValue, &pin);
    std::this_thread::sleep_for(std::chrono::milliseconds(LOCKER_SLEEP_IN_MILSEC));
    ASSERT_EQ(sessionValue, 0);

    status = unlockPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);
    sessionValueChanger.join();
    ASSERT_EQ(sessionValue, 1);

    status = destroyPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_NO_ERROR);

    status = lockPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_LOCK_ERROR);

    status = unlockPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_EXCEPTION_UNLOCK_ERROR);

}