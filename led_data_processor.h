#ifndef _LED_DATA_PROCESSOR_H_
#define _LED_DATA_PROCESSOR_H_

#include <stdint.h>
#include <stdlib.h>

class LedDataProcessor {
public:
    static LedDataProcessor &instance();
    void process(uint32_t data);
private:
    void init();
    bool initialized = false;
};

#endif //  #ifndef _LED_DATA_PROCESSOR_H_
