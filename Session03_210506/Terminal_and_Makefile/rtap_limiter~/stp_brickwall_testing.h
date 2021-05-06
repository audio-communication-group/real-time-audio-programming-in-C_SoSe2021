/**
 * @file stp_brickwall_testing.h
 * @author Thomas Resch <br>
 * Audiocommunication Group, Technical University Berlin <br>
 * University of Applied Sciences Nordwestschweiz (FHNW), Music-Academy, Research and Development <br>
 * An exemplary testing unit for the stp_brickwall object. <br>
 * It creates a known signal, alternating from -2 to 2 <br>
 * and then checks whether the output signal holds the correct values<br>
 * for the given parameters gain = 2 and clippingLevel = 1.<br>
 * It is called from the stp_brickwall~ object inside pure data with<br>
 * the message "integrationtest".<br>
 * <br>
 * @brief Unit and Integration Test for stp_brickwall<br>
 * <br>
 * Performs Unit Tests for stp_brickwall_makeUp()<br>
 * and stp_brickwall_clip() and an Integration Test for both.<br>
 * <br>
 */

#ifndef stp_brickwall_unittest_makeup_h
#define stp_brickwall_unittest_makeup_h

#include "stp_brickwall.h"

typedef struct stp_brickwallTest
{
    stp_brickwall *brickwall2Test;
    int vectorSize;
    int testSignalLength;
    int numberOfVectors2Test;
    STP_INPUTVECTOR *inputSignal;
    STP_OUTPUTVECTOR *outputSignal;
    
}   stp_brickwallTest;

stp_brickwallTest *stp_brickwallTest_new(stp_brickwall *brickwall2Test, int vectorSize, int testSignalLength);

void stp_brickwallTest_free(stp_brickwallTest *x);

void stp_brickwallTest_integration(stp_brickwallTest *x);

#endif /* stp_brickwall_unittest_makeup_h */
