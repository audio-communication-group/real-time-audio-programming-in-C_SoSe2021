/**
 * @file vas_delay.h
 * @author Thomas Resch<br>
 * <br>
 * <br>
 * @brief Audio Object for adding delay to the input<br>
 * <br>
 * vas_delay allows for delaying<br>
 * any incoming audio signal. <br>
 * <br>
 */

#ifndef vas_delay_h
#define vas_delay_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vas_mem.h"
#include "vas_util.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * @struct vas_delay
 * @brief A structure for a delay object <br>
 * @var vas_delay::buffer The buffer we save the incoming signal in <br>
 * @var vas_delay::delay_in_samples The parameter value for adjusting the <br>
 * delay of the incoming signal
 * @var vas_delay::buffer_size The size of the delay buffer <br>
 * @var vas_delay::circular_pointer Circular pointer to the delay buffer <br>
 * @var vas_delay::delay_sample The current sample from the delay buffer <br>
 */
typedef struct vas_delay
{
    float *buffer;              /**< Our delay buffer */
    int delayInSamples;     /**< Our delay in samples */
    int bufferSize;           /**< Size of the delay buffer */
    int writeIndex;
    int readIndex1;
    int readIndex2;
    float *writePointer;    /**< Circular pointer to delay buffer */
    float *readPointer1;
    float *readPointer2;
} vas_delay;

/**
 * @related vas_delay
 * @brief Creates a new delay object<br>
 * The function sets the buffer size and delay parameter of <br>
 * the delay class
 * @return a pointer to the newly created vas_delay object <br>
 */
vas_delay *vas_delay_new(int bufferSize);

/**
 * @related vas_delay
 * @brief Frees a delay object<br>
 * @param x My delay object <br>
 * The function frees the allocated memory<br>
 * of a delay object
 */
void vas_delay_free(vas_delay *x);

/**
 * @related vas_delay
 * @brief Performs the delay in realtime. <br>
 * @param x My delay object <br>
 * @param in The input vector <br>
 * @param out The output vector <br>
 * @param vector_size The size of the i/o vectors <br>
 * The function vas_delay_perform delays any <br>
 * incoming signal and copies the result to the output vector <br>
 */
void vas_delay_process(vas_delay *x, float *in, float *outL, float *outR, int vector_size);

/**
 * @related vas_delay
 * @brief Sets the delay time in samples with floating point precision. <br>
 * @param x My delay object <br>
 * @param _delay_in_samples The delay in samples <br>
 * Sets the delay time in samples with floating point precision. <br>
 * Delays exceeding the buffer size are handeled by setting the delay to zero. <br>
 */
void vas_delay_setTap1(vas_delay *x, float _delay_in_samples);
void vas_delay_setTap2(vas_delay *x, float _delay_in_samples);

    
#ifdef __cplusplus
}
#endif

#endif /* vas_delay_h */
