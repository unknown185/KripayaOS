#include <Firmware/Timer.h>


uint32_t tick = 0;

static void TimerCallback(registers_t *regs)
{
    tick++;
    print("Tick: ");

    char tick_ascii[256];
    IntToChar(tick, tick_ascii);
    print(tick_ascii);
    newLine();
}

void InitTimer(uint32_t freq)
{
    /* Install the function we just wrote */
    RegisterInterruptHandler(IRQ0, TimerCallback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);
    /* Send the command */
    Port(0x43).write(0x36); /* Command port */
    Port(0x40).write(low);
    Port(0x40).write(high);
}