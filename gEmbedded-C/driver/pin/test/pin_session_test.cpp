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
    ASSERT_EQ(status, PIN_SESSION_ERROR_NO);
    std::thread configValueChanger(changeConfigValue);
    std::this_thread::sleep_for(std::chrono::milliseconds(LOCKER_SLEEP_IN_MILSEC));
    ASSERT_EQ(configValue, 0);

    status = unlockPinConfigSession();
    ASSERT_EQ(status, PIN_SESSION_ERROR_NO);
    configValueChanger.join();
    ASSERT_EQ(configValue, 1);

}

TEST(PinSessionTest, testInitLockUnlockDestroyIOSession) {

    int status;
    pin_t pin;

    status = initPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_ERROR_NO);

    status = lockPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_ERROR_NO);
    std::thread sessionValueChanger(changeSessionValue, &pin);
    std::this_thread::sleep_for(std::chrono::milliseconds(LOCKER_SLEEP_IN_MILSEC));
    ASSERT_EQ(sessionValue, 0);

    status = unlockPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_ERROR_NO);
    sessionValueChanger.join();
    ASSERT_EQ(sessionValue, 1);

    status = destroyPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_ERROR_NO);

    status = lockPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_ERROR_LOCK);

    status = unlockPinIOSession(&pin);
    ASSERT_EQ(status, PIN_SESSION_ERROR_UNLOCK);

}