#include "m_pd.h"

static t_class *stp_gain_tilde_class;

typedef struct stp_gain_tilde
{
    t_object  x_obj;
    t_sample f;
    t_sample gain;
    t_outlet*x_out;
} stp_gain_tilde;

t_int *stp_gain_tilde_perform(t_int *w)
{
    stp_gain_tilde *x = (stp_gain_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);
    int i;

    for(i=0; i<n; i++)
        out[i] = in[i] * x->gain;

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

void stp_gain_tilde_dsp(stp_gain_tilde *x, t_signal **sp)
{
    dsp_add(stp_gain_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void stp_gain_tilde_free(stp_gain_tilde *x)
{
    outlet_free(x->x_out);
}

void *stp_gain_tilde_new(t_floatarg f)
{
    stp_gain_tilde *x = (stp_gain_tilde *)pd_new(stp_gain_tilde_class);

    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x->gain = 0;
    return (void *)x;
}

void stp_gain_set(stp_gain_tilde *x, float gain)
{
    x->gain = gain;
}

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
      class_addmethod(stp_gain_tilde_class, (t_method)stp_gain_set, gensym("gain"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(stp_gain_tilde_class, stp_gain_tilde, f);
}
