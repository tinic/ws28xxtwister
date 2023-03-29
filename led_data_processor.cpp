#include "led_data_processor.h"

#include <type_traits>
#include <utility>
#include <cstring>

#include <pico/stdlib.h>

#include "ws28xx_output.h"

namespace internal {
    template<class T, T... inds, class F>
    constexpr void loop(std::integer_sequence<T, inds...>, F&& f) {
        (f(std::integral_constant<T, inds>{}), ...);
    }

    template<class T, T count, class F>
    constexpr void loop(F&& f) {
        loop(std::make_integer_sequence<T, count>{}, std::forward<F>(f));
    }
};

LedDataProcessor  &LedDataProcessor::instance() {
    static LedDataProcessor ledDataProcessor;
    if (!ledDataProcessor.initialized) {
        ledDataProcessor.initialized = true;
        ledDataProcessor.init();
    }
    return ledDataProcessor;
}

void LedDataProcessor::init() {
    memset(swizzleBuffer, 0xff, sizeof(swizzleBuffer));
    swizzleIndex = 0;
    swizzlePage = 0;
}

void LedDataProcessor::process(uint32_t data) {

    if (data > 0xff) {
        resetTime = time_us_64();
        dataN = dataCount;
        dataCount = 0;
    } else {
        dataCount++;
    }

    if (skipActive) {
        if (data > 0xFF) {
            skipBytesCounter = 0;
        } else if (skipBytesCounter < skipBytesN) {
            return;
        }
    }

    if (swizzleActive)  {
        if (data > 0xff) {
            memset(swizzleBuffer, 0xff, sizeof(swizzleBuffer));
            swizzleIndex = 0;
            swizzlePage = 0;
        } else {
            swizzleBuffer[swizzlePage][swizzleSelect[swizzleIndex]] = data;
            data = swizzleBuffer[swizzlePage^1][swizzleIndex];
            swizzleIndex ++;
            if (swizzleIndex >= swizzleBufferN) {
                swizzlePage ^= 1;
                swizzleIndex = 0;
            }
        }
    }

    WS28xxOutput::instance().output(data);
}
