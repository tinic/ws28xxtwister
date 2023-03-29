#include <pico/stdlib.h>

#include "ws28xx_decoder.h"
#include "ws28xx_decoder.pio.h"
#include "led_data_processor.h"

static WS28xxDecoder ws28xxDecoder;

void ws28xxx_decoder_isr() {
    if (pio_interrupt_get(WS28XX_DECODER_PIO, WS28XX_DECODER_PIO_IRQ_INDEX)) {
        pio_interrupt_clear(WS28XX_DECODER_PIO, WS28XX_DECODER_PIO_IRQ_INDEX);
        ws28xxDecoder.process(ws28xx_decoder_get_value());
    }
}

WS28xxDecoder &WS28xxDecoder::instance() {
    if (!ws28xxDecoder.initialized) {
        ws28xxDecoder.initialized = true;
        ws28xxDecoder.init();
    }
    return ws28xxDecoder;
}

void WS28xxDecoder::process(uint32_t data) {
    if (data == END_OF_DATA) {
        ledDataProcessor.endOfData();
        compIdx = 0;
        pixel32 = 0;
        pixel64 = 0;
        return;
    }
    (*this.*decoderFunc)(data);
}

void WS28xxDecoder::rgb8Decode(uint32_t data) {
    pixel32 <<= 8;
    pixel32 |= data >> 24;
    compIdx++;
    if (compIdx > 3) {
        ledDataProcessor.processRGB8(pixel32);
        compIdx = 0;
        pixel32 = 0;
    }
}

void WS28xxDecoder::rgba8Decode(uint32_t data) {
    pixel32 <<= 8;
    pixel32 |= data >> 24;
    compIdx++;
    if (compIdx > 4) {
        ledDataProcessor.processRGBA8(pixel32);
        compIdx = 0;
        pixel32 = 0;
    }
}

void WS28xxDecoder::rgb16Decode(uint32_t data) {
    pixel64 <<= 16;
    pixel64 |= data >> 16;
    compIdx++;
    if (compIdx > 3) {
        ledDataProcessor.processRGB16(pixel64);
        compIdx = 0;
        pixel64 = 0;
    }
}

void WS28xxDecoder::rgba16Decode(uint32_t data) {
    pixel64 <<= 16;
    pixel64 |= data >> 16;
    compIdx++;
    if (compIdx > 4) {
        ledDataProcessor.processRGBA16(pixel64);
        compIdx = 0;
        pixel64 = 0;
    }
}

void WS28xxDecoder::init() {
    ws28xx_decoder_init();
    update();
}

void WS28xxDecoder::update() {
    uint32_t bitsPerComponent = 8;
    switch (ledDataType) {
        case LEDDataType::rgb8: {
            decoderFunc = &WS28xxDecoder::rgb8Decode;
            bitsPerComponent = 8;
        } break;
        case LEDDataType::rgba8: {
            decoderFunc = &WS28xxDecoder::rgba8Decode;
            bitsPerComponent = 8;
        } break;
        case LEDDataType::rgb16: {
            decoderFunc = &WS28xxDecoder::rgb16Decode;
            bitsPerComponent = 16;
        } break;
        case LEDDataType::rgba16: {
            decoderFunc = &WS28xxDecoder::rgba16Decode;
            bitsPerComponent = 16;
        } break;
    }
	pio_sm_exec(WS28XX_DECODER_PIO, WS28XX_DECODER_PIO_SM, pio_encode_set(pio_x, bitsPerComponent-1));
}
