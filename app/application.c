#include "application.h"

#include <stdbool.h>
#include <string.h>


#include "version.h"
#include "utils/delay.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME app
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Local declarations

//<<----------------------

/**
 * @brief
 *
 */
void application(void)
{
    LOG_INFO("Version: %s", FW_VERSION);
    while (1)
    {
        delay_ms(1000);
        LOG_INFO("working...");
    }
}