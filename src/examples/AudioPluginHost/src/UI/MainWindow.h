#pragma once
#include <JuceHeader.h>

//==============================================================================
namespace CommandIDs
{
   #if ! (JUCE_IOS || JUCE_ANDROID)
    static const int open                   = 0x30000;
    static const int save                   = 0x30001;
    static const int saveAs                 = 0x30002;
    static const int newFile                = 0x30003;
   #endif
    static const int showPluginListEditor   = 0x30100;
    static const int showAudioSettings      = 0x30200;
    static const int aboutBox               = 0x30300;
    static const int allWindowsForward      = 0x30400;
    static const int toggleDoublePrecision  = 0x30500;
    static const int autoScalePluginWindows = 0x30600;
}

//==============================================================================
juce::ApplicationCommandManager& getCommandManager();
juce::ApplicationProperties& getAppProperties();
bool isOnTouchDevice();

//==============================================================================
/*
    This class implements the desktop window that contains an instance of
    our MainComponent class.
*/
class MainWindow : 
    public juce::DocumentWindow,
    public juce::MenuBarModel,
    public juce::ApplicationCommandTarget
{
public:
    explicit MainWindow(juce::String name);
    ~MainWindow() override;

    void closeButtonPressed() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>&) override;
    void getCommandInfo(juce::CommandID, juce::ApplicationCommandInfo&) override;
    bool perform(const InvocationInfo&) override;

    void menuBarActivated(bool isActive) override;
    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

private:
    static bool isDoublePrecisionProcessingEnabled();
    static bool isAutoScalePluginWindowsEnabled();

    static void updatePrecisionMenuItem(juce::ApplicationCommandInfo& info);
    static void updateAutoScaleMenuItem(juce::ApplicationCommandInfo& info);

    void showAudioSettings();

private:    
    juce::AudioDeviceManager deviceManager;
    juce::AudioPluginFormatManager formatManager;

    std::vector<juce::PluginDescription> internalTypes;
    juce::KnownPluginList knownPluginList;
    juce::KnownPluginList::SortMethod pluginSortMethod;
    juce::Array<juce::PluginDescription> pluginDescriptions;

    //class PluginListWindow;
    //std::unique_ptr<PluginListWindow> pluginListWindow;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};
