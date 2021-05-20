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
        x->tap[i].readPointer = x->buffer;
        x->tap[i].readIndex = -1;
        x->tap[i].gain = 1.0;
        x->tap[i].pan = 0.5;
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
    float gainL;
    float gainR;
        
    while(i--)
    {
        x->writePointer[x->writeIndex++] = *in++;
        if(x->writeIndex >= x->bufferSize)
            x->writeIndex = 0;
        
        *outL = 0;
        *outR = 0;
        
        for(int i = 0; i<MAXNUMBEROFTAPS;i++)
        {
            if(x->tap[i].readIndex >= 0)
            {
                gainL = 1-x->tap[i].pan;
                gainR = x->tap[i].pan;
                
                readPointer = x->tap[i].readPointer;
                *outL += readPointer[x->tap[i].readIndex] * x->tap[i].gain * gainL;
                *outR += readPointer[x->tap[i].readIndex] * x->tap[i].gain * gainR;
                x->tap[i].readIndex++;

                if(x->tap[i].readIndex >= x->bufferSize)
                    x->tap[i].readIndex = 0;
            }
        }
        outL++;
        outR++;
    }
}

void vas_delay_setTap(vas_delay *x, int tapNumber, float delayInSamples, float gain, float pan)
{
    if (delayInSamples < 0 || (delayInSamples >= x-> bufferSize) )
        delayInSamples = 0;
    x->tap[tapNumber].readIndex = (x->bufferSize - (int)delayInSamples + x->writeIndex) % x->bufferSize;
    x->tap[tapNumber].gain = gain;
    x->tap[tapNumber].pan = pan;
}






