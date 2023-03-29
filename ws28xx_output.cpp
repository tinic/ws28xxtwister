#include "ws28xx_output.h"

WS28xxOutput  &WS28xxOutput ::instance() {
    static WS28xxOutput ws28xxOutput;
    if (!ws28xxOutput.initialized) {
        ws28xxOutput.initialized = true;
        ws28xxOutput.init();
    }
    return ws28xxOutput;
}

void WS28xxOutput::init() {
}

void WS28xxOutput::output(uint32_t data) {
}
