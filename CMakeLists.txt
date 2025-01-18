cmake_minimum_required(VERSION 3.20)

project(microbit LANGUAGES C)

find_package(Git REQUIRED)
execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --match "v[0-9]*.[0-9]*.[0-9]*"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
string(REGEX REPLACE "^v(.*)" "\\1" GIT_VERSION "${GIT_TAG}")
if(NOT GIT_VERSION MATCHES "[0-9]+.[0-9]+.[0-9]+")
    set(GIT_VERSION "0.0.0")
endif()

string(APPEND CMAKE_C_FLAGS " -mthumb -mcpu=cortex-m4 -mfloat-abi=soft")
string(APPEND CMAKE_C_FLAGS " -ffunction-sections -fdata-sections")

string(APPEND CMAKE_C_FLAGS " -Wall -Wextra -Wpedantic -Wno-unused-parameter -Werror")

string(APPEND CMAKE_C_FLAGS_DEBUG " -Og -g3 -ggdb3")

set(LINKER_SCRIPT linker.ld)

set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT} \
-Wl,-Map=${TARGET_NAME}.map -Wl,--print-memory-usage \
-Wl,--gc-sections -static")

set(TARGET_NAME ${PROJECT_NAME})
add_subdirectory(src)
