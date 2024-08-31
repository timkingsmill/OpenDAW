cmake_minimum_required(VERSION 3.15)

project(OpenDAW VERSION 0.0.1 LANGUAGES CXX ASM)

# Banner ------------------------------------------------------------
message(STATUS "OpenDAW! Version is ${PROJECT_VERSION}")
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
message(STATUS "CMake version is ${CMAKE_VERSION}")
message(STATUS "Compiler ID is ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler version is ${CMAKE_CXX_COMPILER_VERSION}")
math(EXPR OPEN_DAW_BITNESS "${CMAKE_SIZEOF_VOID_P} * 8" OUTPUT_FORMAT DECIMAL)
message(STATUS "Targeting ${OPEN_DAW_BITNESS}-bit configuration")

# Make Sure the JUCE repo is properly cloned ------------------------
set(OPEN_DAW_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
if (NOT EXISTS "${OPEN_DAW_SOURCE_DIR}/libs/JUCE/README.md")
    message(FATAL_ERROR 
        "Cannot find the JUCE library submodule... "
        "To resolve this, please run `git submodule update --init --recursive` and re-run CMake!")
endif()

# -------------------------------------------------------------------
# Set JUCE target build options.
# Improves module source grouping.
set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON)

# Add src subdirectory -------------------------------------------------------------
add_subdirectory(src)

# -----------------------------------------------------------------

