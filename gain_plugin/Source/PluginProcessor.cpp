/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Gain_pluginAudioProcessor::Gain_pluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    DBG("PluginProcessor Constructor");
    addParameter(mGainParameter = new AudioParameterFloat("gain","Gain",0.0f,1.0f,0.5f));
    mGainSmoothed = mGainParameter->get();
}

Gain_pluginAudioProcessor::~Gain_pluginAudioProcessor()
{
}

//==============================================================================
const String Gain_pluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Gain_pluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Gain_pluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Gain_pluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Gain_pluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Gain_pluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Gain_pluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Gain_pluginAudioProcessor::setCurrentProgram (int index)
{
}

const String Gain_pluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Gain_pluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Gain_pluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Gain_pluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Gain_pluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Gain_pluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    DBG("PluginProcessor->processBlock.");
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
       buffer.clear (i, 0, buffer.getNumSamples());
    }
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    //DBG(*mGainParameter);
    
    float* leftChannel = nullptr;
    float* rightChannel = nullptr;
    
    if (totalNumInputChannels == 1)
    {
        leftChannel = buffer.getWritePointer(0);
    }
    else if (totalNumInputChannels == 2)
    {
        leftChannel = buffer.getWritePointer(0);
        rightChannel = buffer.getWritePointer(1);
    }
    
    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        mGainSmoothed = mGainSmoothed - 0.004 * (mGainSmoothed - mGainParameter->get());
        if (leftChannel != nullptr) leftChannel[sample] *= mGainSmoothed;
        if (rightChannel != nullptr) rightChannel[sample] *= mGainSmoothed;
    }
}

//==============================================================================
bool Gain_pluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Gain_pluginAudioProcessor::createEditor()
{
    return new Gain_pluginAudioProcessorEditor (*this);
}

//==============================================================================
void Gain_pluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Gain_pluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Gain_pluginAudioProcessor();
}
