// Implemented the more sophisticated reverb algorithm proposed by Manfred Schroeder.
// This approach makes used of Comb and All-Pass filters.

AudioFile<double> combFilter(AudioFile<double> audioFile, double delayMilliseconds, double decay);

void allPassFilter();

AudioFile<double> schroeder_reverb(AudioFile<double> audioFile);

int main(){
    return 0;
}

AudioFile<double> combFilter(AudioFile<double> audioFile, double delayMilliseconds, double decay){

    // Calculate the number of delay samples.
    int delaySamples = int(delayMilliseconds * (audioFile.getSampleRate()/1000));

    // See if you need a separate copy of 'audioFile'.
    // temp = pseudocopy audioFile;

    for (int i = 0; i < audioFile.getNumSamplesPerChannel() - delaySamples; i++{
        audioFile.samples[0][i+delaySamples] += (double)((double)audioFile.samples[0][i] * decay);
        // DO THIS FOR ALL CHANNELS THAT THE WAV FILE PROVIDES.
    }
    return audioFile;
}
