cmake_minimum_required(VERSION 3.13)

include(pico-sdk/pico_sdk_init.cmake)

project(ws28xxtwister)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(USE_CORE 0)

set(CC_FLAGS
    -flto=auto
    -Wformat=2 
    -Wformat-overflow
    -Wformat-truncation
    -Wnull-dereference
    -mthumb
    -fdata-sections
    -ffunction-sections
    -Wall
    -Wextra
    -Wpedantic 
    -Wfloat-conversion 
    -Wdouble-promotion
    -Wno-unused-parameter
    -Wno-strict-aliasing 
    -Wno-format
    -Wstack-usage=8192
    -Wuninitialized
    -fno-common
    -fstack-usage
    -ffast-math
    -ffat-lto-objects
    -fallow-store-data-races)

set(CXX_FLAGS 
    -Weffc++
    -Wsign-conversion
    -Wshadow 
    -Wnon-virtual-dtor
    -Wunused
    -Woverloaded-virtual
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wstrict-aliasing 
    -Wcast-align
    -Wconversion
    -Wno-volatile
    -std=c++20
    -fno-rtti 
    -fno-exceptions)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    led_data_processor.cpp
    ws28xx_decoder.cpp
    main.cpp
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws28xx_decoder.pio)

target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_pio)

target_compile_options(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CXX_FLAGS}>")
target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>")
target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>")

pico_add_extra_outputs(${PROJECT_NAME})

set(PROGRAM_CMD "./openocd --debug -f ./jlink.cfg -c \"adapter speed 6000\" -f ./rp2040.cfg -c \"targets rp2040.core0; program ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin ${BASE_ADDRESS} verify reset exit\"")
install(CODE "execute_process(COMMAND ${PROGRAM_CMD} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/openocd)")
