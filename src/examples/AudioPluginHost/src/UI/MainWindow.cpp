#include "MainWindow.h"

// ----------------------------------------------------------------------

MainWindow::MainWindow(juce::String name)
    : DocumentWindow(name,
                     juce::Desktop::getInstance()
                        .getDefaultLookAndFeel()
                        .findColour(ResizableWindow::backgroundColourId),
                     DocumentWindow::allButtons)
{
    formatManager.addDefaultFormats();
    //formatManager.addFormat(new InternalPluginFormat());

    auto safeThis = SafePointer<MainWindow>(this);
    juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
        [safeThis](bool granted) mutable
        {
            auto savedState = getAppProperties().getUserSettings()->getXmlValue("audioDeviceState");
            safeThis->deviceManager.initialise(granted ? 256 : 0, 256, savedState.get(), true);
        });

    // Setup the window's appearance
    setUsingNativeTitleBar(true);
    #if JUCE_IOS || JUCE_ANDROID
        setFullScreen(true);
    #else
        setResizable(true, true);
        setResizeLimits(500, 400, 10000, 10000);
        centreWithSize(getWidth(), getHeight());
    #endif
    setVisible(true);
}

// ----------------------------------------------------------------------

MainWindow::~MainWindow()
{

}

// ----------------------------------------------------------------------

void MainWindow::closeButtonPressed()
{
    //tryToQuitApplication();
    juce::JUCEApplication::quit();
}

bool MainWindow::isDoublePrecisionProcessingEnabled()
{
    if (auto* props = getAppProperties().getUserSettings())
        return props->getBoolValue ("doublePrecisionProcessing", false);
    return false;
}

bool MainWindow::isAutoScalePluginWindowsEnabled()
{
    if (auto* props = getAppProperties().getUserSettings())
        return props->getBoolValue ("autoScalePluginWindows", false);
    return false;
}

void MainWindow::updatePrecisionMenuItem(juce::ApplicationCommandInfo& info)
{
    info.setInfo ("Double Floating-Point Precision Rendering", {}, "General", 0);
    info.setTicked (isDoublePrecisionProcessingEnabled());
}

void MainWindow::updateAutoScaleMenuItem(juce::ApplicationCommandInfo& info)
{
    info.setInfo ("Auto-Scale Plug-in Windows", {}, "General", 0);
    info.setTicked (isAutoScalePluginWindowsEnabled());
}

void MainWindow::showAudioSettings()
{
    auto* audioSettingsComp = new juce::AudioDeviceSelectorComponent (deviceManager,
                                                                0, 256,
                                                                0, 256,
                                                                true, true,
                                                                true, false);

    audioSettingsComp->setSize (500, 450);

    juce::DialogWindow::LaunchOptions o;
    o.content.setOwned (audioSettingsComp);
    o.dialogTitle                   = "Audio Settings";
    o.componentToCentreAround       = this;
    o.dialogBackgroundColour        = getLookAndFeel().findColour (ResizableWindow::backgroundColourId);
    o.escapeKeyTriggersCloseButton  = true;
    o.useNativeTitleBar             = false;
    o.resizable                     = false;

     auto* w = o.create();
     auto safeThis = SafePointer<MainWindow> (this);
/****
     w->enterModalState (true,
                         ModalCallbackFunction::create
                         ([safeThis] (int)
                         {
                             auto audioState = safeThis->deviceManager.createStateXml();

                             getAppProperties().getUserSettings()->setValue ("audioDeviceState", audioState.get());
                             getAppProperties().getUserSettings()->saveIfNeeded();

                             if (safeThis->graphHolder != nullptr)
                                 if (safeThis->graphHolder->graph != nullptr)
                                     safeThis->graphHolder->graph->graph.removeIllegalConnections();
                         }), true);
**/
}

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

juce::ApplicationCommandTarget* MainWindow::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
};

void MainWindow::getAllCommands(juce::Array<juce::CommandID>& commands)
{
    // this returns the set of all commands that this target can perform..
    const juce::CommandID ids[] = {
                             #if ! (JUCE_IOS || JUCE_ANDROID)
                              CommandIDs::newFile,
                              CommandIDs::open,
                              CommandIDs::save,
                              CommandIDs::saveAs,
                             #endif
                              CommandIDs::showPluginListEditor,
                              CommandIDs::showAudioSettings,
                              CommandIDs::toggleDoublePrecision,
                              CommandIDs::aboutBox,
                              CommandIDs::allWindowsForward,
                              CommandIDs::autoScalePluginWindows
    };

    commands.addArray(ids, juce::numElementsInArray(ids));
};

void MainWindow::getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result)
{
    const juce::String category("General");

    switch (commandID)
    {
#if ! (JUCE_IOS || JUCE_ANDROID)
    case CommandIDs::newFile:
        result.setInfo("New", "Creates a new filter graph file", category, 0);
        result.defaultKeypresses.add(juce::KeyPress('n', juce::ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::open:
        result.setInfo("Open...", "Opens a filter graph file", category, 0);
        result.defaultKeypresses.add(juce::KeyPress('o', juce::ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::save:
        result.setInfo("Save", "Saves the current graph to a file", category, 0);
        result.defaultKeypresses.add(juce::KeyPress('s', juce::ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::saveAs:
        result.setInfo("Save As...",
            "Saves a copy of the current graph to a file",
            category, 0);
        result.defaultKeypresses.add(juce::KeyPress('s', juce::ModifierKeys::shiftModifier | juce::ModifierKeys::commandModifier, 0));
        break;
#endif

    case CommandIDs::showPluginListEditor:
        result.setInfo("Edit the List of Available Plug-ins...", {}, category, 0);
        result.addDefaultKeypress('p', juce::ModifierKeys::commandModifier);
        break;

    case CommandIDs::showAudioSettings:
        result.setInfo("Change the Audio Device Settings", {}, category, 0);
        result.addDefaultKeypress('a', juce::ModifierKeys::commandModifier);
        break;

    case CommandIDs::toggleDoublePrecision:
        updatePrecisionMenuItem(result);
        break;

    case CommandIDs::aboutBox:
        result.setInfo("About...", {}, category, 0);
        break;

    case CommandIDs::allWindowsForward:
        result.setInfo("All Windows Forward", "Bring all plug-in windows forward", category, 0);
        result.addDefaultKeypress('w', juce::ModifierKeys::commandModifier);
        break;

    case CommandIDs::autoScalePluginWindows:
        updateAutoScaleMenuItem(result);
        break;

    default:
        break;
    }
};

bool MainWindow::perform(const InvocationInfo&)
{


    return true;
};

// ----------------------------------------------------------------------
// ----------------------------------------------------------------------

void MainWindow::menuBarActivated(bool isActive)
{};

juce::StringArray MainWindow::getMenuBarNames()
{
    juce::StringArray names;
    names.add("File");
    names.add("Plugins");
    names.add("Options");
    names.add("Windows");
    return names;
};

juce::PopupMenu MainWindow::getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName)
{
    juce::PopupMenu menu;

    return menu;
};

void MainWindow::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{};


// ----------------------------------------------------------------------


