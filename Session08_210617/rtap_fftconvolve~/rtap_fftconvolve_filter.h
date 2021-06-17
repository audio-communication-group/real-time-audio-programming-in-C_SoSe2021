//
//  rtap_fftconvolve_filter.h
//  rtap_fftconvolve~
//
//  Created by Harvey Keitel on 17.06.21.
//  Copyright © 2021 Intrinsic Audio. All rights reserved.
//

#ifndef rtap_fftconvolve_filter_h
#define rtap_fftconvolve_filter_h

#include <stdio.h>
#include "kissfft/kiss_fft.h"
#include "kissfft/tools/kiss_fftr.h"

typedef struct rtap_fftconvolve_filter
{
    int filterSize;
    float *data;
    kiss_fft_cpx *complexData;
    
    kiss_fftr_cfg  forwardFFT;
    kiss_fftr_cfg  inverseFFT;
    
} rtap_fftconvolve_filter;

rtap_fftconvolve_filter *rtap_fftconvolve_filter_new(int filterSize);

void rtap_fftconvolve_filter_free(rtap_fftconvolve_filter *x);

void rtap_fftconvolve_filter_loadUnitPulse(rtap_fftconvolve_filter *x);

void rtap_fftconvolve_filter_load2DelaysIr(rtap_fftconvolve_filter *x);

void rtap_fftconvolve_filter_calculate(rtap_fftconvolve_filter *x);


#endif /* rtap_fftconvolve_filter_h */
