#ifndef __KRIPAYAOS__TIMER_H__
#define __KRIPAYAOS__TIMER_H__

#include <Drivers/Display.h>
#include <Drivers/Port.h>
#include <Kernel/Common.h>
#include <Firmware/ISR.h>

void InitTimer(uint32_t freq);

#endif // __KRIPAYAOS__TIMER_H__