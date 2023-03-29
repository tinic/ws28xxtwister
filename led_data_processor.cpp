#include "led_data_processor.h"

#include <type_traits>
#include <utility>
#include <cstring>

#include <pico/stdlib.h>

#include "ws28xx_output.h"

LedDataProcessor &LedDataProcessor::instance() {
    static LedDataProcessor ledDataProcessor;
    if (!ledDataProcessor.initialized) {
        ledDataProcessor.initialized = true;
        ledDataProcessor.init();
    }
    return ledDataProcessor;
}

void LedDataProcessor::init() {
}

void LedDataProcessor::endOfData() {
    resetTime = time_us_64();
    dataN = dataC;
    dataC = 0;
}

void LedDataProcessor::processRGB8(uint32_t pixel) {

    // TODO

    dataC++;
    ws29xxOutput.outputRGB8(pixel);
}

void LedDataProcessor::processRGBA8(uint32_t pixel) {

    // TODO

    dataC++;
    ws29xxOutput.outputRGBA8(pixel);
}

void LedDataProcessor::processRGB16(uint64_t pixel) {

    // TODO

    dataC++;
    ws29xxOutput.outputRGB16(pixel);
}

void LedDataProcessor::processRGBA16(uint64_t pixel) {

    // TODO

    dataC++;
    ws29xxOutput.outputRGBA16(pixel);
}
