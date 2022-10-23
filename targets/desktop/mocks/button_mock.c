/**
 * @file button_mock.c
 * @author Viacheslav (Viacheslav@mcublog.ru)
 * @brief Mocking
 * @version 0.1
 * @date 2022-09-25
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include <pthread.h>

#include "button/button.h"
#include "utils/delay.h"
#include "io_mock.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME btn_mock
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Local variables
#define BUTTON_FILE "/tmp/button"
#define LED_OF_BUTTON "/tmp/led_button"

static pthread_t _edge_detection_thread_id;

static iomock_handlers_t button_handlers = {.irg_handler = NULL,
                                            .state_reading = button_get_state};
//<<----------------------

//>>---------------------- Local
//<<----------------------

//>>---------------------- Public
/**
 * @brief
 *
 */
void button_init(app_t_gpio_irq_handler_t irg_handler)
{
    LOG_INFO("button_init");
    if (iomock_file_is_exist(BUTTON_FILE) == false)
        iomock_write_bool(BUTTON_FILE, false);
    if (iomock_file_is_exist(LED_OF_BUTTON) == false)
        iomock_write_bool(LED_OF_BUTTON, false);
    button_handlers.irg_handler = (iomock_irq_handler_t)irg_handler;
    pthread_create(&_edge_detection_thread_id, NULL, iomock_edge_detecting,
                   (void *)&button_handlers);
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool button_get_state(void)
{
    bool result = iomock_read_bool(BUTTON_FILE);
    LOG_DEBUG("button_get_state: %d", result);
    return result;
}

/**
 * @brief
 *
 * @param on
 */
void button_led_on(bool on)
{
    LOG_INFO("set button_led: %d", on);
    iomock_write_bool(LED_OF_BUTTON, on);
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool button_led_is_on(void)
{
    bool result = iomock_read_bool(LED_OF_BUTTON);
    LOG_DEBUG("get button_led: %d", result);
    return result;
}

/**
 * @brief Return pointer to irq handler function
 *
 * @return app_t_gpio_irq_handler_t
 */
app_t_gpio_irq_handler_t button_get_irq_handler(void)
{
    return (app_t_gpio_irq_handler_t)button_handlers.irg_handler;
}
//<<----------------------