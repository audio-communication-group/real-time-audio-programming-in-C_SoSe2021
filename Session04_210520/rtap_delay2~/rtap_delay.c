/**
 * @file rtap_delay_pd.c
 * @author Thomas Resch <br>
 * Audiocommunication Group, Technical University Berlin <br>
 * University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
 * A gain object for pure data <br>
 * <br>
 * @brief A Pure Data gain object for adjusting the volume<br>
 * <br>
 * rtap_delay~ allows for adjusting the level<br>
 * of any incoming audio signal. <br>
 * <br>
 */

#include "m_pd.h"
#include "vas_delay.h"

static t_class *rtap_delay2_tilde_class;

/**
 * @struct rtap_delay2_tilde
 * @brief The Pure Data struct of the rtap_delay~ object. <br>
 * @var rtap_delay2_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var rtap_delay2_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var rtap_delay2_tilde::gain The gain object for the actual signal processing <br>
 * @var rtap_delay2_tilde::x_out A signal outlet for the adjusted signal
 * level of the incoming signal
 */

typedef struct rtap_delay2_tilde
{
    t_object  x_obj;
    t_sample f;
    vas_delay *delay;
    t_outlet *outL;
    t_outlet *outR;
    t_inlet *delayTap1;
    t_inlet *delayTap2;
} rtap_delay2_tilde;

/**
 * @related rtap_delay2_tilde
 * @brief Calculates the volume adjusted output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the rtap_delay_perform method. <br>
 * @return A pointer to the signal chain right behind the rtap_delay2_tilde object. <br>
 */

t_int *rtap_delay2_tilde_perform(t_int *w)
{
    rtap_delay2_tilde *x = (rtap_delay2_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *outL =  (t_sample *)(w[3]);
    t_sample  *outR =  (t_sample *)(w[4]);
    int n =  (int)(w[5]);

    vas_delay_process(x->delay, in, outL, outR, n);
    //vas_iir_lowpass_process(x->lowpass, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+6);
}

/**
 * @related rtap_delay2_tilde
 * @brief Adds rtap_delay2_tilde_perform to the signal chain. <br>
 * @param x A pointer the rtap_delay2_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_delay2_tilde_dsp(rtap_delay2_tilde *x, t_signal **sp)
{
    dsp_add(rtap_delay2_tilde_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
}

/**
 * @related rtap_delay2_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the rtap_delay2_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_delay2_tilde_free(rtap_delay2_tilde *x)
{
    outlet_free(x->outL);
    outlet_free(x->outR);
    inlet_free(x->delayTap1);
    inlet_free(x->delayTap2);
    vas_delay_free(x->delay);
}

/**
 * @related rtap_delay2_tilde
 * @brief Creates a new rtap_delay2_tilde object.<br>
 * @param f Sets the initial gain value. <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *rtap_delay2_tilde_new(t_floatarg f)
{
    rtap_delay2_tilde *x = (rtap_delay2_tilde *)pd_new(rtap_delay2_tilde_class);
    
    //The main inlet is created automatically
    x->outL = outlet_new(&x->x_obj, &s_signal);
    x->outR = outlet_new(&x->x_obj, &s_signal);
    x->delay = vas_delay_new(44100);
    
    x->delayTap1 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("tap1"));
    x->delayTap2 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("tap2"));

    return (void *)x;
}

/**
 * @related rtap_delay2_tilde
 * @brief Sets the gain adjustment parameter. <br>
 * @param x A pointer the rtap_delay2_tilde object <br>
 * @param level Sets the level parameter <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_delay2_tilde_setTap1(rtap_delay2_tilde *x, float delayTime)
{
    vas_delay_setTap1(x->delay, delayTime);
}

void rtap_delay2_tilde_setTap2(rtap_delay2_tilde *x, float delayTime)
{
    vas_delay_setTap2(x->delay, delayTime);
}

/**
 * @related rtap_delay2_tilde
 * @brief Setup of rtap_delay2_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_delay2_tilde_setup(void)
{
      rtap_delay2_tilde_class = class_new(gensym("rtap_delay2~"),
            (t_newmethod)rtap_delay2_tilde_new,
            (t_method)rtap_delay2_tilde_free,
        sizeof(rtap_delay2_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(rtap_delay2_tilde_class, (t_method)rtap_delay2_tilde_dsp, gensym("dsp"), 0);

      // this adds the gain message to our object
      class_addmethod(rtap_delay2_tilde_class, (t_method)rtap_delay2_tilde_setTap1, gensym("tap1"), A_DEFFLOAT,0);
      class_addmethod(rtap_delay2_tilde_class, (t_method)rtap_delay2_tilde_setTap2, gensym("tap2"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(rtap_delay2_tilde_class, rtap_delay2_tilde, f);
}
