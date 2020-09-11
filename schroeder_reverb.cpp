// Implemented the more sophisticated reverb algorithm proposed by Manfred Schroeder.
// This approach makes used of Comb and All-Pass filters.

void combFilter();

void allPassFilter();

AudioFile<double> schroeder_reverb(AudioFile<double> audioFile);

int main(){
    return 0;
}
