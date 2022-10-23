/**
 * @file level_mock.c
 * @author Viacheslav (Viacheslav@mcublog.ru)
 * @brief Mock for level_sensor
 * @version 0.1
 * @date 2022-09-25
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include <pthread.h>

#include "level/level.h"
#include "utils/delay.h"
#include "io_mock.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME level_mock
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Local variables
#define LEVEL_SENSOR_FILE "/tmp/level_sensor"
#define LEVEL_CLAMP_FILE "/tmp/level_clamp"

static pthread_t _edge_detection_thread_id;

static iomock_handlers_t _handlers = {.irg_handler = NULL, .state_reading = level_check};
//<<----------------------

//>>---------------------- Public
/**
 * @brief Init level_sensor
 *
 */
void level_init(app_t_gpio_irq_handler_t irg_handler)
{
    LOG_INFO("level_sensor init");
    if (iomock_file_is_exist(LEVEL_SENSOR_FILE) == false)
        iomock_write_bool(LEVEL_SENSOR_FILE, false);
    if (iomock_file_is_exist(LEVEL_CLAMP_FILE) == false)
        iomock_write_bool(LEVEL_CLAMP_FILE, false);
    _handlers.irg_handler = (iomock_irq_handler_t)irg_handler;
    pthread_create(&_edge_detection_thread_id, NULL, iomock_edge_detecting,
                   (void *)&_handlers);
}

/**
 * @brief Checking level sensor
 *
 * @return true
 * @return false
 */
bool level_check(void)
{
    bool result = iomock_read_bool(LEVEL_SENSOR_FILE);
    LOG_DEBUG("level is: %d", result);
    return result;
}

/**
 * @brief
 *
 * @param on
 */
void level_clamp_switch(bool on)
{
    LOG_INFO("level clamp switch: %d", on);
    iomock_write_bool(LEVEL_CLAMP_FILE, on);
}

/**
 * @brief
 *
 * @return app_t_gpio_irq_handler_t
 */
app_t_gpio_irq_handler_t level_get_irq_handler(void)
{
    return (app_t_gpio_irq_handler_t)_handlers.irg_handler;
}
//<<----------------------