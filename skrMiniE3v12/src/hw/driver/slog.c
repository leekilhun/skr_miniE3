/*
 * slog.h
 *
 *  Created on: 2022. 3. 5.
 *      Author: gns2l
 */


#include "slog.h"
#include "uart.h"

#ifdef _USE_HW_SLOG


static uint8_t log_ch = LOG_CH;
static char print_buf[256];

#ifdef _USE_HW_RTOS
static osMutexId mutex_lock_log;
#endif


bool slogInit(void)
{
#ifdef _USE_HW_RTOS
  osMutexDef(mutex_lock_log);
  mutex_lock_log = osMutexCreate (osMutex(mutex_lock_log));
#endif

  return true;
}

void slogPrintf(const char *fmt, ...)
{
#ifdef _USE_HW_RTOS
  osMutexWait(mutex_lock_log, osWaitForever);
#endif

  va_list args;
  int len;

  va_start(args, fmt);
  len = vsnprintf(print_buf, 256, fmt, args);

  uartWrite(log_ch, (uint8_t *)print_buf, len);
  va_end(args);

#ifdef _USE_HW_RTOS
  osMutexRelease(mutex_lock_log);
#endif
}



#endif
