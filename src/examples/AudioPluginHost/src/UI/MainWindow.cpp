#include "MainWindow.h"

// ----------------------------------------------------------------------

MainWindow::MainWindow(juce::String name)
    : DocumentWindow(name,
                     juce::Desktop::getInstance()
                        .getDefaultLookAndFeel()
                        .findColour(ResizableWindow::backgroundColourId),
                     DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    //setContentOwned(new MainComponent(), true);

#if JUCE_IOS || JUCE_ANDROID
    setFullScreen(true);
#else
    setResizable(true, true);
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
    JUCEApplication::quit();
}

bool MainWindow::isDoublePrecisionProcessingEnabled()
{
    //if (auto* props = getAppProperties().getUserSettings())
    //    return props->getBoolValue ("doublePrecisionProcessing", false);

    return false;
}

bool MainWindow::isAutoScalePluginWindowsEnabled()
{
    //if (auto* props = getAppProperties().getUserSettings())
    //    return props->getBoolValue ("autoScalePluginWindows", false);

    return false;
}

void MainWindow::updatePrecisionMenuItem (ApplicationCommandInfo& info)
{
    info.setInfo ("Double Floating-Point Precision Rendering", {}, "General", 0);
    info.setTicked (isDoublePrecisionProcessingEnabled());
}

void MainWindow::updateAutoScaleMenuItem (ApplicationCommandInfo& info)
{
    info.setInfo ("Auto-Scale Plug-in Windows", {}, "General", 0);
    info.setTicked (isAutoScalePluginWindowsEnabled());
}

void MainWindow::showAudioSettings()
{
    auto* audioSettingsComp = new AudioDeviceSelectorComponent (deviceManager,
                                                                0, 256,
                                                                0, 256,
                                                                true, true,
                                                                true, false);

    audioSettingsComp->setSize (500, 450);

    DialogWindow::LaunchOptions o;
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


