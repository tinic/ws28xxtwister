#include <stdio.h>
#include "pico/stdlib.h"
#include "ws28xx_decoder.h"
#include "ws28xx_decoder.pio.h"

int main() {
    setup_default_uart();
    printf("Hello, world!\n");

    WS28xxDecoder::instance();
    
    return 0;
}
