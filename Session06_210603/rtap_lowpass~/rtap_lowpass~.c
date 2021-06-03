/**
 * @file rtap_lowpass_pd.c
 * @author Thomas Resch <br>
 * Audiocommunication Group, Technical University Berlin <br>
 * University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
 * A gain object for pure data <br>
 * <br>
 * @brief A Pure Data gain object for adjusting the volume<br>
 * <br>
 * rtap_lowpass~ allows for adjusting the level<br>
 * of any incoming audio signal. <br>
 * <br>
 */

#include "m_pd.h"
#include "vas_iir_lowpass.h"

static t_class *rtap_lowpass_tilde_class;

/**
 * @struct rtap_lowpass_tilde
 * @brief The Pure Data struct of the rtap_lowpass~ object. <br>
 * @var rtap_lowpass_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var rtap_lowpass_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var rtap_lowpass_tilde::gain The gain object for the actual signal processing <br>
 * @var rtap_lowpass_tilde::x_out A signal outlet for the adjusted signal
 * level of the incoming signal
 */

typedef struct rtap_lowpass_tilde
{
    t_object  x_obj;
    t_sample f;
    vas_iir_lowpass *lowpass;
    t_outlet *x_out;
} rtap_lowpass_tilde;

/**
 * @related rtap_lowpass_tilde
 * @brief Calculates the volume adjusted output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the rtap_lowpass_perform method. <br>
 * @return A pointer to the signal chain right behind the rtap_lowpass_tilde object. <br>
 */

t_int *rtap_lowpass_tilde_perform(t_int *w)
{
    rtap_lowpass_tilde *x = (rtap_lowpass_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);

    vas_iir_lowpass_process(x->lowpass, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

/**
 * @related rtap_lowpass_tilde
 * @brief Adds rtap_lowpass_tilde_perform to the signal chain. <br>
 * @param x A pointer the rtap_lowpass_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_lowpass_tilde_dsp(rtap_lowpass_tilde *x, t_signal **sp)
{
    dsp_add(rtap_lowpass_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @related rtap_lowpass_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the rtap_lowpass_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_lowpass_tilde_free(rtap_lowpass_tilde *x)
{
    outlet_free(x->x_out);
    vas_iir_lowpass_free(x->lowpass);
}

/**
 * @related rtap_lowpass_tilde
 * @brief Creates a new rtap_lowpass_tilde object.<br>
 * @param f Sets the initial gain value. <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *rtap_lowpass_tilde_new(t_floatarg f)
{
    rtap_lowpass_tilde *x = (rtap_lowpass_tilde *)pd_new(rtap_lowpass_tilde_class);
    
    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x->lowpass = vas_iir_lowpass_new(1000);

    return (void *)x;
}

/**
 * @related rtap_lowpass_tilde
 * @brief Sets the gain adjustment parameter. <br>
 * @param x A pointer the rtap_lowpass_tilde object <br>
 * @param level Sets the level parameter <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_lowpass_tilde_setFrequency(rtap_lowpass_tilde *x, float freq)
{
    vas_iir_lowpass_setCutoff(x->lowpass, freq);
}

/**
 * @related rtap_lowpass_tilde
 * @brief Setup of rtap_lowpass_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_lowpass_tilde_setup(void)
{
      rtap_lowpass_tilde_class = class_new(gensym("rtap_lowpass~"),
            (t_newmethod)rtap_lowpass_tilde_new,
            (t_method)rtap_lowpass_tilde_free,
        sizeof(rtap_lowpass_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(rtap_lowpass_tilde_class, (t_method)rtap_lowpass_tilde_dsp, gensym("dsp"), 0);

      // this adds the gain message to our object
      class_addmethod(rtap_lowpass_tilde_class, (t_method)rtap_lowpass_tilde_setFrequency, gensym("freq"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(rtap_lowpass_tilde_class, rtap_lowpass_tilde, f);
}
