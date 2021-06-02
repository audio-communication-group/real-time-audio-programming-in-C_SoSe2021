/**
 * @file rtap_delay_pd.c
 * @author Thomas Resch <br>
 * @author changed by Markus Hädrich <br>
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

float MAX_DELAY_TIME_SEC = 10.0;
static t_class *rtap_delay10_tilde_class;

/**
 * @struct rtap_delay10_tilde
 * @brief The Pure Data struct of the rtap_delay~ object. <br>
 * @var rtap_delay10_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var rtap_delay10_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var rtap_delay10_tilde::gain The gain object for the actual signal processing <br>
 * @var rtap_delay10_tilde::x_out A signal outlet for the adjusted signal
 * level of the incoming signal
 */

typedef struct rtap_delay10_tilde
{
    t_object  x_obj;
    t_sample f;
    vas_delay *delay;
    void *inR;
    t_float in_delay_sec;
    t_float in_gain;
    t_float in_pan;
    t_outlet *outL;
    t_outlet *outR;
} rtap_delay10_tilde;

/**
 * @related rtap_delay10_tilde
 * @brief Calculates the volume adjusted output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the rtap_delay_perform method. <br>
 * @return A pointer to the signal chain right behind the rtap_delay10_tilde object. <br>
 */

t_int *rtap_delay10_tilde_perform(t_int *w)
{
    rtap_delay10_tilde *x = (rtap_delay10_tilde *)(w[1]);
    t_sample  *inL = (t_sample *)(w[2]);
    t_sample  *inR = (t_sample *)(w[3]);
    t_sample  *outL =  (t_sample *)(w[4]);
    t_sample  *outR =  (t_sample *)(w[5]);
    int n =  (int)(w[6]);

    vas_delay_process(x->delay, inL, inR, outL, outR, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+7);
}

/**
 * @related rtap_delay10_tilde
 * @brief Adds rtap_delay10_tilde_perform to the signal chain. <br>
 * @param x A pointer the rtap_delay10_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_delay10_tilde_dsp(rtap_delay10_tilde *x, t_signal **sp)
{
    dsp_add(rtap_delay10_tilde_perform, 6, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);
}


/**
 * @related rtap_delay10_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the rtap_delay10_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_delay10_tilde_free(rtap_delay10_tilde *x)
{
    outlet_free(x->outL);
    outlet_free(x->outR);
    inlet_free(x->inR);
    vas_delay_free(x->delay);
}

/**
 * @related rtap_delay10_tilde
 * @brief Creates a new rtap_delay10_tilde object.<br>
 * @param delay_in_sec Sets the delay in seconds. <br>
 * @param gain Sets the gain of the delay. <br>
 * @param pan Sets the panning of the delay. <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *rtap_delay10_tilde_new(t_floatarg f, t_floatarg delay_in_sec, t_floatarg gain, t_floatarg pan)
{
    rtap_delay10_tilde *x = (rtap_delay10_tilde *)pd_new(rtap_delay10_tilde_class);
    
    //The main inlet is created automatically
    x->outL = outlet_new(&x->x_obj, &s_signal);
    x->outR = outlet_new(&x->x_obj, &s_signal);
    x->in_delay_sec = delay_in_sec;
    x->in_gain = gain;
    x->in_pan = pan;
    floatinlet_new(&x->x_obj, &x->in_delay_sec); // passive inlets
    floatinlet_new(&x->x_obj, &x->in_gain);
    floatinlet_new(&x->x_obj, &x->in_pan);
    x->inR  = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal); // not used now
    x->delay = vas_delay_new(MAX_DELAY_TIME_SEC * sys_getsr());

    return (void *)x;
}

/**
 * @related rtap_delay10_tilde
 * @brief Sets the gain adjustment parameter. <br>
 * @param x A pointer the rtap_delay10_tilde object <br>
 * @param level Sets the level parameter <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_delay10_tilde_set_params(rtap_delay10_tilde *x)
{
    float sample_rate = sys_getsr();
    float delayInSamples = (x->in_delay_sec * sample_rate);
    post("Delay:\ndelay time: %.1f\tgain: %.1f\tpan: %.1f", x->in_delay_sec, x->in_gain, x->in_pan);
    vas_delay_setTap(x->delay, delayInSamples, x->in_gain, x->in_pan);
}

/**
 * @related rtap_delay10_tilde
 * @brief Setup of rtap_delay10_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_delay10_tilde_setup(void)
{
      rtap_delay10_tilde_class = class_new(gensym("rtap_delay10~"),
            (t_newmethod)rtap_delay10_tilde_new,
            (t_method)rtap_delay10_tilde_free,
        sizeof(rtap_delay10_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, 0);

      class_addmethod(rtap_delay10_tilde_class, (t_method)rtap_delay10_tilde_dsp, gensym("dsp"), 0);

      // this adds the delay method to our object
      class_addmethod(rtap_delay10_tilde_class, (t_method)rtap_delay10_tilde_set_params, gensym("set_params"), 0);
    
      CLASS_MAINSIGNALIN(rtap_delay10_tilde_class, rtap_delay10_tilde, f);
}
