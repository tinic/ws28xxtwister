#include <pico/stdlib.h>

#include "ws28xx_decoder.h"
#include "ws28xx_decoder.pio.h"
#include "led_data_processor.h"

void ws28xxx_decoder_isr() {
    if (pio_interrupt_get(WS28XX_DECODER_PIO, WS28XX_DECODER_PIO_IRQ_INDEX)) {
	    pio_interrupt_clear(WS28XX_DECODER_PIO, WS28XX_DECODER_PIO_IRQ_INDEX);
        LedDataProcessor::instance().process(ws28xx_decoder_get_value());
	}
}

WS28xxDecoder  &WS28xxDecoder ::instance() {
    static WS28xxDecoder ws28xxDecoder;
    if (!ws28xxDecoder.initialized) {
        ws28xxDecoder.initialized = true;
        ws28xxDecoder.init();
    }
    return ws28xxDecoder;
}

void WS28xxDecoder::init() {
    ws28xx_decoder_init();
}
