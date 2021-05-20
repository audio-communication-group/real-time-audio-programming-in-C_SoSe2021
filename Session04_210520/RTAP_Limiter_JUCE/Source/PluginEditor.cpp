/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    
    // these define the parameters of our slider object
    makeup.setSliderStyle (juce::Slider::LinearBarVertical);
    makeup.setRange (0.0, 4.0, 0.01);
    makeup.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    makeup.setPopupDisplayEnabled (true, false, this);
    makeup.setTextValueSuffix (" Make-up");
    makeup.setValue(1.0);
     
        // this function adds the slider to the editor
    addAndMakeVisible (&makeup);
    
    clipping.setSliderStyle (juce::Slider::LinearBarVertical);
    clipping.setRange (0.0, 1.0, 0.01);
    clipping.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    clipping.setPopupDisplayEnabled (true, false, this);
    clipping.setTextValueSuffix (" Clipping");
    clipping.setValue(1.0);

    addAndMakeVisible (&clipping);
    
    makeup.addListener(this);  // define the instance that implements the listener function
    clipping.addListener (this);   
}

/* 

   Implement the sliderValueChanged method, don't forget to subclass
   the Editor from "private juce::Slider::Listener"

*/
void NewProjectAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.limiter->makeUpLevel = makeup.getValue();
    audioProcessor.limiter->clippingLevel  = clipping.getValue();
    
    printf("%f\n", audioProcessor.limiter->makeUpLevel);
    printf("%f\n", audioProcessor.limiter->clippingLevel);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("RTAP Limiter", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    makeup.setBounds (40, 30, 20, getHeight() - 60);
    clipping.setBounds (80, 30, 20, getHeight() - 60);

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
