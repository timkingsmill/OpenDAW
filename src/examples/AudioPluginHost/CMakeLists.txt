cmake_minimum_required(VERSION 3.22)

project(AudioPluginHost VERSION 0.0.1)

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
    src/MainApplication.cpp
    src/UI/MainWindow.h
    src/UI/MainWindow.cpp
    src/MainComponent.h
    src/MainComponent.cpp
    #Source/Plugins/IOConfigurationWindow.cpp
    src/Plugins/InternalPlugins.h
    src/Plugins/InternalPlugins.cpp
    #Source/Plugins/PluginGraph.cpp
    #Source/UI/GraphEditorPanel.cpp
    #Source/UI/MainHostWindow.cpp
)

# -----------------------------------------------------------

target_compile_definitions(${PROJECT_NAME} PRIVATE
    PIP_JUCE_EXAMPLES_DIRECTORY_STRING="${JUCE_SOURCE_DIR}/examples"
    JUCE_ALSA=1
    JUCE_DIRECTSOUND=1
    JUCE_PLUGINHOST_LADSPA=1
    JUCE_PLUGINHOST_VST3=1
    JUCE_PLUGINHOST_VST=0
    JUCE_USE_CAMERA=0
    JUCE_USE_CDBURNER=0
    JUCE_USE_CDREADER=0
    JUCE_USE_CURL=0
    JUCE_USE_FLAC=0
    JUCE_USE_OGGVORBIS=1
    JUCE_VST3_HOST_CROSS_PLATFORM_UID=1
    JUCE_WASAPI=1
    JUCE_WEB_BROWSER=0)

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
