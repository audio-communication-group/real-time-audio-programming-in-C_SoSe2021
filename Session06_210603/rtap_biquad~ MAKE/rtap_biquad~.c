/**
 * @file rtap_biquad_pd.c
 * @author Thomas Resch <br>
 * Audiocommunication Group, Technical University Berlin <br>
 * University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
 * A gain object for pure data <br>
 * <br>
 * @brief A Pure Data gain object for adjusting the volume<br>
 * <br>
 * rtap_biquad~ allows for adjusting the level<br>
 * of any incoming audio signal. <br>
 * <br>
 */

#include "m_pd.h"
#include "vas_iir_biquad.h"

static t_class *rtap_biquad_tilde_class;

/**
 * @struct rtap_biquad_tilde
 * @brief The Pure Data struct of the rtap_biquad~ object. <br>
 * @var rtap_biquad_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var rtap_biquad_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var rtap_biquad_tilde::gain The gain object for the actual signal processing <br>
 * @var rtap_biquad_tilde::x_out A signal outlet for the adjusted signal
 * level of the incoming signal
 */

typedef struct rtap_biquad_tilde
{
    t_object  x_obj;
    t_sample f;
    vas_iir_biquad *biquad;
    t_outlet *x_out;
} rtap_biquad_tilde;

/**
 * @related rtap_biquad_tilde
 * @brief Calculates the volume adjusted output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the rtap_biquad_perform method. <br>
 * @return A pointer to the signal chain right behind the rtap_biquad_tilde object. <br>
 */

t_int *rtap_biquad_tilde_perform(t_int *w)
{
    rtap_biquad_tilde *x = (rtap_biquad_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);

    vas_iir_biquad_process(x->biquad, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

/**
 * @related rtap_biquad_tilde
 * @brief Adds rtap_biquad_tilde_perform to the signal chain. <br>
 * @param x A pointer the rtap_biquad_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_biquad_tilde_dsp(rtap_biquad_tilde *x, t_signal **sp)
{
    dsp_add(rtap_biquad_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @related rtap_biquad_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the rtap_biquad_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_biquad_tilde_free(rtap_biquad_tilde *x)
{
    outlet_free(x->x_out);
    vas_iir_biquad_free(x->biquad);
}

/**
 * @related rtap_biquad_tilde
 * @brief Creates a new rtap_biquad_tilde object.<br>
 * @param f Sets the initial gain value. <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *rtap_biquad_tilde_new(t_floatarg f)
{
    rtap_biquad_tilde *x = (rtap_biquad_tilde *)pd_new(rtap_biquad_tilde_class);
    
    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x->biquad = vas_iir_biquad_new(VAS_IIR_BIQUAD_LOWPASS, 1000, 10);

    return (void *)x;
}

/**
 * @related rtap_biquad_tilde
 * @brief Sets the gain adjustment parameter. <br>
 * @param x A pointer the rtap_biquad_tilde object <br>
 * @param level Sets the level parameter <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_biquad_tilde_setFrequency(rtap_biquad_tilde *x, float freq)
{
    vas_iir_biquad_setFrequency(x->biquad, freq);
}

/**
 * @related rtap_biquad_tilde
 * @brief Setup of rtap_biquad_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_biquad_tilde_setup(void)
{
      rtap_biquad_tilde_class = class_new(gensym("rtap_biquad~"),
            (t_newmethod)rtap_biquad_tilde_new,
            (t_method)rtap_biquad_tilde_free,
        sizeof(rtap_biquad_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(rtap_biquad_tilde_class, (t_method)rtap_biquad_tilde_dsp, gensym("dsp"), 0);

      // this adds the gain message to our object
      class_addmethod(rtap_biquad_tilde_class, (t_method)rtap_biquad_tilde_setFrequency, gensym("freq"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(rtap_biquad_tilde_class, rtap_biquad_tilde, f);
}
