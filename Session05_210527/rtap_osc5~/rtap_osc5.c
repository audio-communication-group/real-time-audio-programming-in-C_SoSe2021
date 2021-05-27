/**
 * @file rtap_osc5_pd.c
 * @author Thomas Resch <br>
 * Audiocommunication Group, Technical University Berlin <br>
 * University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
 * A gain object for pure data <br>
 * <br>
 * @brief A Pure Data gain object for adjusting the volume<br>
 * <br>
 * rtap_osc5~ allows for adjusting the level<br>
 * of any incoming audio signal. <br>
 * <br>
 */

#include "m_pd.h"
#include "vas_osc.h"

static t_class *rtap_osc5_tilde_class;

/**
 * @struct rtap_osc5_tilde
 * @brief The Pure Data struct of the rtap_osc5~ object. <br>
 * @var rtap_osc5_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var rtap_osc5_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var rtap_osc5_tilde::gain The gain object for the actual signal processing <br>
 * @var rtap_osc5_tilde::x_out A signal outlet for the adjusted signal
 * level of the incoming signal
 */

typedef struct rtap_osc5_tilde
{
    t_object  x_obj;
    t_sample f;
    vas_osc *osc;
    t_word *table;
    t_word *envelopeTable;
    
    t_outlet *out;
} rtap_osc5_tilde;

/**
 * @related rtap_osc5_tilde
 * @brief Calculates the volume adjusted output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the rtap_osc5_perform method. <br>
 * @return A pointer to the signal chain right behind the rtap_osc5_tilde object. <br>
 */

t_int *rtap_osc5_tilde_perform(t_int *w)
{
    rtap_osc5_tilde *x = (rtap_osc5_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);

    vas_osc_process(x->osc, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

/**
 * @related rtap_osc5_tilde
 * @brief Adds rtap_osc5_tilde_perform to the signal chain. <br>
 * @param x A pointer the rtap_osc5_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_osc5_tilde_dsp(rtap_osc5_tilde *x, t_signal **sp)
{
    dsp_add(rtap_osc5_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @related rtap_osc5_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the rtap_osc5_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_osc5_tilde_free(rtap_osc5_tilde *x)
{
    outlet_free(x->out);
    vas_osc_free(x->osc);
}

/**
 * @related rtap_osc5_tilde
 * @brief Creates a new rtap_osc5_tilde object.<br>
 * @param f Sets the initial gain value. <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_getArray(rtap_osc5_tilde *x, t_symbol *arrayname, t_word **array, int *length)
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
        pd_error(x, "%s: bad template for rtap_osc5~", arrayname->s_name);
        *array = 0;
    }
    else
    {
        post("Reading IRs from array %s", arrayname->s_name);
    }
}

void rtap_osc5_tilde_setExternTable(rtap_osc5_tilde *x, t_symbol *name)
{
    int length = 0;
    rtap_getArray(x, name, &x->table, &length);
    for (int i=0;i<44100; i++)
        x->osc->lookupTable[i] = x->table[i].w_float;
}

void rtap_osc5_tilde_setEnvelopeTable(rtap_osc5_tilde *x, t_symbol *name)
{
    int length = 0;
    rtap_getArray(x, name, &x->envelopeTable, &length);
    for (int i=0;i<44100; i++)
        x->osc->envelopeTable[i] = x->envelopeTable[i].w_float;
}

void *rtap_osc5_tilde_new(t_floatarg f)
{
    rtap_osc5_tilde *x = (rtap_osc5_tilde *)pd_new(rtap_osc5_tilde_class);
    
    //The main inlet is created automatically
    x->out = outlet_new(&x->x_obj, &s_signal);
    x->osc = vas_osc_new(44100);

    return (void *)x;
}

/**
 * @related rtap_osc5_tilde
 * @brief Sets the gain adjustment parameter. <br>
 * @param x A pointer the rtap_osc5_tilde object <br>
 * @param level Sets the level parameter <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_osc5_tilde_noteOn(rtap_osc5_tilde *x, float frequency, float velocity)
{
    vas_osc_noteOn(x->osc, frequency, velocity);   
}

/**
 * @related rtap_osc5_tilde
 * @brief Setup of rtap_osc5_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void rtap_osc5_tilde_setup(void)
{
      rtap_osc5_tilde_class = class_new(gensym("rtap_osc5~"),
            (t_newmethod)rtap_osc5_tilde_new,
            (t_method)rtap_osc5_tilde_free,
        sizeof(rtap_osc5_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(rtap_osc5_tilde_class, (t_method)rtap_osc5_tilde_dsp, gensym("dsp"), 0);

      // this adds the gain message to our object
      class_addmethod(rtap_osc5_tilde_class, (t_method)rtap_osc5_tilde_noteOn, gensym("noteon"), A_DEFFLOAT, A_DEFFLOAT, 0);
      class_addmethod(rtap_osc5_tilde_class, (t_method)rtap_osc5_tilde_setExternTable, gensym("setwaveform"), A_SYMBOL, 0);
      class_addmethod(rtap_osc5_tilde_class, (t_method)rtap_osc5_tilde_setEnvelopeTable, gensym("setenvelope"), A_SYMBOL, 0);
      

      CLASS_MAINSIGNALIN(rtap_osc5_tilde_class, rtap_osc5_tilde, f);
}
