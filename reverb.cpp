/* Alexandros I. Metsai
 * alexmetsai@gmail.com
 *
 * License will probably be GPLv3.
 *
 * Librady for reading/writing wav files: adamstark/AudioFile
 */

#include <vector>
#include <iostream>
#include <string>
#include "AudioFile.h"
#include <cstring>

AudioFile<double> delay_reverb(AudioFile<double> audioFile, float delayMilliseconds = 0.3, double decay = 0.5f);

int main(){
    // Load wav file
    AudioFile<double> audioFile;
    audioFile.load("input.wav");
    
    // Apply Reverb effect.
    audioFile = delay_reverb(audioFile);
    audioFile.save("output.wav");
    
    return 0;
}

// Algorithmic Delay/Reverb.
AudioFile<double> delay_reverb(AudioFile<double> audioFile, float delayMilliseconds, double decay){
    // TODO: handle multiple channels
    
    int delaySamples = int(delayMilliseconds * audioFile.getSampleRate());
    
    std::cout << "Delay/Reverb effect using" << "delaySamples: " << 
    delaySamples << " " << audioFile.getSampleRate() << " " << audioFile.getNumSamplesPerChannel() << std::endl;
    
    for (int i = 0; i < audioFile.getNumSamplesPerChannel() - delaySamples; i++){
        audioFile.samples[0][i+delaySamples] += (double)((double)audioFile.samples[0][i] * decay);
    }
    
    return audioFile;
}
