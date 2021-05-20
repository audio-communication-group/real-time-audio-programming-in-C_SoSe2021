#include "vas_delay.h"

vas_delay *vas_delay_new(int bufferSize)
{
    vas_delay *x = (vas_delay *)malloc(sizeof(vas_delay));
    x->bufferSize = bufferSize;
    x->buffer = (float *) vas_mem_alloc(x-> bufferSize * sizeof(float));
    x->writePointer = x->buffer;
    x->writeIndex = 0;
    
    for(int i = 0; i<MAXNUMBEROFTAPS;i++)
    {
        x->readPointer[i] = x->buffer;
        x->readIndex[i] = -1;
        x->gain[i] = 0.5;
    }
    
    return x;
}

void vas_delay_free(vas_delay *x)
{
    vas_mem_free(x->buffer);
    free(x);
}

void vas_delay_process(vas_delay *x, float *in, float *outL, float *outR, int vectorSize)
{
    int i = vectorSize;
    float *readPointer;
    
    while(i--)
    {
        x->writePointer[x->writeIndex++] = *in++;
        if(x->writeIndex >= x->bufferSize)
            x->writeIndex = 0;
        
        *outL = 0;
        *outR = 0;
        
        for(int i = 0; i<MAXNUMBEROFTAPS;i++)
        {
            if(x->readIndex[i] >= 0)
            {
                readPointer = x->readPointer[i];
                *outL += readPointer[x->readIndex[i]] * x->gain[i];
                *outR += readPointer[x->readIndex[i]] * x->gain[i];
                x->readIndex[i]++;

                if(x->readIndex[i] >= x->bufferSize)
                    x->readIndex[i] = 0;
            }
        }
        outL++;
        outR++;
    }
}

void vas_delay_setTap(vas_delay *x, int tapNumber, float delayInSamples, float gain)
{
    if (delayInSamples < 0 || (delayInSamples >= x-> bufferSize) )
        delayInSamples = 0;
    x->readIndex[tapNumber] = (x->bufferSize - (int)delayInSamples + x->writeIndex) % x->bufferSize;
    x->gain[tapNumber] = gain;
}






