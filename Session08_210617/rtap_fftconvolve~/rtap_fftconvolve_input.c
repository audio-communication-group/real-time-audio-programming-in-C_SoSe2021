//
//  rtap_fftconvolve_input.c
//  rtap_fftconvolve~
//
//  Created by Harvey Keitel on 17.06.21.
//  Copyright © 2021 Intrinsic Audio. All rights reserved.
//

#include "rtap_fftconvolve_input.h"
#include "vas_mem.h"

rtap_fftconvolve_input *rtap_fftconvolve_input_new(int filterSize)
{
    rtap_fftconvolve_input *x = vas_mem_alloc(sizeof(rtap_fftconvolve_input));
    x->filterSize = filterSize;
    x->data = vas_mem_alloc( sizeof(float) * (filterSize * 2 + 1));
    x->overlap = vas_mem_alloc( sizeof(float) * filterSize );
    x->signalOut = vas_mem_alloc( sizeof(float) * filterSize * 2 +1);
    
    for(int i = x->filterSize; i<x->filterSize; i++)
        x->overlap[i] = 0;
    
    x->complexData = vas_mem_alloc((filterSize*2) * sizeof(kiss_fft_cpx));
    x->complexOut = vas_mem_alloc((filterSize*2) * sizeof(kiss_fft_cpx));
    x->forwardFFT = kiss_fftr_alloc(x->filterSize*2,0,0,0);
    x->inverseFFT = kiss_fftr_alloc(x->filterSize*2,1,0,0);
    
    return x;
}

void rtap_fftconvolve_complexMultiply(int length, kiss_fft_cpx *signalIn, kiss_fft_cpx *filter, kiss_fft_cpx *dest)
{
    int n = length;
    while (n--)
    {
        dest->r = filter->r * signalIn->r - filter->i * signalIn->i;
        dest->i = filter->r * signalIn->i + filter->i * signalIn->r;
        dest++;filter++;signalIn++;
    }
}

void rtap_fftconvolve_input_perform(rtap_fftconvolve_input *x, float *in, float *out, rtap_fftconvolve_filter *h, int n)
{
    float *dataPtr;
    
    for(int i= 0; i<n; i++)
        x->data[i] = *in++;
    
    for(int i = x->filterSize; i<n+1; i++)
        x->data[i] = 0;
    
    kiss_fftr(x->forwardFFT, x->data, x->complexData);
     
    rtap_fftconvolve_complexMultiply(x->filterSize, x->complexData, h->complexData, x->complexOut);

    kiss_fftri(x->inverseFFT, x->complexOut, x->signalOut);

    dataPtr = x->signalOut;
    float *overlapPtr = x->overlap;

    for(int i = 0; i < n; i++)
        *out++ = (*dataPtr++ + *overlapPtr++) * (1.0f / (x->filterSize*2));

    overlapPtr = x->overlap;
    dataPtr = x->data + n;

    for(int i = 0; i < n; i++)
        *overlapPtr++ = *dataPtr++;
}
