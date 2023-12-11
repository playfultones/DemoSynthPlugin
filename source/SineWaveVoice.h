//
// Created by Bence Kovács on 10/12/2023.
//

#ifndef DEMOSYNTH_SINEWAVEVOICE_H
#define DEMOSYNTH_SINEWAVEVOICE_H

#include <juce_audio_basics/juce_audio_basics.h>

class SineWaveVoice : public juce::SynthesiserVoice
{
public:
    SineWaveVoice() = default;
    ~SineWaveVoice() override = default;

    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
    void stopNote(float /*velocity*/, bool /*allowTailOff*/) override;

    void pitchWheelMoved(int /*newValue*/) override;
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
    double currentAngle = 0.0;
    double level = 0.0;
    double frequency = 0.0;
    double tailOff = 0.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SineWaveVoice)
};

#endif //DEMOSYNTH_SINEWAVEVOICE_H
