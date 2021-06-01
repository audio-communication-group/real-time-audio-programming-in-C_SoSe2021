#include "vas_osc.h"

vas_osc *vas_osc_new(int tableSize)
{
    vas_osc *x = (vas_osc *)malloc(sizeof(vas_osc));
    x->tableSize = tableSize;
    x->lookupTable = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->envelopeTable = (float *) vas_mem_alloc(x-> tableSize * sizeof(float));
    x->frequency = 440;
    
    for(int i = 0;  i < MAXNUMBEROFVOICES; i++)
    {
        x->voice[i].frequency = 440;
        x->voice[i].index = 0;
        x->voice[i].envelopeIndex = 0;
        x->voice[i].velocity = 0.7;
        x->voice[i].occupied = 0;
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

void vas_osc_noteOn(vas_osc *x, float frequency, float velocity)
{
    for(int i = 0; i < MAXNUMBEROFVOICES; i++)
    {
        if(!x->voice[i].occupied)
        {
            x->voice[i].occupied = 1;
            x->voice[i].frequency = frequency;
            x->voice[i].velocity = velocity;
            x->voice[i].envelopeIndex = 0;
            x->voice[i].index = 0;
            break;
        }
    }
}

void vas_osc_process(vas_osc *x, float *in, float *out, int vectorSize)
{
    int i = vectorSize;
    float voiceSample = 0;
    
    while(i--)
    {
        *out = 0;
        for(int j = 0; j < MAXNUMBEROFVOICES; j++)
        {
            if(x->voice[j].occupied)
            {
                voiceSample = 0;
                int intIndex = floor(x->voice[j].index);
                voiceSample += x->lookupTable[intIndex];
                x->voice[j].index += x->voice[j].frequency;
                       
                if(x->voice[j].index >= x->tableSize)
                    x->voice[j].index -= x->tableSize;
                
                voiceSample *= x->voice[j].velocity;
                voiceSample *= x->envelopeTable[x->voice[j].envelopeIndex++];
                
                if(x->voice[j].envelopeIndex >= x->tableSize)
                    x->voice[j].occupied = 0;
                
                *out += voiceSample;
            }
        }
        out++;
    }
}






