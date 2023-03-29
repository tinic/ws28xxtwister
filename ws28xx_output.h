#ifndef _WS28XX_OUTPUT_H_
#define _WS28XX_OUTPUT_H_

#include <stdint.h>

class WS28xxOutput {
public:
    static WS28xxOutput &instance();
    void output(uint32_t data);
private:
    void init();
    bool initialized = false;
};

#endif //  #ifndef _WS28XX_OUTPUT_H_
