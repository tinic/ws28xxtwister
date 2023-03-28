#include <stdio.h>
#include "pico/stdlib.h"
#include "ws28xx_decoder.h"
#include "ws28xx_decoder.pio.h"
#include "processor.h"

static NullProcessor first;
static SkipperProcessor skipper;
static SwizzleProcessor<3> rgb8Swizzle;
static SwizzleProcessor<4> rgba8Swizzle;
static SwizzleProcessor<6> rgb16Swizzle;
static SwizzleProcessor<8> rgba16Swizzle;
static OutProcessor out;

void ws28xxx_decoder_isr() {
    if (pio_interrupt_get(WS28XX_PIO, WS28XX_PIO_IRQ_INDEX)) {
	    pio_interrupt_clear(WS28XX_PIO, WS28XX_PIO_IRQ_INDEX);
        first.process(ws28xx_get_value());
	}
}

int main() {
    setup_default_uart();
    printf("Hello, world!\n");

    WS28xxDecoder::instance();

    first.setNext(skipper);

    skipper.setSkipN(3);
    skipper.setNext(rgb8Swizzle);

    rgb8Swizzle.setSwizzle((2<<0)|(1<<4)|(0<<8));
    rgb8Swizzle.setNext(out);

    return 0;
}

