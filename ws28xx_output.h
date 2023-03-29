#ifndef _WS28XX_OUTPUT_H_
#define _WS28XX_OUTPUT_H_

#include <cstdint>

class WS28xxOutput {
public:
    static WS28xxOutput &instance();
    void output(uint32_t data);
private:
    static constexpr uint32_t END_OF_DATA = 0xffffffff;

    void init();
    bool initialized = false;
};

#endif //  #ifndef _WS28XX_OUTPUT_H_
