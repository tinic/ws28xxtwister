#ifndef _WS28XX_DECODER_H_
#define _WS28XX_DECODER_H_

class WS28xxDecoder {
public:
    static WS28xxDecoder &instance();
private:
    void init();
    bool initialized = false;
};

#endif //  #ifndef _WS28XX_DECODER_H_
