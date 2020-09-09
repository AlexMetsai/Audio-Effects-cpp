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

AudioFile<double> delay_reverb(AudioFile<double> audioFile);

int main(){
    //TODO
}

// Algorithmic delay/reverb.
AudioFile<double> delay_reverb(AudioFile<double> audioFile){
    // TODO: add decay and delay duration as parameters?
    float delayMilliseconds = 0.3;
    double decay = 0.5f;
    int delaySamples = int(delayMilliseconds * audioFile.getSampleRate());
    std::cout << "Delay/Reverb effect using" << "delaySamples: " << delaySamples << " " << audioFile.getSampleRate() << " " << audioFile.getNumSamplesPerChannel();
    for (int i = 0; i < audioFile.getNumSamplesPerChannel() - delaySamples; i++){
        audioFile.samples[0][i+delaySamples] += (double)((double)audioFile.samples[0][i] * decay);
    }
    return audioFile;
}
