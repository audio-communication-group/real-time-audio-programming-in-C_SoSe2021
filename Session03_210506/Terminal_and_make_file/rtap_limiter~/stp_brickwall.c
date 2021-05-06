#include "stp_brickwall.h"

stp_brickwall *stp_brickwall_new()
{
    stp_brickwall *x = (stp_brickwall *)malloc(sizeof(stp_brickwall));
    x->makeUpLevel = 0.0;
    x->clippingLevel = 1.0;
    return x;
}

void stp_brickwall_free(stp_brickwall *x)
{
    free(x);
}

void stp_brickwall_setMakeUpLevel(stp_brickwall *x, float makeUpLevel)
{
    x->makeUpLevel = makeUpLevel;
}

void stp_brickwall_setClippingLevel(stp_brickwall *x, float clippingLevel)
{
    x->clippingLevel = clippingLevel;
}

void stp_brickwall_makeUp(stp_brickwall *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize)
{
    int i = 0;
    while(i < vectorSize)
    {
        *out++ = *in++ * x->makeUpLevel;
        i++;
    }
}

void stp_brickwall_clip(stp_brickwall *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize)
{
    int i = 0;
    while(i < vectorSize)
    {
        *out = *in;
        
        if(*out > x->clippingLevel)
            *out = x->clippingLevel;
        if(*out < -x->clippingLevel)
            *out = -x->clippingLevel;
        
        out++;
        in++;
        i++;
    }
}

void stp_brickwall_perform(stp_brickwall *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize)
{
    stp_brickwall_makeUp(x, in, out, vectorSize);
    stp_brickwall_clip(x, in, out, vectorSize);
}
