/**
 * @file vas_osc.h
 * @author C.Jaedicke, A.Monciero, P.Schuhladen, F.Müller <br>
 * An interpolated delay <br>
 * <br>
 * @brief Audio Object for adding delay to the input<br>
 * <br>
 * vas_osc allows for delaying<br>
 * any incoming audio signal. <br>
 * <br>
 */

#ifndef vas_osc_h
#define vas_osc_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vas_mem.h"
#include "vas_util.h"

#ifdef __cplusplus
extern "C" {
#endif

    
/**
 * @struct vas_osc
 * @brief A structure for a delay object <br>
 * @var vas_osc::buffer The buffer we save the incoming signal in <br>
 * @var vas_osc::delay_in_samples The parameter value for adjusting the <br>
 * delay of the incoming signal
 * @var vas_osc::buffer_size The size of the delay buffer <br>
 * @var vas_osc::circular_pointer Circular pointer to the delay buffer <br>
 * @var vas_osc::delay_sample The current sample from the delay buffer <br>
 */

typedef struct vas_osc
{
    int tableSize;

    float currentIndex;
    int envelopeIndex;
    float frequency;
    float *lookupTable;
    float *envelopeTable;

} vas_osc;

/**
 * @related vas_osc
 * @brief Creates a new delay object<br>
 * The function sets the buffer size and delay parameter of <br>
 * the delay class
 * @return a pointer to the newly created vas_osc object <br>
 */
vas_osc *vas_osc_new(int tableSize);

/**
 * @related vas_osc
 * @brief Frees a delay object<br>
 * @param x My delay object <br>
 * The function frees the allocated memory<br>
 * of a delay object
 */
void vas_osc_free(vas_osc *x);

/**
 * @related vas_osc
 * @brief Performs the delay in realtime. <br>
 * @param x My delay object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vector_size The size of the i/o vectors <br>
 * The function vas_osc_perform delays any <br>
 * incoming signal and copies the result to the output vector <br>
 */
void vas_osc_process(vas_osc *x, float *in, float *out, int vector_size);

/**
 * @related vas_osc
 * @brief Sets the delay time in samples with floating point precision. <br>
 * @param x My delay object <br>
 * @param _delay_in_samples The delay in samples <br>
 * Sets the delay time in samples with floating point precision. <br>
 * Delays exceeding the buffer size are handeled by setting the delay to zero. <br>
 */
void vas_osc_setFrequency(vas_osc *x, float frequency);

    
#ifdef __cplusplus
}
#endif

#endif /* vas_osc_h */
