#include "vas_delay.h"

vas_delay *vas_delay_new(int bufferSize)
{
    vas_delay *x = (vas_delay *)malloc(sizeof(vas_delay));
    x->bufferSize = bufferSize;
    x->buffer = (float *) vas_mem_alloc(x-> bufferSize * sizeof(float));
    x->writePointer = x->buffer;
    x->readPointer1 = x->buffer;
    x->readPointer2 = x->buffer;
    x->readIndex1 = 0;
    x->readIndex2 = 0;
    x->writeIndex = 0;
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
    
    while(i--)
    {
        x->writePointer[x->writeIndex++] = *in++;
        if(x->writeIndex >= x->bufferSize)
            x->writeIndex = 0;
        
        *outL++ = x->readPointer1[x->readIndex1++];
        if(x->readIndex1 >= x->bufferSize)
            x->readIndex1 = 0;
        
        *outR++ = x->readPointer2[x->readIndex2++];
        if(x->readIndex2 >= x->bufferSize)
            x->readIndex2 = 0;
    }
}

void vas_delay_setTap1(vas_delay *x, float delayInSamples)
{
    if (delayInSamples < 0 || (delayInSamples >= x-> bufferSize) )
        delayInSamples = 0;
    x->readIndex1 = (x->bufferSize - (int)delayInSamples + x->writeIndex) % x->bufferSize;
}

void vas_delay_setTap2(vas_delay *x, float delayInSamples)
{
    if (delayInSamples < 0 || (delayInSamples >= x-> bufferSize) )
        delayInSamples = 0;
    x->readIndex2 = (x->bufferSize - (int)delayInSamples + x->writeIndex) % x->bufferSize;
}




