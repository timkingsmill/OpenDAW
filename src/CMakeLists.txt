# Configure the JUCE library --------------------------------------------
# Set JUCE library source path 
set(JUCE_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../libs/JUCE" CACHE STRING "Path to JUCE library source tree")
message(STATUS "Using JUCE library from ${JUCE_SOURCE_PATH}")

# Call the JUCE library CMakeLists.txt
add_subdirectory(${JUCE_SOURCE_PATH} ${CMAKE_BINARY_DIR}/JUCE EXCLUDE_FROM_ALL)# Add src subdirectory -------------------------------------------------------------
add_subdirectory(OpenDAW)
