/**
 * @file time_syscall.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief
 * @version 0.1
 * @date 2023-02-15
 *
 * @copyright Viacheslav mcublog (c) 2023
 *
 */
#include <sys/times.h>
#include <time.h>
//>>---------------------- Log control
#define LOG_MODULE_NAME timesys
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (0)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

/**
 * @brief
 *
 * @param r
 * @param t
 * @return clock_t
 */
__attribute__((__used__))
clock_t
_times_r(struct _reent *r, struct tms *t)
{
    return 1000;
}

/**
 * @brief
 *
 * @param buf
 * @return clock_t
 */
__attribute__((__used__))
clock_t
_times(struct tms *buf)
{
    return 1000;
}

/**
 * @brief
 *
 * @param tv
 * @param tzvp
 * @return int
 */
int _gettimeofday(struct timeval *tv, void *tzvp)
{
    tv->tv_usec = 0;
    tv->tv_sec = 1676464882;
    return 0;
}