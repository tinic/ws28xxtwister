#include "ws28xx_output.h"
#include "ws28xx_output.pio.h"

WS28xxOutput  &WS28xxOutput ::instance() {
    static WS28xxOutput ws28xxOutput;
    if (!ws28xxOutput.initialized) {
        ws28xxOutput.initialized = true;
        ws28xxOutput.init();
    }
    return ws28xxOutput;
}

void WS28xxOutput::init() {
    ws28xx_output_init();
}

void WS28xxOutput::output(uint32_t data) {
    if (data != END_OF_DATA) {
        pio_sm_put_blocking(WS28XX_OUTPUT_PIO, 0, data << 24);
    }
}
