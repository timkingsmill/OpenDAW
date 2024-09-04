//#include <JuceHeader.h>
#include "UI/MainWindow.h"

#if ! (JUCE_PLUGINHOST_VST || JUCE_PLUGINHOST_VST3 || JUCE_PLUGINHOST_AU)
    #error "If you're building the audio plugin host, you probably want to enable VST and/or AU support"
#endif

/* ------------------------------------------------------------------------------------
* 
*/

class PluginHostApplication : 
    public juce::JUCEApplication,
    private juce:: AsyncUpdater 
{
public:
    // ---------------------------------------------------------------------------------
    PluginHostApplication() {}

    // ---------------------------------------------------------------------------------
    void initialise(const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        juce::ignoreUnused(commandLine);

        juce::PropertiesFile::Options options;
        options.applicationName = getApplicationName();
        options.filenameSuffix = "settings";
        options.osxLibrarySubFolder = "Preferences";

        appProperties.reset(new juce::ApplicationProperties());
        appProperties->setStorageParameters(options);

        mainWindow.reset(new MainWindow(getApplicationName()));
        mainWindow->setUsingNativeTitleBar(true);

        commandManager.registerAllCommandsForTarget(this);
        commandManager.registerAllCommandsForTarget(mainWindow.get());

        mainWindow->menuItemsChanged();
    }

    // ---------------------------------------------------------------------------------
    // We inject these as compile definitions from the CMakeLists.txt
    // If you've enabled the juce header with `juce_generate_juce_header(<thisTarget>)`
    // you could `#include <JuceHeader.h>` and use `ProjectInfo::projectName` etc. instead.
    const juce::String getApplicationName() override 
    { 
        return ProjectInfo::projectName;
    }
    
    const juce::String getApplicationVersion() override 
    { 
        return ProjectInfo::versionString;
    }

    // ---------------------------------------------------------------------------------
    bool moreThanOneInstanceAllowed() override 
    { 
        return true; 
    }

    // ---------------------------------------------------------------------------------
    void shutdown() override
    {
        // Add your application's shutdown code here..
        mainWindow = nullptr; // (deletes our window)
    }

    // ---------------------------------------------------------------------------------
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    // ---------------------------------------------------------------------------------
    void anotherInstanceStarted(const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
        juce::ignoreUnused(commandLine);
    }

    /**
    *   Implement abstract juce::AsyncUpdater class
    */
    void handleAsyncUpdate() override
    {

    }

    juce::ApplicationCommandManager commandManager;
    std::unique_ptr<juce::ApplicationProperties> appProperties;

private:
    std::unique_ptr<MainWindow> mainWindow;
};

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------

static PluginHostApplication& getApp() 
{ 
    return *dynamic_cast<PluginHostApplication*>(juce::JUCEApplication::getInstance());
}

juce::ApplicationProperties& getAppProperties()
{ 
    return *getApp().appProperties; 
}

juce::ApplicationCommandManager& getCommandManager()
{ 
    return getApp().commandManager; 
}

// ------------------------------------------------------------------------------------

bool isOnTouchDevice()
{
    static bool isTouch = juce::Desktop::getInstance().getMainMouseSource().isTouch();
    return isTouch;
}

// ------------------------------------------------------------------------------------
/**
 *  This macro generates the main() routine that launches the app.
 */
START_JUCE_APPLICATION(PluginHostApplication)
