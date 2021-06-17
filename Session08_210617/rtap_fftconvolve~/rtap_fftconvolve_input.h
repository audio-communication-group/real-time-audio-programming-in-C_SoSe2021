//
//  rtap_fftconvolve_input.h
//  rtap_fftconvolve~
//
//  Created by Harvey Keitel on 17.06.21.
//  Copyright © 2021 Intrinsic Audio. All rights reserved.
//

#ifndef rtap_fftconvolve_input_h
#define rtap_fftconvolve_input_h

#include <stdio.h>
#include "rtap_fftconvolve_filter.h"

typedef struct rtap_fftconvolve_input
{
    int filterSize;
    float *data;
    float *overlap;
    float *signalOut;
    
    kiss_fft_cpx *complexData;
    kiss_fft_cpx *complexOut;
    kiss_fftr_cfg  forwardFFT;
    kiss_fftr_cfg  inverseFFT;
    
} rtap_fftconvolve_input;

rtap_fftconvolve_input *rtap_fftconvolve_input_new(int filterSize);

void rtap_fftconvolve_input_free(rtap_fftconvolve_input *x);

void rtap_fftconvolve_input_perform(rtap_fftconvolve_input *x, float *in, float *out, rtap_fftconvolve_filter *h, int n);

#endif /* rtap_fftconvolve_input_h */
