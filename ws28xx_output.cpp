#include "ws28xx_output.h"
#include "ws28xx_output.pio.h"

WS28xxOutput  &WS28xxOutput ::instance() {
    static WS28xxOutput ws28xxOutput;
    if (!ws28xxOutput.initialized) {
        ws28xxOutput.initialized = true;
        ws28xxOutput.init();
    }
    return ws28xxOutput;
}

void WS28xxOutput::init() {
    update();
}

void WS28xxOutput::update() {
    size_t bits = 24;
    switch(ledDataType) {
        default:
        case WS28xxOutput::rgb8: {
            bits = 24;
            rgb8Func = &WS28xxOutput::outputRGB8toRGB8;
            rgba8Func = &WS28xxOutput::outputRGBA8toRGB8;
            rgb16Func = &WS28xxOutput::outputRGB16toRGB8;
            rgba16Func = &WS28xxOutput::outputRGBA16toRGB8;
        } break;
        case WS28xxOutput::rgba8: {
            bits = 32;
            rgb8Func = &WS28xxOutput::outputRGB8toRGBA8;
            rgba8Func = &WS28xxOutput::outputRGBA8toRGBA8;
            rgb16Func = &WS28xxOutput::outputRGB16toRGBA8;
            rgba16Func = &WS28xxOutput::outputRGBA16toRGBA8;
        } break;
        case WS28xxOutput::rgb16: {
            bits = 24;
            rgb8Func = &WS28xxOutput::outputRGB8toRGB16;
            rgba8Func = &WS28xxOutput::outputRGBA8toRGB16;
            rgb16Func = &WS28xxOutput::outputRGB16toRGB16;
            rgba16Func = &WS28xxOutput::outputRGBA16toRGB16;
        } break;
        case WS28xxOutput::rgba16: {
            bits = 32;
            rgb8Func = &WS28xxOutput::outputRGB8toRGBA16;
            rgba8Func = &WS28xxOutput::outputRGBA8toRGBA16;
            rgb16Func = &WS28xxOutput::outputRGB16toRGBA16;
            rgba16Func = &WS28xxOutput::outputRGBA16toRGBA16;
        } break;
    }
    ws28xx_output_init(bits);
}

void WS28xxOutput::outputRGB8toRGB8(uint32_t data) {
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, data << 8);
}

void WS28xxOutput::outputRGB8toRGBA8(uint32_t data) {
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, data << 8);
}

void WS28xxOutput::outputRGB8toRGB16(uint32_t data) {
    uint32_t dataHi = (((data>>24)&0xFF)<<24) | (((data>>24)&0xFF)<<16) | (((data>>16)&0xFF)<< 8);
    uint32_t dataLo = (((data>>16)&0xFF)<<24) | (((data>> 8)&0xFF)<<16) | (((data>> 8)&0xFF)<< 8);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, dataHi);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, dataLo);
}

void WS28xxOutput::outputRGB8toRGBA16(uint32_t data) {
    uint32_t dataHi = (((data>>24)&0xFF)<<24) | (((data>>24)&0xFF)<<16)| (((data>>16)&0xFF)<< 8) | (((data>>16)&0xFF));
    uint32_t dataLo = (((data>> 8)&0xFF)<<24) | (((data>> 8)&0xFF)<<16)| (((data>> 0)&0xFF)<< 8) | (((data>> 0)&0xFF));
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, dataHi);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, dataLo);
}

void WS28xxOutput::outputRGBA8toRGB8(uint32_t data) {
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, data & 0xFFFFFF00);
}

void WS28xxOutput::outputRGBA8toRGBA8(uint32_t data) {
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, data);
}

void WS28xxOutput::outputRGBA8toRGB16(uint32_t data) {
    uint32_t dataHi = (((data>>24)&0xFF)<<24) | (((data>>24)&0xFF)<<16) | (((data>>16)&0xFF)<< 8);
    uint32_t dataLo = (((data>>16)&0xFF)<<24) | (((data>> 8)&0xFF)<<16) | (((data>> 8)&0xFF)<< 8);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, dataHi);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, dataLo);
}

void WS28xxOutput::outputRGBA8toRGBA16(uint32_t data) {
    uint32_t dataHi = (((data>>24)&0xFF)<<24) | (((data>>24)&0xFF)<<16)| (((data>>16)&0xFF)<< 8) | (((data>>16)&0xFF));
    uint32_t dataLo = (((data>> 8)&0xFF)<<24) | (((data>> 8)&0xFF)<<16)| (((data>> 0)&0xFF)<< 8) | (((data>> 0)&0xFF));
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, dataHi);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, dataLo);
}

void WS28xxOutput::outputRGB16toRGB8(uint64_t data) {
    data = (((data>>56)&0xFF)<<24) | (((data>>40)&0xFF)<<16) | (((data>>24)&0xFF)<< 8)| (((data>> 8)&0xFF)<< 0);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t(data));
}

void WS28xxOutput::outputRGB16toRGBA8(uint64_t data) {
    data = (((data>>56)&0xFF)<<24) | (((data>>40)&0xFF)<<16) | (((data>>24)&0xFF)<< 8)| (((data>> 8)&0xFF)<< 0);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t(data));
}

void WS28xxOutput::outputRGB16toRGB16(uint64_t data) {
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t((data>>40)&0xFFFFFF)<<8);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t((data>>16)&0xFFFFFF)<<8);
}

void WS28xxOutput::outputRGB16toRGBA16(uint64_t data) {
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t((data>>32)&0xFFFFFFFF));
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t((data>> 0)&0xFFFFFFFF));
}

void WS28xxOutput::outputRGBA16toRGB8(uint64_t data) {
    data = (((data>>56)&0xFF)<<24) | (((data>>40)&0xFF)<<16) | (((data>>24)&0xFF)<< 8)| (((data>> 8)&0xFF)<< 0);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t(data));
}

void WS28xxOutput::outputRGBA16toRGBA8(uint64_t data) {
    data = (((data>>56)&0xFF)<<24) | (((data>>40)&0xFF)<<16) | (((data>>24)&0xFF)<< 8)| (((data>> 8)&0xFF)<< 0);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t(data));
}

void WS28xxOutput::outputRGBA16toRGB16(uint64_t data) {
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t((data>>40)&0xFFFFFF)<<8);
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t((data>>16)&0xFFFFFF)<<8);
}

void WS28xxOutput::outputRGBA16toRGBA16(uint64_t data) {
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t((data>>32)&0xFFFFFFFF));
    pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, uint32_t((data>> 0)&0xFFFFFFFF));
}
