cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

project(ws28xxtwister)

set(USE_CORE 0)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${PROJECT_NAME})

#.\openocd -f .\jlink.cfg -c "transport select swd" -c "adapter_khz 6000" -f .\rp2040.cfg  -c "reset halt program blink.elf reset exit"

set(PROGRAM_CMD "./openocd --debug -f ./jlink.cfg -c \"adapter speed 6000\" -f ./rp2040.cfg -c \"targets rp2040.core0; program ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin ${BASE_ADDRESS} verify reset exit\"")
install(CODE "execute_process(COMMAND ${PROGRAM_CMD} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/openocd)")
