#include "vas_delay.h"

vas_delay *vas_delay_new(int bufferSize)
{
    vas_delay *x = (vas_delay *)malloc(sizeof(vas_delay));
    x->bufferSize = bufferSize;
    x->bufferL = (float *) vas_mem_alloc(x-> bufferSize * sizeof(float));
    x->bufferR = (float *) vas_mem_alloc(x-> bufferSize * sizeof(float));
    x->writePointerL = x->bufferL;
    x->writePointerR = x->bufferR;
    x->writeIndex = 0;
    
    x->tap.readPointer = x->bufferL;
    x->tap.readIndex = -1;
    x->tap.gain = 1.0;
    x->tap.pan = 0.5;
    
    
    return x;
}

void vas_delay_free(vas_delay *x)
{
    vas_mem_free(x->bufferL);
    free(x);
}


void vas_delay_process(vas_delay *x, float *inL, float *inR, float *outL, float *outR, int vectorSize)
{
    int i = vectorSize;
    float *readPointer;
    float gainL;
    float gainR;
        
    while (i--)
    {
        x->writePointerL[x->writeIndex] = *inL++;
        x->writePointerR[x->writeIndex] = *inR++; // second inlet is not in use yet
        x->writeIndex++;
        
        if(x->writeIndex >= x->bufferSize)
            x->writeIndex = 0;
        
        *outL = 0;
        *outR = 0;
        
        if (x->tap.readIndex >= 0)
        {
            gainL = 1.0 - x->tap.pan;
            gainR = x->tap.pan;
            
            readPointer = x->tap.readPointer;
            *outL += readPointer[x->tap.readIndex] * x->tap.gain * gainL;
            *outR += readPointer[x->tap.readIndex] * x->tap.gain * gainR;
            x->tap.readIndex++;

            if(x->tap.readIndex >= x->bufferSize)
                x->tap.readIndex = 0;
        }
        outL++;
        outR++;
    }
}


void vas_delay_setTap(vas_delay *x, float delayInSamples, float gain, float pan)
{
    if (delayInSamples < 0 || (delayInSamples >= x-> bufferSize) )
        delayInSamples = 0;
    x->tap.readIndex = (x->bufferSize - (int)delayInSamples + x->writeIndex) % x->bufferSize;
    x->tap.gain = gain;
    x->tap.pan = pan;
}




