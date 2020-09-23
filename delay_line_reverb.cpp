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

#include <vector>
#include <iostream>
#include <string>
#include "AudioFile.h"
#include <cstring>
#include <unistd.h>

AudioFile<double> delay_reverb(AudioFile<double> audioFile, float delayMilliseconds, double decay);

int main(int argc, char **argv){
    
    char *input = NULL;
    char *output = NULL;
    int c;
    
    // Default values for delay-ms, decay and dry/wet mix.
    float delayMilliseconds = 300;
    double decay = 0.5;
    double mix = 0.5;
    
    if (argc <= 2){
        std::cout << "Delay line Reverb. Input filename is required.\n"
	             "Options are:\n"
		     "    -i: input audio filename\n"
		     "    -t: Delay Milliseconds (default: 300)\n"
		     "    -d: Decay value        (default: 0.5)\n"
		     "    -m: Dry/Wet mix ratio  (default: 0.5)\n"
		     "    -o: output filename    (default: output.wav)\n";
        return -1;
    }

    while((c = getopt(argc, argv, "i:t:d:m:o:")) != -1)
       switch (c){
           case 'i':
               input = optarg;
               continue;
	   case 't':
	       std::cout<<optarg;
	       delayMilliseconds = std::stof(optarg);
	       continue;
	   case 'd':
	       decay = std::stod(optarg);
	       continue;
	   case 'm':
	       mix = std::stod(optarg);
	       continue;
	   case 'o':
	       output = optarg;
	       continue;
           case '?':
               fprintf(stderr, "Unknown argument -%c .\n", optopt);
               return 1;
           default:
               abort();
       }
       
    if (input == NULL){
        std::cout << "You have to specify the wav file that will be processed." << std::endl;
        return -1;
    }
    if (output == NULL){
        output = new char[10];
	std::strcpy(output, "output.wav");
    }

    // Load wav file
    AudioFile<double> audioFile, effect;
    audioFile.load(input);
    
    // Apply Reverb effect.
    effect = delay_reverb(audioFile, delayMilliseconds, decay);
    
    // Adjust Dry/Wet mix.
    for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++){
        for (int channel = 0; channel < audioFile.getNumChannels(); channel++){
            audioFile.samples[channel][i] += (1 - mix) * audioFile.samples[channel][i] + mix * effect.samples[channel][i];
		}
    }
    
    // I encountered distortion / audio-cliiping on pure-tone waves, especially for pure sine waves.
    // This happens because some values, due to the added delay, exceed the accepted range of [-1, 1].
    // A simple way to tackle this is multiplying all values with (1 / max_val), where max_val is the largest sample.
    for (int channel = 0; channel < audioFile.getNumChannels(); channel++){
        double max_val = audioFile.samples[channel][0];

        for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++)
           if (abs(audioFile.samples[channel][i]) > max_val) max_val = abs(audioFile.samples[channel][i]);

        for (int i = 0; i < audioFile.getNumSamplesPerChannel(); i++)
            audioFile.samples[channel][i] =  audioFile.samples[channel][i] * (1 / max_val);
    }
    
    // Save output to file.
    audioFile.save(output);
    
    return 0;
}

// Algorithmic Delay/Reverb using a single delay line.
AudioFile<double> delay_reverb(AudioFile<double> audioFile, float delayMilliseconds, double decay){
    
    int delaySamples = int(delayMilliseconds * audioFile.getSampleRate() / 1000);
    int numChannels = audioFile.getNumChannels();
    int channel;
    
    std::cout << "Delay/Reverb effect using " << "delaySamples: " << 
    delaySamples << " " << audioFile.getSampleRate() << " " << audioFile.getNumSamplesPerChannel() << std::endl;
    
    for (int i = 0; i < audioFile.getNumSamplesPerChannel() - delaySamples; i++){
        for (channel = 0; channel < numChannels; channel ++){
            audioFile.samples[channel][i+delaySamples] += (double)((double)audioFile.samples[channel][i] * decay);
        }
    }
    
    return audioFile;
}
