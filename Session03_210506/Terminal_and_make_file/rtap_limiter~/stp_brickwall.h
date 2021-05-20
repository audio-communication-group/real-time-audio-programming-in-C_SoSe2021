/**
 * @file stp_brickwall.h
 * @author Thomas Resch <br>
 * Audiocommunication Group, Technical University Berlin <br>
 * University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
 * A very advanced gain plugin <br>
 * <br>
 * @brief Audio Object for a simple brickwall limiter<br>
 * <br>
 * stp_brickwall allows for adjusting and clipping the level<br>
 * of any incoming audio signal. <br>
 * <br>
 */

#ifndef stp_brickwall_h
#define stp_brickwall_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>


typedef float STP_INPUTVECTOR;
typedef float STP_OUTPUTVECTOR;

/**
 * @struct stp_brickwall
 * @brief A structure for a brickwall limiter object <br>
 * @var stp::level The parameter value for adjusting the <br>
 * level of the incoming signal
 */

typedef struct stp_brickwall
{
    float makeUpLevel; /**< parameter for adjusting the level of the incoming signal */
    float clippingLevel; /**< parameter for clipping the level of the incoming signal */
} stp_brickwall;

/**
 * @related stp_brickwall
 * @brief Creates a new brickwall object<br>
 * The function creates a new stp_brickwall object <br>
 * @return a pointer to the newly created stp_brickwall object <br>
 */

stp_brickwall *stp_brickwall_new();

/**
 * @related stp_brickwall
 * @brief Frees a stp_brickwall object<br>
 * @param x My brickwall object to delete.<br>
 * The function frees the allocated memory<br>
 * of a gain object
 */

void stp_brickwall_free(stp_brickwall *x);

/**
 * @related stp_brickwall
 * @brief Sets the gain parameter <br>
 * @param x My stp_brickwall object <br>
 * @param makeUpLevel The gain value <br>
 * The function sets the makeUpLevel parameter of <br>
 * the gain class
 */

void stp_brickwall_setMakeUpLevel(stp_brickwall *x, float makeUpLevel);

/**
 * @related stp_brickwall
 * @brief Sets the clippingLevel parameter <br>
 * @param x My stp_brickwall object <br>
 * @param clippingLevel The clippingLevel value <br>
 * The function sets the clippingLevel parameter of <br>
 * the gain class
 */

void stp_brickwall_setClippingLevel(stp_brickwall *x, float clippingLevel);

/**
 * @related stp_brickwall
 * @brief Performs the level makeup in realtime <br>
 * @param x My gain object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vectorSize The vectorSize <br>
 * The function stp_brickwall_makeUp multiplies the input signal <br>
 * with the parameter gain. <br>
 */

void stp_brickwall_makeUp(stp_brickwall *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize);

/**
 * @related stp_brickwall
 * @brief Performs the clipping in realtime <br>
 * @param x My gain object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vectorSize The vectorSize <br>
 * The function stp_brickwall_clip sets every value of the input signal <br>
 * thats either greater then the parameter clippingLevel or smaller then the <br>
 * parameter -clippingLevel to either clippingLevel or -clippingLevel. <br>
 */

void stp_brickwall_clip(stp_brickwall *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize);

/**
 * @related stp_brickwall
 * @brief Performs the level adjustment in realtime <br>
 * @param x My gain object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vectorSize The vectorSize <br>
 * The function stp_brickwall_perform performs the gain adjustment of <br>
 * the incoming signal and copies the result to the output vector <br>
 */

void stp_brickwall_perform(stp_brickwall *x, STP_INPUTVECTOR *in, STP_OUTPUTVECTOR *out, int vectorSize);

#ifdef __cplusplus
}
#endif

#endif /* stp_brickwall_h */
