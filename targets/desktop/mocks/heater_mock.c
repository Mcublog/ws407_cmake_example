/**
 * @file heater_mock.c
 * @author Viacheslav (Viacheslav@mcublog.ru)
 * @brief Mocking
 * @version 0.1
 * @date 2022-09-25
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "heater/heater.h"
#include "io_mock.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME heater_mock
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

//>>---------------------- Local variables
#define HEATER_FILE_NAME "/tmp/heater"
//<<----------------------

//>>---------------------- Public
/**
 * @brief
 *
 */
void heater_init(void)
{
    LOG_INFO("heater init");
    if (iomock_file_is_exist(HEATER_FILE_NAME) == false)
        iomock_write_bool(HEATER_FILE_NAME, false);
}

/**
 * @brief
 *
 * @param on
 */
void heater_switch(bool on)
{
    if (on)
        LOG_INFO("heater: switch ON");
    else
        LOG_INFO("heater: switch OFF");
    iomock_write_bool(HEATER_FILE_NAME, on);
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool heater_is_on(void)
{
    bool result = iomock_read_bool(HEATER_FILE_NAME);
    LOG_INFO("get state: %d", result);
    return result;
}
//<<----------------------
