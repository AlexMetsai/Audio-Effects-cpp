/* Copyright (C) 2020 Alexandros I. Metsai
 * alexmetsai@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// Librady for reading/writing wav files: adamstark/AudioFile
// TODO: add functionality for adjusting dry/wet ratio (current setting is 100% wet).

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

// Algorithmic Delay/Reverb using a single delay line.
AudioFile<double> delay_reverb(AudioFile<double> audioFile, float delayMilliseconds, double decay){
    
    int delaySamples = int(delayMilliseconds * audioFile.getSampleRate());
    int numChannels = audioFile.getNumChannels();
    int channel;
    
    std::cout << "Delay/Reverb effect using" << "delaySamples: " << 
    delaySamples << " " << audioFile.getSampleRate() << " " << audioFile.getNumSamplesPerChannel() << std::endl;
    
    for (int i = 0; i < audioFile.getNumSamplesPerChannel() - delaySamples; i++){
        for (channel = 0; channel < numChannels; channel ++){
            audioFile.samples[channel][i+delaySamples] += (double)((double)audioFile.samples[channel][i] * decay);
        }
    }
    
    return audioFile;
}
