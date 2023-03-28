#include "pico/stdlib.h"
#include "ws28xx_decoder.h"

#include "ws28xx_decoder.pio.h"

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
