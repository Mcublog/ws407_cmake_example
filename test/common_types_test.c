/**
 * @file app_test.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2022-10-27
 *
 * @copyright Viacheslav mcublog (c) 2022
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "common_type.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME common_types_test
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

int main()
{
    const char* edge_str = cm_irq_edge_stringify(APP_GPIO_IRQ_RISING);
    if (strncmp(edge_str, "APP_GPIO_IRQ_RISING", strlen("APP_GPIO_IRQ_RISING")) != 0)
    {
        LOG_ERROR("Stringify error");
        exit(1);
    }
    LOG_DEBUG("Test ok");
}
