cmake_minimum_required(VERSION 3.22)

project(HelloWorldExample VERSION 0.0.1)

juce_add_gui_app(HelloWorldExample
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "Hello World Example")

juce_generate_juce_header(${PROJECT_NAME})

target_sources(HelloWorldExample
    PRIVATE
        Main.cpp
        MainComponent.h
        MainComponent.cpp)

target_compile_definitions(HelloWorldExample
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:HelloWorldExample,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:HelloWorldExample,JUCE_VERSION>")

target_link_libraries(HelloWorldExample
    PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)