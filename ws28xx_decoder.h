#ifndef _WS28XX_DECODER_H_
#define _WS28XX_DECODER_H_

#include "led_data_processor.h"

class WS28xxDecoder {
public:
    WS28xxDecoder() : ledDataProcessor(LedDataProcessor::instance()) {}

    static WS28xxDecoder &instance();

    enum LEDDataType {
        rgb8,
        rgba8,
        rgb16,
        rgba16
    } ledDataType = rgb8;

    void setLedDataType(LEDDataType type) { ledDataType = type; update(); }
    LEDDataType LedDataType() const { return ledDataType; }

private:
    LedDataProcessor &ledDataProcessor;

    friend void ws28xxx_decoder_isr();

    static constexpr uint32_t END_OF_DATA = 0xffffffff;

    size_t compIdx = 0;
    uint32_t pixel32 = 0;
    uint32_t pixel64 = 0;

    void process(uint32_t data);
    void update();

    void rgb8Decode(uint32_t);
    void rgba8Decode(uint32_t);
    void rgb16Decode(uint32_t);
    void rgba16Decode(uint32_t);

    typedef void (WS28xxDecoder::*DecoderFunc)(uint32_t);
    DecoderFunc decoderFunc = nullptr;

    void init();
    bool initialized = false;
};

#endif //  #ifndef _WS28XX_DECODER_H_
