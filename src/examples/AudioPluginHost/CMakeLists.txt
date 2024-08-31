cmake_minimum_required(VERSION 3.22)

project(AudioPluginHost VERSION 0.0.1)

###add_subdirectory(${JUCE_SOURCE_PATH} ${CMAKE_BINARY_DIR}/JUCE EXCLUDE_FROM_ALL)

# -----------------------------------------------------------
juce_add_gui_app(${PROJECT_NAME}
    BUNDLE_ID                       com.juce.pluginhost
    #ICON_BIG                        "${CMAKE_CURRENT_SOURCE_DIR}/Source/JUCEAppIcon.png"
    MICROPHONE_PERMISSION_ENABLED   TRUE
    PLUGINHOST_AU                   TRUE)

# -----------------------------------------------------------

juce_generate_juce_header(${PROJECT_NAME})

# -----------------------------------------------------------

target_sources(${PROJECT_NAME} PRIVATE
    src/Main.cpp
    #Source/Plugins/IOConfigurationWindow.cpp
    #Source/Plugins/InternalPlugins.cpp
    #Source/Plugins/PluginGraph.cpp
    #Source/UI/GraphEditorPanel.cpp
    #Source/UI/MainHostWindow.cpp
)

# -----------------------------------------------------------


# -----------------------------------------------------------

target_link_libraries(${PROJECT_NAME} PRIVATE
    juce::juce_audio_utils
    juce::juce_cryptography
    juce::juce_dsp
    juce::juce_opengl
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)

# -----------------------------------------------------------
# -----------------------------------------------------------
