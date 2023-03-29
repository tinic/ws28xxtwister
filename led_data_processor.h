#ifndef _LED_DATA_PROCESSOR_H_
#define _LED_DATA_PROCESSOR_H_

#include <cstdint>
#include <cstdlib>
#include <array>

class LedDataProcessor {
public:
    LedDataProcessor():
        workBuffer(),
        swizzleSelect() {
    }
    static LedDataProcessor &instance();
    void process(uint32_t data);

    enum LedDataType {
        rgb8,
        rgba8,
        rgb16,
        rgba16
    } ledDataType = rgb8;

private:
    static constexpr uint32_t END_OF_DATA = 0xffffffff;

    void init();
    bool initialized = false;

    // Track reset time
    uint64_t resetTime = 0;

    // Track data/LED count
    size_t dataN = 0;
    size_t dataCount = 0;

    // Intermediate work buffer
    static constexpr size_t workBufferN = 24; // LCM of ledDataType
    std::array<std::array<uint32_t, workBufferN>, 2> workBuffer;
    size_t workBufferPage = 0;
    size_t workBufferIndex = 0;

    // Skip pixels
    bool skipActive = false;
    size_t skipBytesN = 0;
    size_t skipBytesCounter = 0;

    // Swizzle pixels
    bool swizzleActive = false;
    std::array<uint32_t, workBufferN> swizzleSelect;
};

#endif //  #ifndef _LED_DATA_PROCESSOR_H_
