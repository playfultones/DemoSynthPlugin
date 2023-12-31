#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <playfultones_unitysynth/playfultones_unitysynth.h>

#if (MSVC)
#include "ipps.h"
#endif

class PluginProcessor : public juce::AudioProcessor
{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::MidiKeyboardState keyboardState;

private:
    juce::Synthesiser synth;
    playfultones::UnitySynth unitySynth;

    class SynthSound : public juce::SynthesiserSound
    {
    public:
        SynthSound() = default;
        bool appliesToNote (int /*midiNoteNumber*/) override { return true; }
        bool appliesToChannel (int /*midiChannel*/) override { return true; }
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthSound)
    };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
