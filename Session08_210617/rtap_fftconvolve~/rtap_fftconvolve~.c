/**
 * @file rtap_fftconvolve.c
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
#include "rtap_fftconvolve_filter.h"
#include "rtap_fftconvolve_input.h"

static t_class *rtap_fftconvolve_tilde_class;

/**
 * @struct rtap_fftconvolve_tilde
 * @brief The Pure Data struct of the rtap_fftconvolve~ object. <br>
 * @var rtap_fftconvolve_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var rtap_fftconvolve_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var rtap_fftconvolve_tilde::tmp A tmp float buffer.<br>
 * @var rtap_fftconvolve_tilde::outL  Left signal outlet.<br>
 * @var rtap_fftconvolve_tilde::outR Right signal outlet<br>
 */

typedef struct rtap_fftconvolve_tilde
{
    t_object  x_obj;
    t_sample f;
    rtap_fftconvolve_filter *filter;
    rtap_fftconvolve_input *input;

    t_outlet *out; // Holds real part

} rtap_fftconvolve_tilde;

/**
 * @related rtap_fftconvolve_tilde
 * @brief Calculates a real fft <br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the rtap_delay_perform method. <br>
 * @return A pointer to the signal chain right behind the rtap_fftconvolve_tilde object. <br>
 */

t_int *rtap_fftconvolve_tilde_perform(t_int *w)
{
    rtap_fftconvolve_tilde *x = (rtap_fftconvolve_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);
    rtap_fftconvolve_input_perform(x->input, in, out, x->filter, n);
    return (w+5);
}

/**
 * @related rtap_fftconvolve_tilde
 * @brief Adds rtap_fftconvolve_tilde_perform to the signal chain. <br>
 * @param x A pointer the rtap_fftconvolve_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_fftconvolve_tilde_dsp(rtap_fftconvolve_tilde *x, t_signal **sp)
{
    dsp_add(rtap_fftconvolve_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
    post("Current Vector Size: %d", sp[0]->s_n);
}

/**
 * @related rtap_fftconvolve_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the rtap_fftconvolve_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_fftconvolve_tilde_free(rtap_fftconvolve_tilde *x)
{
    outlet_free(x->out);
}

/**
 * @related rtap_fftconvolve_tilde
 * @brief Creates a new rtap_fftconvolve_tilde object.<br>
 * @param f dummy variable <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *rtap_fftconvolve_tilde_new(t_floatarg f)
{
    rtap_fftconvolve_tilde *x = (rtap_fftconvolve_tilde *)pd_new(rtap_fftconvolve_tilde_class);
    x->filter = rtap_fftconvolve_filter_new(64);
    x->input = rtap_fftconvolve_input_new(64);
    x->out = outlet_new(&x->x_obj, &s_signal);
    return (void *)x;
}

void rtap_fftconvolve_tilde_loadFilter(rtap_fftconvolve_tilde *x)
{
    rtap_fftconvolve_filter_loadUnitPulse(x->filter);
    rtap_fftconvolve_filter_calculate(x->filter);
    post("Load Filter");
}

/**
 * @related rtap_fftconvolve_tilde
 * @brief Setup of rtap_fftconvolve_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_fftconvolve_tilde_setup(void)
{
      rtap_fftconvolve_tilde_class = class_new(gensym("rtap_fftconvolve~"),
            (t_newmethod)rtap_fftconvolve_tilde_new,
            (t_method)rtap_fftconvolve_tilde_free,
        sizeof(rtap_fftconvolve_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(rtap_fftconvolve_tilde_class, (t_method)rtap_fftconvolve_tilde_dsp, gensym("dsp"), 0);
      class_addmethod(rtap_fftconvolve_tilde_class, (t_method)rtap_fftconvolve_tilde_loadFilter, gensym("loadfilter"), 0);

      
      // declares, that the class will use signal-inlets
      CLASS_MAINSIGNALIN(rtap_fftconvolve_tilde_class, rtap_fftconvolve_tilde, f);
}
