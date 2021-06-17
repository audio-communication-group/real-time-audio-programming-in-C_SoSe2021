//
//  rtap_fftconvolve_filter.c
//  rtap_fftconvolve~
//
//  Created by Harvey Keitel on 17.06.21.
//  Copyright © 2021 Intrinsic Audio. All rights reserved.
//

#include "rtap_fftconvolve_filter.h"
#include "m_pd.h"
#include "vas_mem.h"
#include "math.h"

rtap_fftconvolve_filter *rtap_fftconvolve_filter_new(int filterSize)
{
    rtap_fftconvolve_filter *x = vas_mem_alloc(sizeof(rtap_fftconvolve_filter));
    x->filterSize = filterSize;
    x->data = vas_mem_alloc( sizeof(float) * filterSize * 2);
    
    post("FilterSize: %d", x->filterSize);

    x->complexData = vas_mem_alloc((filterSize * 2 +1) * sizeof(kiss_fft_cpx));
    x->forwardFFT = kiss_fftr_alloc(x->filterSize*2,0,0,0);
    x->inverseFFT = kiss_fftr_alloc(x->filterSize*2,1,0,0);
    
    return x;
}

void rtap_fftconvolve_filter_loadUnitPulse(rtap_fftconvolve_filter *x)
{
    x->data[0] = 1.0f;
    for(int i=1; i<x->filterSize*2; i++)
        x->data[i] = 0;
}

void rtap_fftconvolve_filter_calculate(rtap_fftconvolve_filter *x)
{
    kiss_fftr(x->forwardFFT, x->data, x->complexData);
}

void rtap_fftconvolve_filter_free(rtap_fftconvolve_filter *x)
{
   // ...
}
