#ifndef _WS28XX_OUTPUT_H_
#define _WS28XX_OUTPUT_H_

#include <cstdint>

class WS28xxOutput {
public:
    static WS28xxOutput &instance();

    enum LEDDataType {
        rgb8,
        rgba8,
        rgb16,
        rgba16
    } ledDataType = rgb8;

    void setLedDataType(LEDDataType type) { ledDataType = type; update(); }
    LEDDataType LedDataType() const { return ledDataType; }

    void outputRGB8(uint32_t pixel) { (*this.*rgb8Func)(pixel); } ;
    void outputRGBA8(uint32_t pixel) { (*this.*rgba8Func)(pixel); };
    void outputRGB16(uint64_t pixel) { (*this.*rgb16Func)(pixel); };
    void outputRGBA16(uint64_t pixel) { (*this.*rgba16Func)(pixel); };

private:
    void update();

    void outputRGB8toRGB8(uint32_t data);
    void outputRGB8toRGBA8(uint32_t data);
    void outputRGB8toRGB16(uint32_t data);
    void outputRGB8toRGBA16(uint32_t data);
    typedef void (WS28xxOutput::*RGB8Func)(uint32_t);
    RGB8Func rgb8Func = nullptr;

    void outputRGBA8toRGB8(uint32_t data);
    void outputRGBA8toRGBA8(uint32_t data);
    void outputRGBA8toRGB16(uint32_t data);
    void outputRGBA8toRGBA16(uint32_t data);
    typedef void (WS28xxOutput::*RGBA8Func)(uint32_t);
    RGBA8Func rgba8Func = nullptr;

    void outputRGB16toRGB8(uint64_t data);
    void outputRGB16toRGBA8(uint64_t data);
    void outputRGB16toRGB16(uint64_t data);
    void outputRGB16toRGBA16(uint64_t data);
    typedef void (WS28xxOutput::*RGB16Func)(uint64_t);
    RGB16Func rgb16Func = nullptr;

    void outputRGBA16toRGB8(uint64_t data);
    void outputRGBA16toRGBA8(uint64_t data);
    void outputRGBA16toRGB16(uint64_t data);
    void outputRGBA16toRGBA16(uint64_t data);
    typedef void (WS28xxOutput::*RGBA16Func)(uint64_t);
    RGBA16Func rgba16Func = nullptr;

    static constexpr uint32_t END_OF_DATA = 0xffffffff;

    void init();
    bool initialized = false;
};

#endif //  #ifndef _WS28XX_OUTPUT_H_
