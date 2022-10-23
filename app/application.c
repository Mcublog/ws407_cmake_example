#include "application.h"

#include <stdbool.h>
#include <string.h>


#include "version.h"
// #include "usbd_cdc_if.h"
#if defined(CORE407)
#include "core407.hpp"
Core407 sys = Core407();
#elif defined(GREEN_PILL)
#include "green_pill.hpp"
GreenPill sys = GreenPill();
#else
#include "system.hpp"
System sys = System();
#endif
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