#include <Firmware/Timer.h>
#include <Drivers/Display.h>
#include <Drivers/Port.h>
#include <Kernel/Common.h>
#include <Firmware/ISR.h>

uint32_t tick = 0;

static void timer_callback(registers_t *regs) {
    tick++;
    print("Tick: ");

    char tick_ascii[256];
    int_to_string(tick, tick_ascii);
    print(tick_ascii);
    newLine();
}

void init_timer(uint32_t freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    Port(0x43).write(0x36); /* Command port */
    Port(0x40).write(low);
    Port(0x40).write(high);
}