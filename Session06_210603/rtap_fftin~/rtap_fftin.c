/**
 * @file rtap_fftin.c
 * @author Thomas Resch <br>
 * Audiocommunication Group, Technical University Berlin <br>
 * University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
 * A  better legible forward fft for teaching purposes, not as optimized as Miller's rfft~ object <br
 * <br>
 * @brief A Pure Data gain object for adjusting the volume<br>
 * <br>
 * rtap_delay~ allows for adjusting the level<br>
 * of any incoming audio signal. <br>
 * <br>
 */

#include "m_pd.h"
#include "vas_mem.h"
#include "vas_util.h"

static t_class *rtap_fftin_tilde_class;

/**
 * @struct rtap_fftin_tilde
 * @brief The Pure Data struct of the rtap_fftin~ object. <br>
 * @var rtap_fftin_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var rtap_fftin_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var rtap_fftin_tilde::tmp A tmp float buffer.<br>
 * @var rtap_fftin_tilde::outL  Left signal outlet.<br>
 * @var rtap_fftin_tilde::outR Right signal outlet<br>
 */

typedef struct rtap_fftin_tilde
{
    t_object  x_obj;
    t_sample f;
    
    float *tmp;

    t_outlet *outL; // Holds real part
    t_outlet *outR; // Holds imag part

} rtap_fftin_tilde;

/**
 * @related rtap_fftin_tilde
 * @brief Calculates a real fft <br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the rtap_delay_perform method. <br>
 * @return A pointer to the signal chain right behind the rtap_fftin_tilde object. <br>
 */

t_int *rtap_fftin_tilde_perform(t_int *w)
{
    // a more legible real forward fft than miller's version but of course but not as optimized
    rtap_fftin_tilde *x = (rtap_fftin_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *outL =  (t_sample *)(w[3]);
    t_sample  *outR =  (t_sample *)(w[4]);
    int n =  (int)(w[5]);
    int n2 = (n>>1);        // half frame n2 = n/2
    
    float *tmpPtr = x->tmp; // get tmp ptr to buffer to work with
    // Note: for *in and *outL is often used the same address, because for in-place calculation no data copy in needed, thats why we need to copy the input data to show what happens in this example.   (Miller Puckette does this all in-place: https://github.com/pure-data/pure-data/blob/master/src/d_fft.c)
    
    mayer_realfft(n, in);  // calculates n2+1 real and n2-1 imaginary parts in-place
                           // n = 0 is DC and n = n2 is nyquist frequency
                           // both have no imaginary parts in real fft
    
// a 2^n point real FFT can be reduced to a 2^(n-1) point complex FFT:
//
//    **    mayer_realfft(n,real)
//    **    Does a real-valued fourier transform of "n" points of the
//    **    "real" array.  The real part of the transform ends
//    **    up in the first half of the array and the imaginary part of the
//    **    transform ends up in the second half of the array.
//
// For more information about mayer fft please refer: https://github.com/Venetian/MayerFFT
    
    for (int i = 0; i < n; i++)
        *tmpPtr++ = *in++; // copy input in case in = outL which is usually the case
    
    // Clear memory from possible trash data
    memset(outL+n2+1, 0, (n2-1) * sizeof(float)); // set everything else to zero
    memset(outR, 0, sizeof(float));               // bin 0 is DC which has no imaginary part
    memset(outR+n2-1, 0, (n2+1) * sizeof(float)); // bin n2 is nyquist frequency which has no imaginary part
  
    float *realPtr = x->tmp;
    float *imagPtr = x->tmp+n-1; // Imag part is written backwards, so we start at the end
    
    for (int i = 0; i < n2+1; i++) // copying real part to outL
        *outL++ = *realPtr++;
    
    outR++; // bin 0 is DC which has no imaginary part
    
    for (int i = 0; i < n2-1; i++) // copying imag part to outR
        *outR++ = *imagPtr--;

    //last bin is nyquist freq which has also no imaginary part

    return (w+6);
}

/**
 * @related rtap_fftin_tilde
 * @brief Adds rtap_fftin_tilde_perform to the signal chain. <br>
 * @param x A pointer the rtap_fftin_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_fftin_tilde_dsp(rtap_fftin_tilde *x, t_signal **sp)
{
    dsp_add(rtap_fftin_tilde_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
    post("Current Vector Size: %d", sp[0]->s_n);
}

/**
 * @related rtap_fftin_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the rtap_fftin_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_fftin_tilde_free(rtap_fftin_tilde *x)
{
    outlet_free(x->outL);
    outlet_free(x->outR);
    vas_mem_free(x->tmp);
}

/**
 * @related rtap_fftin_tilde
 * @brief Creates a new rtap_fftin_tilde object.<br>
 * @param f dummy variable <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *rtap_fftin_tilde_new(t_floatarg f)
{
    rtap_fftin_tilde *x = (rtap_fftin_tilde *)pd_new(rtap_fftin_tilde_class);

    x->tmp = vas_mem_alloc(sizeof(float) * MAXFFTSIZE);
    
    //The main inlet is created automatically
    x->outL = outlet_new(&x->x_obj, &s_signal);
    x->outR = outlet_new(&x->x_obj, &s_signal);
    return (void *)x;
}

/**
 * @related rtap_fftin_tilde
 * @brief Setup of rtap_fftin_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_fftin_tilde_setup(void)
{
      rtap_fftin_tilde_class = class_new(gensym("rtap_fftin~"),
            (t_newmethod)rtap_fftin_tilde_new,
            (t_method)rtap_fftin_tilde_free,
        sizeof(rtap_fftin_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(rtap_fftin_tilde_class, (t_method)rtap_fftin_tilde_dsp, gensym("dsp"), 0);

      
      // declares, that the class will use signal-inlets
      CLASS_MAINSIGNALIN(rtap_fftin_tilde_class, rtap_fftin_tilde, f);
}
