#ifndef _LED_DATA_PROCESSOR_H_
#define _LED_DATA_PROCESSOR_H_

#include <cstdint>
#include <cstdlib>
#include <array>

#include "ws28xx_output.h"

class LedDataProcessor {
public:
    LedDataProcessor():ws29xxOutput(WS28xxOutput::instance()) {};

    static LedDataProcessor &instance();

    void processRGB8(uint32_t pixel);
    void processRGBA8(uint32_t pixel);
    void processRGB16(uint64_t pixel);
    void processRGBA16(uint64_t pixel);

    void endOfData();

private:
    WS28xxOutput &ws29xxOutput;

    void init();
    bool initialized = false;

    // Track reset time
    uint64_t resetTime = 0;

    // Track data/LED count
    size_t dataN = 0;
    size_t dataC = 0;

};

#endif //  #ifndef _LED_DATA_PROCESSOR_H_
