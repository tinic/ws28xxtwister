#include "led_data_processor.h"

LedDataProcessor  &LedDataProcessor::instance() {
    static LedDataProcessor ledDataProcessor;
    if (!ledDataProcessor.initialized) {
        ledDataProcessor.initialized = true;
        ledDataProcessor.init();
    }
    return ledDataProcessor;
}

void LedDataProcessor::init() {
}

void LedDataProcessor::process(uint32_t data) {
}
