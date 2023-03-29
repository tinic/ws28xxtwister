#include "led_data_processor.h"

#include <type_traits>
#include <utility>
#include <cstring>

#include <pico/stdlib.h>

#include "ws28xx_output.h"

LedDataProcessor  &LedDataProcessor::instance() {
    static LedDataProcessor ledDataProcessor;
    if (!ledDataProcessor.initialized) {
        ledDataProcessor.initialized = true;
        ledDataProcessor.init();
    }
    return ledDataProcessor;
}

void LedDataProcessor::init() {

    // default swizzle is copy
    for (size_t c = 0; c < workBufferN; c++) {
        swizzleSelect[c] = c;
    }

    workBuffer[0].fill(END_OF_DATA);
    workBuffer[1].fill(END_OF_DATA);

    workBufferIndex = 0;
    workBufferPage = 0;
}

void LedDataProcessor::process(uint32_t data) {

    if (data == END_OF_DATA) {
        resetTime = time_us_64();
        dataN = dataCount;
        dataCount = 0;
    } else {
        dataCount++;
    }

    if (skipActive) {
        if (data == END_OF_DATA) {
            skipBytesCounter = 0;
        } else if (skipBytesCounter < skipBytesN) {
            return;
        }
    }

    auto process = [this] (std::array<uint32_t, workBufferN> &array) {
        switch (ledDataType) {
            case rgb8: {
            } break;
            case rgba8: {
            } break;
            case rgb16: {
            } break;
            case rgba16: {
            } break;
        }
    };

    // When we are at the end push out rest of data
    if (data == END_OF_DATA) {
        // Process front work buffer, even if incomplete
        process(workBuffer[workBufferPage]);
        // Enqueue all remaining data
        for (size_t c = workBufferIndex ; c < workBufferN; c++) {
            WS28xxOutput::instance().output(workBuffer[workBufferPage^1][c]);
        }
        for (size_t c = 0; c < workBufferIndex; c++) {
            WS28xxOutput::instance().output(workBuffer[workBufferPage][c]);
        }
        workBuffer[0].fill(END_OF_DATA);
        workBuffer[1].fill(END_OF_DATA);
        workBufferIndex = 0;
        workBufferPage = 0;
    } else {
        // Byte is in top of word
        data >>= 24;
        // Always appply swizzle when storing to front buffer
        workBuffer[workBufferPage][swizzleSelect[workBufferIndex]] = data;
        // Obtain in flight data from shadow buffer
        data = workBuffer[workBufferPage^1][workBufferIndex];
        workBufferIndex ++;
        if (workBufferIndex >= workBufferN) {
            // Process front buffer
            process(workBuffer[workBufferPage]);
            // Flip front to shadow work buffer
            workBufferPage ^= 1;
            workBufferIndex = 0;
        }
        WS28xxOutput::instance().output(data);
    }
}
