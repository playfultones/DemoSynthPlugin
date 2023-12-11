//
// Created by Bence Kovács on 10/12/2023.
//

#include "SineWaveVoice.h"

bool SineWaveVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SineWaveVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound*, int)
{
    currentAngle = 0.0;
    level = velocity * 0.15;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    tailOff = 0.0;
}

void SineWaveVoice::stopNote (float, bool)
{
    if (tailOff == 0.0)
        tailOff = 1.0;
}

void SineWaveVoice::controllerMoved (int, int)
{
}

void SineWaveVoice::pitchWheelMoved (int)
{
}


void SineWaveVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (tailOff > 0.0)
    {
        for (int i = startSample; i < startSample + numSamples; ++i)
        {
            const auto value = static_cast<float>(std::sin(currentAngle) * level * tailOff);

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                outputBuffer.addSample(channel, i, value);

            currentAngle += frequency * 2.0 * juce::MathConstants<double>::pi / getSampleRate();

            tailOff *= 0.99;

            if (tailOff <= 0.005)
            {
                clearCurrentNote();
                break;
            }
        }
    }
    else
    {
        for (int i = startSample; i < startSample + numSamples; ++i)
        {
            const auto value = static_cast<float>(std::sin(currentAngle) * level);

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
                outputBuffer.addSample(channel, i, value);

            currentAngle += frequency * 2.0 * juce::MathConstants<double>::pi / getSampleRate();
        }
    }
}
