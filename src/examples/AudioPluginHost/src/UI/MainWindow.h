#pragma once
#include <JuceHeader.h>


//==============================================================================
/*
    This class implements the desktop window that contains an instance of
    our MainComponent class.
*/
class MainWindow : public juce::DocumentWindow
{
public:
    explicit MainWindow(juce::String name);
    ~MainWindow() override;


    void closeButtonPressed() override;

private:
    static bool isDoublePrecisionProcessingEnabled();
    static bool isAutoScalePluginWindowsEnabled();

    static void updatePrecisionMenuItem(ApplicationCommandInfo& info);
    static void updateAutoScaleMenuItem(ApplicationCommandInfo& info);

    void showAudioSettings();

private:    
    AudioDeviceManager deviceManager;
    AudioPluginFormatManager formatManager;

    std::vector<PluginDescription> internalTypes;
    KnownPluginList knownPluginList;
    KnownPluginList::SortMethod pluginSortMethod;
    Array<PluginDescription> pluginDescriptions;

    //class PluginListWindow;
    //std::unique_ptr<PluginListWindow> pluginListWindow;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};
