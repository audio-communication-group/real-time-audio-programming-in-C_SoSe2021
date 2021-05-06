

#include "stp_brickwall_testing.h"
#include "m_pd.h"

stp_brickwallTest *stp_brickwallTest_new(stp_brickwall *brickwall2Test, int vectorSize, int testSignalLength)
{
    stp_brickwallTest *x = (stp_brickwallTest *)malloc(sizeof(stp_brickwallTest));
    x->brickwall2Test = brickwall2Test;
    x->testSignalLength = testSignalLength;
    x->vectorSize = vectorSize;
    x->numberOfVectors2Test = testSignalLength/vectorSize;
    x->inputSignal = (STP_INPUTVECTOR *)malloc(testSignalLength * sizeof(STP_INPUTVECTOR));
    x->outputSignal = (STP_OUTPUTVECTOR *)malloc(testSignalLength * sizeof(STP_OUTPUTVECTOR));

    return x;
}

void stp_brickwallTest_free(stp_brickwallTest *x)
{
    free(x->inputSignal);
    free(x->outputSignal);
    free(x);
}

void stp_brickwallTest_createInputSignal(stp_brickwallTest *x)
{
    for(int i = 0; i < x->testSignalLength; i++)
    {
        if(i % 2)
            x->inputSignal[i] = 2;
        else
            x->inputSignal[i] = -2;
    }
}

int stp_brickwallTest_unitMakeUpLevel(stp_brickwallTest *x)
{
    int unitTestFailed = 0;
    stp_brickwall_setMakeUpLevel(x->brickwall2Test, 2);
    
    for(int i = 0; i < x->numberOfVectors2Test; i++)
    {
        STP_INPUTVECTOR *inputSignalPtr = x->inputSignal + i * x->vectorSize;
        STP_OUTPUTVECTOR *outputSignalPtr = x->outputSignal + i * x->vectorSize;
        stp_brickwall_makeUp(x->brickwall2Test, inputSignalPtr, outputSignalPtr, x->vectorSize);
    }
    
    for(int i = 0; i < x->testSignalLength; i++)
    {
        if(i % 2)
        {
            post("Output at index %d is %f, should be %f", i, x->outputSignal[i], 4.0);
            if(x->outputSignal[i] != 4)
                unitTestFailed = 1;
        }
        else
        {
            post("Output at index %d is %f, should be %f", i,x->outputSignal[i], -4.0);
            if(x->outputSignal[i] != -4)
                unitTestFailed = 1;
        }
    }
    
    if(!unitTestFailed)
        post("\nUnit Test for function stp_brickwall_makeUp() succeeded!\n");
    else
        post("\nUnit Test for function stp_brickwall_makeUp() failed!\n");
    
    return unitTestFailed;
}

int stp_brickwallTest_unitClipping(stp_brickwallTest *x)
{
    int unitTestFailed = 0;
    stp_brickwall_setClippingLevel(x->brickwall2Test, 1);
    
    for(int i = 0; i < x->numberOfVectors2Test; i++)
    {
        STP_INPUTVECTOR *inputSignalPtr = x->inputSignal + i * x->vectorSize;
        STP_OUTPUTVECTOR *outputSignalPtr = x->outputSignal + i * x->vectorSize;
        stp_brickwall_clip(x->brickwall2Test, inputSignalPtr, outputSignalPtr, x->vectorSize);
    }
    
    for(int i = 0; i < x->testSignalLength; i++)
    {
        if(i % 2)
        {
            post("Output at index %d is %f, should be %f", i, x->outputSignal[i], 1.0);
            if(x->outputSignal[i] != 1)
                unitTestFailed = 1;
        }
        else
        {
            post("Output at index %d is %f, should be %f", i,x->outputSignal[i], -1.0);
            if(x->outputSignal[i] != -1)
                unitTestFailed = 1;
        }
    }
    
    if(!unitTestFailed)
        post("\nUnit Test for function stp_brickwall_clip() succeeded!\n");
    else
        post("\nUnit Test for function stp_brickwall_clip() failed!\n");
    
    return unitTestFailed;
}

void stp_brickwallTest_integration(stp_brickwallTest *x)
{
    int integrationTestFailed = 0;
    
    stp_brickwallTest_createInputSignal(x);
    
    integrationTestFailed |= stp_brickwallTest_unitMakeUpLevel(x);
    integrationTestFailed |= stp_brickwallTest_unitClipping(x);
    
    if(!integrationTestFailed)
        post("\nIntegration Test for stp_brickwall~ succeeded!\n");
    else
        post("\nIntegration Test for stp_brickwall~ failed!\n");
}

