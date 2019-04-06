cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME Arduino2)

set(${PROJECT_NAME}_BOARD mega)
set(ARDUINO_CPU atmega2560)
project(${PROJECT_NAME})


# Setup FastLED library
include_directories(libs/FastLED-3.2.0)
set(FASTLED_SRC
    libs/FastLED-3.2.0/power_mgt.cpp
    libs/FastLED-3.2.0/colorutils.cpp
    libs/FastLED-3.2.0/lib8tion.cpp
    libs/FastLED-3.2.0/FastLED.cpp
    libs/FastLED-3.2.0/noise.cpp
    libs/FastLED-3.2.0/hsv2rgb.cpp
    libs/FastLED-3.2.0/wiring.cpp
    libs/FastLED-3.2.0/bitswap.cpp
    libs/FastLED-3.2.0/colorpalettes.cpp
)
set(led_lib_SRCS ${FASTLED_SRC})
set(led_lib_BOARD mega)
generate_arduino_library(led_lib)


### Main sketch file
set(${PROJECT_NAME}_SKETCH arduino2.ino)
set(${PROJECT_NAME}_LIBS led_lib)

#### Additional settings for programmer. From programmers.txt
set(${PROJECT_NAME}_PORT /dev/cu.usbserial-141220)
set(mega.upload.speed 9600)

## Verbose build process
set(${PROJECT_NAME}_AFLAGS -v)

generate_arduino_firmware(${PROJECT_NAME})
