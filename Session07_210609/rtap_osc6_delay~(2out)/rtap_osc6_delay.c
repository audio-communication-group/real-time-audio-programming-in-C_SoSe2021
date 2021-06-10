/**
 * @file rtap_osc6_pd.c
 * @author Thomas Resch <br>
 * Audiocommunication Group, Technical University Berlin <br>
 * University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
 * A gain object for pure data <br>
 * <br>
 * @brief A Pure Data gain object for adjusting the volume<br>
 * <br>
 * rtap_osc6~ allows for adjusting the level<br>
 * of any incoming audio signal. <br>
 * <br>
 */

#include "m_pd.h"
#include "vas_osc.h"
#include "vas_delay.h"

float MAX_DELAY_TIME_SEC = 10.0;
static t_class *rtap_osc6_delay_class;

/**
 * @struct rtap_osc6_delay
 * @brief The Pure Data struct of the rtap_osc6~ object. <br>
 * @var rtap_osc6_delay::x_obj Necessary for every signal object in Pure Data <br>
 * @var rtap_osc6_delay::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var rtap_osc6_delay::gain The gain object for the actual signal processing <br>
 * @var rtap_osc6_delay::x_out A signal outlet for the adjusted signal
 * level of the incoming signal
 */

typedef struct rtap_osc6_delay_tilde
{
    t_object  x_obj;
    t_sample f;
    vas_osc *osc;
    t_word *table;
    t_word *envelopeTable;
    vas_delay *delay; //new
    t_outlet *outL;   // new
    t_outlet *outR;   // new
} rtap_osc6_delay;

/**
 * @related rtap_osc6_delay
 * @brief Calculates the volume adjusted output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the rtap_osc6_perform method. <br>
 * @return A pointer to the signal chain right behind the rtap_osc6_delay object. <br>
 */

t_int *rtap_osc6_delay_perform(t_int *w)
{
    rtap_osc6_delay *x = (rtap_osc6_delay *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *outL =  (t_sample *)(w[3]);
    t_sample  *outR =  (t_sample *)(w[4]);
    int n =  (int)(w[5]);

    vas_osc_process(x->osc, in, outL, n);
    vas_delay_process(x->delay, outL, outR, n); //new

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+6); //new
}

/**
 * @related rtap_osc6_delay
 * @brief Adds rtap_osc6_delay_perform to the signal chain. <br>
 * @param x A pointer the rtap_osc6_delay object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_osc6_delay_tilde_dsp(rtap_osc6_delay *x, t_signal **sp)
{
    dsp_add(rtap_osc6_delay_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
} //new

/**
 * @related rtap_osc6_delay
 * @brief Frees our object. <br>
 * @param x A pointer the rtap_osc6_delay object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_osc6_delay_tilde_free(rtap_osc6_delay *x)
{
    outlet_free(x->outL);     // new
    outlet_free(x->outR);     // new
    vas_osc_free(x->osc);
    vas_delay_free(x->delay); //new
}

/**
 * @related rtap_osc6_delay
 * @brief Creates a new rtap_osc6_delay object.<br>
 * @param f Sets the initial gain value. <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_getArray(rtap_osc6_delay *x, t_symbol *arrayname, t_word **array, int *length)
{
    t_garray *a;

    if (!(a = (t_garray *)pd_findbyclass(arrayname, garray_class)))
    {
        if (*arrayname->s_name) pd_error(x, "vas_binaural~: %s: no such array",
            arrayname->s_name);
        *array = 0;
    }
    else if (!garray_getfloatwords(a, length, array))
    {
        pd_error(x, "%s: bad template for rtap_osc6~", arrayname->s_name);
        *array = 0;
    }
    else
    {
        post("Reading IRs from array %s", arrayname->s_name);
    }
}

void rtap_osc6_delay_tilde_setExternTable(rtap_osc6_delay *x, t_symbol *name)
{
    int length = 0;
    rtap_getArray(x, name, &x->table, &length);
    for (int i=0;i<44100; i++)
        x->osc->lookupTable[i] = x->table[i].w_float;
}

void rtap_osc6_delay_tilde_setEnvelopeTable(rtap_osc6_delay *x, t_symbol *name)
{
    int length = 0;
    rtap_getArray(x, name, &x->envelopeTable, &length);
    for (int i=0;i<44100; i++)
        x->osc->envelopeTable[i] = x->envelopeTable[i].w_float;
}

void *rtap_osc6_delay_tilde_new(t_floatarg f, t_floatarg d)
{
    rtap_osc6_delay *x = (rtap_osc6_delay *)pd_new(rtap_osc6_delay_class);
    
    //The main inlet is created automatically
    x->outL = outlet_new(&x->x_obj, &s_signal); // new
    x->outR = outlet_new(&x->x_obj, &s_signal); // new
    x->osc = vas_osc_new(sys_getsr());
    x->delay = vas_delay_new(MAX_DELAY_TIME_SEC * sys_getsr()); //new

    return (void *)x;
}

/**
 * @related rtap_delay_tilde
 * @brief Sets the gain adjustment parameter. <br>
 * @param x A pointer the rtap_delay_tilde object <br>
 * @param level Sets the level parameter <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_delay_tilde_setDelayTime(rtap_osc6_delay *x, float delayTime)
{
    vas_delay_setDelayTime(x->delay, delayTime);
} //new


/**
 * @related rtap_osc6_delay
 * @brief Sets the gain adjustment parameter. <br>
 * @param x A pointer the rtap_osc6_delay object <br>
 * @param level Sets the level parameter <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_osc6_delay_tilde_noteOn(rtap_osc6_delay *x, float frequency, float velocity)
{
    vas_osc_noteOn(x->osc, frequency, velocity);   
}

/**
 * @related rtap_osc6_delay
 * @brief Setup of rtap_osc6_delay <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_osc6_delay_tilde_setup(void)
{
      rtap_osc6_delay_class = class_new(gensym("rtap_osc6_delay~"),
            (t_newmethod)rtap_osc6_delay_tilde_new,
            (t_method)rtap_osc6_delay_tilde_free,
        sizeof(rtap_osc6_delay),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(rtap_osc6_delay_class, (t_method)rtap_osc6_delay_tilde_dsp, gensym("dsp"), 0);

      // this adds the gain message to our object
      class_addmethod(rtap_osc6_delay_class, (t_method)rtap_osc6_delay_tilde_noteOn, gensym("noteon"), A_DEFFLOAT, A_DEFFLOAT, 0);
      class_addmethod(rtap_osc6_delay_class, (t_method)rtap_osc6_delay_tilde_setExternTable, gensym("setwaveform"), A_SYMBOL, 0);
      class_addmethod(rtap_osc6_delay_class, (t_method)rtap_osc6_delay_tilde_setEnvelopeTable, gensym("setenvelope"), A_SYMBOL, 0);
    
      // this adds the gain message to our object
      class_addmethod(rtap_osc6_delay_class, (t_method)rtap_delay_tilde_setDelayTime, gensym("delaytime"), A_DEFFLOAT,0); //new
      

      CLASS_MAINSIGNALIN(rtap_osc6_delay_class, rtap_osc6_delay, f);
}
