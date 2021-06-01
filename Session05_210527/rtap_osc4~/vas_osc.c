#include "vas_osc.h"

vas_osc *vas_osc_new(int tableSize)
{
    vas_osc *x = (vas_osc *)malloc(sizeof(vas_osc));
    x->tableSize = tableSize;
    x->lookupTable = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->envelopeTable = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->currentIndex = 0;
    x->frequency = 440;
    x->envelopeIndex = 0;
    x->numberOfHarmonics = 10;
    
    for(int i = 0; i < 10; i ++)
    {
        x->harmonicGain[i] = 1 / (i + 1);
        x->harmonicIndex[i] = 0;
    }
    
    float stepSize = (M_PI*2) / (float)tableSize;
    float currentX = 0;
    
    for(int i = 0; i < x->tableSize; i++)
    {
        x->lookupTable[i] = sinf(currentX);
        x->envelopeTable[i] = 1;
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
    
    while(i--)
    {
        int intIndex = floor(x->currentIndex);
        *out = x->lookupTable[intIndex];
        x->currentIndex += x->frequency;
        
        if(x->currentIndex >= x->tableSize)
            x->currentIndex -= x->tableSize;
        
        for(int i = 0; i < 10; i++)
        {
            float harmonicFreq = x->frequency * (i+2);
            intIndex = floor(x->harmonicIndex[i]);
            *out += x->lookupTable[intIndex] * x->harmonicGain[i];
            x->harmonicIndex[i] += harmonicFreq;
            
            if(x->harmonicIndex[i] >= x->tableSize)
                x->harmonicIndex[i] -= x->tableSize;
        }
        
        *out *= x->envelopeTable[x->envelopeIndex++];
        if(x->envelopeIndex >= x->tableSize)
            x->envelopeIndex = 0;
        
        out++;
    }
}

void vas_osc_setFrequency(vas_osc *x, float frequency)
{
    if(frequency > 0)
        x->frequency = frequency;
}






