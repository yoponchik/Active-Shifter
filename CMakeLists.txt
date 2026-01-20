cmake_minimum_required(VERSION 3.16)

# This includes the magic ESP-IDF build system
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(ActiveShifter C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)