#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/stdio_uart.h>

#include "ws28xx_decoder.h"
#include "ws28xx_decoder.pio.h"

int main() {
    stdout_uart_init();
    printf("WS28xxTwister: Hello!\n");

    set_sys_clock_khz(200000, true);

    WS28xxDecoder::instance();

    return 0;
}
