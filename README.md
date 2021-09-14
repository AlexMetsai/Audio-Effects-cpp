# Audio-Effects-cpp

Implementations of audio effects using C++. 

This code relies on the header file provided by [AdamStark](https://github.com/adamstark/AudioFile) for wav audio I/O, which has been slightly modified to include cstring.

## Compile with:
```shell
g++ delay_line_reverb.cpp -std=c++11
```

## Example run:
```shell
./a.out -i input.wav
```

## Arguments:
```
-i: input audio filename  
-t: Delay Milliseconds  (default: 300)  
-d: Decay value         (default: 0.5)  
-m: Dry/Wet mix ratio   (default: 0.5)  
-o: output filename     (default: output.wav)  
```
