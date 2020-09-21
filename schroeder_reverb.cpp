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

// Implemented the more sophisticated reverb algorithm proposed by Manfred Schroeder.
// This approach makes used of Comb and All-Pass filters.

AudioFile<double> combFilter(AudioFile<double> audioFile, double delayMilliseconds = 0.3, double decay = 0.5f);

void allPassFilter();

AudioFile<double> schroeder_reverb(AudioFile<double> audioFile);

int main(){
   
   char *input = NULL;
   int c;
   double mix = 0.5;

   if (argc <= 2){
       std::cout << "You have to specify the wav file that will be processed." << std::endl;
       return -1;
   }

   while((c = getopt(argc, argv, "i:")) != -1)
       switch (c){
           case 'i':
               input = optarg;
               break;
           case '?':
               fprintf(stderr, "Unknown argument -%c .\n", optopt);
               return 1;
           default:
               abort();
       }
    
    // Load wav file
    AudioFile<double> audioFile, effect;
    audioFile.load(input);
    
    // Apply reverb
    // TODO
    
    return 0;
}

AudioFile<double> combFilter(AudioFile<double> audioFile, double delayMilliseconds, double decay){

    // Calculate the number of delay samples and the number of channels.
    int delaySamples = int(delayMilliseconds * (audioFile.getSampleRate()/1000));
    int numChannels = audioFile.getNumChannels();
    int channel;
    
    // See if you need a separate copy of 'audioFile'.
    // temp = pseudocopy audioFile;

    for (int i = 0; i < audioFile.getNumSamplesPerChannel() - delaySamples; i++{
        for (channel = 0; channel < numChannels; channel ++){
            audioFile.samples[channel][i+delaySamples] += (double)((double)audioFile.samples[channel][i] * decay);
        }
    }
    return audioFile;
}
