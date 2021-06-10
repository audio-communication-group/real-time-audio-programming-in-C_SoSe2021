#include "vas_delay.h"

vas_delay *vas_delay_new(int bufferSize)
{
    vas_delay *x = (vas_delay *)malloc(sizeof(vas_delay));
    x->bufferSize = bufferSize;
    x->buffer = (float *) vas_mem_alloc(x-> bufferSize * sizeof(float));
    x->writePointer = x->buffer;
    x->readPointer = x->buffer;
    x->readIndex = 0;
    x->writeIndex = 0;
    return x;
}

void vas_delay_free(vas_delay *x)
{
    vas_mem_free(x->buffer);
    free(x);
}

void vas_delay_process(vas_delay *x, float *in, float *out, int vectorSize)
{
    int i = vectorSize;
    
    while(i--)
    {
        x->writePointer[x->writeIndex++] = *in++;
        if(x->writeIndex >= x->bufferSize)
            x->writeIndex = 0;
        
        *out++ = x->readPointer[x->readIndex++];
        if(x->readIndex >= x->bufferSize)
            x->readIndex = 0;
    }
}


void vas_delay_processAddInPlace(vas_delay *x, float *in, float *out, int vectorSize)
{
    int i = vectorSize;
    
    while(i--)
    {
        x->writePointer[x->writeIndex++] = *in++;
        if(x->writeIndex >= x->bufferSize)
            x->writeIndex = 0;
       
        *out++ += x->readPointer[x->readIndex++]; // <——— statt = einfach +=
        if(x->readIndex >= x->bufferSize)
            x->readIndex = 0;
    }
}


void vas_delay_setDelayTime(vas_delay *x, float delayInSamples)
{
    if (delayInSamples < 0 || (delayInSamples >= x-> bufferSize) )
        delayInSamples = 0;
    x->readIndex = (x->bufferSize - (int)delayInSamples + x->writeIndex) % x->bufferSize;
}



