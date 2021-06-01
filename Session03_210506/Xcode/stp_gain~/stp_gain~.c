/**
 * @file stp_gain_pd.c
 * @author Thomas Resch <br>
 * Audiocommunication Group, Technical University Berlin <br>
 * University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
 * A gain object for pure data <br>
 * <br>
 * @brief A Pure Data gain object for adjusting the volume<br>
 * <br>
 * stp_gain~ allows for adjusting the level<br>
 * of any incoming audio signal. <br>
 * <br>
 */

#include "m_pd.h"
#include "stp_gain.h"

static t_class *stp_gain_tilde_class;

/**
 * @struct stp_gain_tilde
 * @brief The Pure Data struct of the stp_gain~ object. <br>
 * @var stp_gain_tilde::x_obj Necessary for every signal object in Pure Data <br>
 * @var stp_gain_tilde::f Also necessary for signal objects, float dummy dataspace <br>
 * for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) <br>
 * @var stp_gain_tilde::gain The gain object for the actual signal processing <br>
 * @var stp_gain_tilde::x_out A signal outlet for the adjusted signal
 * level of the incoming signal
 */

typedef struct stp_gain_tilde
{
    t_object  x_obj;
    t_sample f;
    stp_gain *gain;
    t_outlet *x_out;
} stp_gain_tilde;

/**
 * @related stp_gain_tilde
 * @brief Calculates the volume adjusted output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * For more information please refer to the Pure Data Docs <br>
 * The function calls the stp_gain_perform method. <br>
 * @return A pointer to the signal chain right behind the stp_gain_tilde object. <br>
 */

t_int *stp_gain_tilde_perform(t_int *w)
{
    stp_gain_tilde *x = (stp_gain_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);

    stp_gain_perform(x->gain, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

/**
 * @related stp_gain_tilde
 * @brief Adds stp_gain_tilde_perform to the signal chain. <br>
 * @param x A pointer the stp_gain_tilde object <br>
 * @param sp A pointer the input and output vectors <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void stp_gain_tilde_dsp(stp_gain_tilde *x, t_signal **sp)
{
    dsp_add(stp_gain_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @related stp_gain_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the stp_gain_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void stp_gain_tilde_free(stp_gain_tilde *x)
{
    outlet_free(x->x_out);
    stp_gain_free(x->gain);
}

/**
 * @related stp_gain_tilde
 * @brief Creates a new stp_gain_tilde object.<br>
 * @param f Sets the initial gain value. <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *stp_gain_tilde_new(t_floatarg f)
{
    stp_gain_tilde *x = (stp_gain_tilde *)pd_new(stp_gain_tilde_class);
    
    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x->gain = stp_gain_new();
    x->gain->level = f;

    return (void *)x;
}

/**
 * @related stp_gain_tilde
 * @brief Sets the gain adjustment parameter. <br>
 * @param x A pointer the stp_gain_tilde object <br>
 * @param level Sets the level parameter <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void stp_gain_tilde_setLevel(stp_gain_tilde *x, float level)
{
    x->gain->level = level;
}

/**
 * @related stp_gain_tilde
 * @brief Setup of stp_gain_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void stp_gain_tilde_setup(void)
{
      stp_gain_tilde_class = class_new(gensym("stp_gain~"),
            (t_newmethod)stp_gain_tilde_new,
            (t_method)stp_gain_tilde_free,
        sizeof(stp_gain_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(stp_gain_tilde_class, (t_method)stp_gain_tilde_dsp, gensym("dsp"), 0);

      // this adds the gain message to our object
      class_addmethod(stp_gain_tilde_class, (t_method)stp_gain_tilde_setLevel, gensym("gain"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(stp_gain_tilde_class, stp_gain_tilde, f);
}
