#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"

double rect(double t);

int main(int argv, char **argc)
{
    MONO_PCM pcmForWrite, pcmForRead, pcm;
    int i;
    double amplitude, frequency;

    pcmForWrite.fs = 8000;
    pcmForWrite.bits = 16;
    pcmForWrite.length = 8000;
    pcmForWrite.s = (double *)calloc(pcmForWrite.length, sizeof(double));

    amplitude = 0.25;
    frequency = 400.0;

    for(i = 0; i < pcmForWrite.length; i++)
    {
        pcmForWrite.s[i] = amplitude * sin((2.0 * M_PI * frequency * i) / pcmForWrite.fs);
        // A sin(2πft0/fs) + A/2 sine(2πft1/fs) ・・・
    }
    monoWaveWrite(&pcmForWrite, "testWave.wav");
    free(pcmForWrite.s);

    monoWaveRead(&pcmForRead, "testWave.wav");
    for(i = 0; i < pcmForRead.length; i++)
    {
        // printf("%d:%lf\n", i, pcmForRead.s[i]);
	}

	monoWaveRead(&pcm, "sound_research.wav");
	printf("%d, %d\n", pcm.fs, pcm.length);

    free(pcmForRead.s);
    free(pcm.s);

    return 0;
}

double rect(double t) {
	int N = 10000;
	double v = 0;
	for (int i = 0; i < N; i++)
	{
		int odd = 2*i - 1;
		v += (1.0/odd) * sin(odd * t);
	}
	return v;
}