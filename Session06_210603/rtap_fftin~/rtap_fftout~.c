/**
* @file rtap_fftout.c
* @author Thomas Resch <br>
* Audiocommunication Group, Technical University Berlin <br>
* University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
* A  better legible inverse fft for teaching purposes, not as optimized as Miller's irfft~ object <br
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

static t_class *rtap_fftout_tilde_class;

/**
 * @struct rtap_fftout_tilde
 * @brief The Pure Data struct of the rtap_delay~ object. <br>
 * @var rtap_fftout_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var rtap_fftout_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * @var rtap_fftin_tilde::tmp A tmp float buffer.<br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var rtap_fftout_tilde::inR Right inlet for imaginary input <br>
 * @var rtap_fftout_tilde::outtL Outlet for time domain signal.
 */

typedef struct rtap_fftout_tilde
{
    t_object  x_obj;
    t_sample f;
    
    float *tmp;

    t_inlet *inR;
    t_outlet *outL;
    

} rtap_fftout_tilde;

/**
 * @related rtap_fftout_tilde
 * @brief Calculates the volume adjusted output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the rtap_delay_perform method. <br>
 * @return A pointer to the signal chain right behind the rtap_fftout_tilde object. <br>
 */

t_int *rtap_fftout_tilde_perform(t_int *w)
{
    // a more legible real inverse fft than miller's version but of course but not as optimized
    rtap_fftout_tilde *x = (rtap_fftout_tilde *)(w[1]);
    t_sample  *inL = (t_sample *)(w[2]);
    t_sample  *inR =  (t_sample *)(w[3]);
    t_sample  *out =  (t_sample *)(w[4]);
    int n =  (int)(w[5]);
    int n2 = (n>>1);
    
    float *tmpPtr = x->tmp; // copying real part to tmp
    for (int i = 0; i < n2+1; i++)
        *tmpPtr++ = *inL++;
    
    inR += n2-1;  // move right inlet vector pointer to the end, because the mayer_realifft()
                 // needs the imag part written backwards
    for (int i = 0; i < n2-1; i++)
        *tmpPtr++ = *inR--; // copying imag part backwards to tmp
    
    mayer_realifft(n, x->tmp);  // calculating ifft
    // For more information about mayer fft please refer: https://github.com/Venetian/MayerFFT
                         
    tmpPtr = x->tmp;
    for (int i = 0; i < n; i++) // copying tmp to out
        *out++ = *tmpPtr++;

    return (w+6);
}

/**
 * @related rtap_fftout_tilde
 * @brief Adds rtap_fftout_tilde_perform to the signal chain. <br>
 * @param x A pointer the rtap_fftout_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_fftout_tilde_dsp(rtap_fftout_tilde *x, t_signal **sp)
{
    dsp_add(rtap_fftout_tilde_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
    post("Current Vector Size: %d", sp[0]->s_n);
}

/**
 * @related rtap_fftout_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the rtap_fftout_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_fftout_tilde_free(rtap_fftout_tilde *x)
{
    outlet_free(x->outL);
    inlet_free(x->inR);
    vas_mem_free(x->tmp);
}

/**
 * @related rtap_fftout_tilde
 * @brief Creates a new rtap_fftout_tilde object.<br>
 * @param f Sets the initial gain value. <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *rtap_fftout_tilde_new(t_floatarg f)
{
    rtap_fftout_tilde *x = (rtap_fftout_tilde *)pd_new(rtap_fftout_tilde_class);
    // The main inlet is created automatically
    
    x->tmp = vas_mem_alloc(sizeof(float) * MAXFFTSIZE);
    x->inR = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    
    x->outL = outlet_new(&x->x_obj, &s_signal);
    return (void *)x;
}

/**
 * @related rtap_fftout_tilde
 * @brief Setup of rtap_fftout_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_fftout_tilde_setup(void)
{
      rtap_fftout_tilde_class = class_new(gensym("rtap_fftout~"),
            (t_newmethod)rtap_fftout_tilde_new,
            (t_method)rtap_fftout_tilde_free,
        sizeof(rtap_fftout_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(rtap_fftout_tilde_class, (t_method)rtap_fftout_tilde_dsp, gensym("dsp"), 0);

      // declares, that the class will use signal-inlets
      CLASS_MAINSIGNALIN(rtap_fftout_tilde_class, rtap_fftout_tilde, f);
}
