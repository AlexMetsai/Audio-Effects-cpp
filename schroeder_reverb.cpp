// Implemented the more sophisticated reverb algorithm proposed by Manfred Schroeder.
// This approach makes used of Comb and All-Pass filters.

AudioFile<double> combFilter(AudioFile<double> audioFile, double delayMilliseconds, double decay);

void allPassFilter();

AudioFile<double> schroeder_reverb(AudioFile<double> audioFile);

int main(){
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
