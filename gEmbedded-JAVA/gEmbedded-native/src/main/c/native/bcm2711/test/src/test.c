#include "jniutiltest.h"
#include "mappertest.h"
#include "devicedrivertest.h"

int main (void) {

    if (CUE_SUCCESS != CU_initialize_registry ()) {
        return CU_get_error ();
    }

    JNIUTIL_TEST
    MAPPER_TEST
    DEVICEDRIVER_TEST

    CU_SuiteInfo suites[] = {
            //{"JniUtilTest", initJniUtilSuite, cleanupJniUtilSuite, NULL, NULL, jniUtilTests},
            //{"MapperTest", NULL, NULL, NULL, NULL, mapperTests},
            {"DeviceDriverTest", initDeviceDriverSuite, cleanupDeviceDriverSuite, NULL, NULL, deviceDriverTests},
            CU_SUITE_INFO_NULL};

    CU_ErrorCode cuStatus = CU_register_suites (suites);
    if (cuStatus != CUE_SUCCESS) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    CU_basic_set_mode (CU_BRM_VERBOSE);

    createJVM ();
    CU_basic_run_tests ();
    destroyJVM ();

    CU_cleanup_registry ();
    return CU_get_error ();

}