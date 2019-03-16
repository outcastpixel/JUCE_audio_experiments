/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Gain_pluginAudioProcessorEditor::Gain_pluginAudioProcessorEditor (Gain_pluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    auto& parameters = processor.getParameters();
    AudioParameterFloat* gainParameter = (AudioParameterFloat*)parameters.getUnchecked(0);
    
    mGainControlSlider.setBounds(0, 0, 100, 100);
    mGainControlSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mGainControlSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    mGainControlSlider.setRange(gainParameter->range.start, gainParameter->range.end);
    mGainControlSlider.setValue(*gainParameter);
    
    mGainControlSlider.onDragStart = [gainParameter] {
        gainParameter->beginChangeGesture();
    };
    
    mGainControlSlider.onValueChange = [this, gainParameter] {
        DBG("PluginEditor->onValueChange");
        *gainParameter = mGainControlSlider.getValue();
    };
    
    mGainControlSlider.onDragEnd = [gainParameter] {
        gainParameter->endChangeGesture();
    };
    
    addAndMakeVisible(mGainControlSlider);
}

Gain_pluginAudioProcessorEditor::~Gain_pluginAudioProcessorEditor()
{
}

//==============================================================================
void Gain_pluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void Gain_pluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
