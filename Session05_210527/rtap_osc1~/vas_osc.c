#include "vas_osc.h"

vas_osc *vas_osc_new(int tableSize)
{
    vas_osc *x = (vas_osc *)malloc(sizeof(vas_osc));
    x->tableSize = tableSize;
    x->lookupTable = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->currentIndex = 0;
    x->frequency = 440;
    
    x->lfoFrequency = 0.1;
    x->currentLfoIndex = 0;
    x->lfoDepth = 10;
    
    float stepSize = (M_PI*2) / (float)tableSize;
    float currentX = 0;
    
    for(int i = 0; i < x->tableSize; i++)
    {
        x->lookupTable[i] = sinf(currentX);
        currentX += stepSize;
    }
 
    return x;
}

void vas_osc_free(vas_osc *x)
{
    vas_mem_free(x->lookupTable);
    free(x);
}

void vas_osc_process(vas_osc *x, float *in, float *out, int vectorSize)
{
    int i = vectorSize;
    float freqOsc;
    
    while(i--)
    {
        int intLfoIndex = floor(x->currentLfoIndex);
        freqOsc = x->lookupTable[intLfoIndex] * x->lfoDepth + x->frequency;
        x->currentLfoIndex += x->lfoFrequency;
        if(x->currentLfoIndex >= x->tableSize)
            x->currentLfoIndex -= x->tableSize;
        
        int intIndex = floor(x->currentIndex);
        *out++ = x->lookupTable[intIndex];
        x->currentIndex += freqOsc;
        
        if(x->currentIndex >= x->tableSize)
            x->currentIndex -= x->tableSize;
    }
}

void vas_osc_setFrequency(vas_osc *x, float frequency)
{
    if(frequency > 0)
        x->frequency = frequency;
}






