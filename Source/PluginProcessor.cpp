/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstSamplerAudioProcessor::FirstSamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    //registers basic audio formats (mp3, wav, etc.) so that you can stream audio
    mFormatManager.registerBasicFormats(); 

    //adds voices to the synthesizer based on const num declared in header file. 
    for (int i = 0; i < mNumVoices; i++)
    {
        mSampler.addVoice(new juce::SamplerVoice); 
    }
}

FirstSamplerAudioProcessor::~FirstSamplerAudioProcessor()
{
    delete mFormatReader; 
}

//==============================================================================
const juce::String FirstSamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FirstSamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FirstSamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FirstSamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FirstSamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FirstSamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FirstSamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FirstSamplerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FirstSamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void FirstSamplerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FirstSamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSampler.setCurrentPlaybackSampleRate(sampleRate); 
}

void FirstSamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FirstSamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void FirstSamplerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    mSampler.renderNextBlock(buffer, midiMessages,0,buffer.getNumSamples()); 
}

//==============================================================================
bool FirstSamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FirstSamplerAudioProcessor::createEditor()
{
    return new FirstSamplerAudioProcessorEditor (*this);
}

//==============================================================================
void FirstSamplerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FirstSamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void FirstSamplerAudioProcessor::loadFile()
{
    mSampler.clearSounds();

    //delete previous file
    if (mFormatReader != nullptr)
        delete mFormatReader; 

    juce::FileChooser chooser { "Please load a file" }; 
   
    if (chooser.browseForFileToOpen())
    {
        juce::File file = chooser.getResult(); 
        mFormatReader = mFormatManager.createReaderFor(file);

        juce::BigInteger range; 
        range.setRange(0, 128, true); 

        mSampler.addSound(new juce::SamplerSound("Sample", *mFormatReader, range, 60, 0.1, 0.1, 10)); 
        
        //sets the waveform so it can be drawn in audioWave
        auto sampleLength = static_cast<int> (mFormatReader->lengthInSamples);
        mWaveForm.setSize(1, sampleLength);
        mFormatReader->read(&mWaveForm, 0, sampleLength, 0, true, false);
    }

}

void FirstSamplerAudioProcessor::loadFile(const juce::String& path)
{
    mSampler.clearSounds(); 

    auto file = juce::File(path); 

    if(mFormatReader != nullptr)
        delete mFormatReader; //delete previous file

    mFormatReader = mFormatManager.createReaderFor(file);

    //sets the waveform so it can be drawn in audioWave
    auto sampleLength = static_cast<int> (mFormatReader->lengthInSamples); 
    mWaveForm.setSize(1, sampleLength);
    mFormatReader->read(&mWaveForm, 0, sampleLength, 0, true, false);


    juce::BigInteger range;
    range.setRange(0, 128, true);
    mSampler.addSound(new juce::SamplerSound("Sample", *mFormatReader, range, 60, 0.1, 0.1, 10.0));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstSamplerAudioProcessor();
}
