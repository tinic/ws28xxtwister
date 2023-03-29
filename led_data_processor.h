#ifndef _LED_DATA_PROCESSOR_H_
#define _LED_DATA_PROCESSOR_H_

#include <stdint.h>
#include <stdlib.h>

class LedDataProcessor {
public:
    static LedDataProcessor &instance();
    void process(uint32_t data);
private:
    void clearSwizzleBuffer();

    void init();
    bool initialized = false;

    // Track reset time
    uint64_t resetTime = 0;

    // Track data/LED count
    size_t dataN = 0;
    size_t dataCount = 0;

    // Skip pixels
    bool skipActive = false;
    size_t skipBytesN = 0;
    size_t skipBytesCounter = 0;

    // Swizzle pixels
    bool swizzleActive = false;
    size_t swizzlePage = 0;
    size_t swizzleIndex = 0;
    static constexpr size_t swizzleBufferN = 24;
    uint32_t swizzleBuffer[2][swizzleBufferN];
    uint8_t swizzleSelect[swizzleBufferN];
};

#endif //  #ifndef _LED_DATA_PROCESSOR_H_
