/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.fillAll(Colours::purple);

    g.setColour (Colours::yellow);
    g.setFont (Font (Font::getDefaultSansSerifFontName(), 48.0f, Font::italic));
    g.drawText ("Learning JUCE!", getLocalBounds(), Justification::centred, true);
    
    drawBorder(g);
    drawWave(g);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::drawBorder(Graphics& g)
{
    auto bounds = getLocalBounds();
    g.drawRoundedRectangle(bounds.getX() + 10, bounds.getY() + 10, bounds.getWidth() - 20, bounds.getHeight() - 20, 5.0f, 5.0f);
}

void MainComponent::drawWave(Graphics& g)
{
    // Change drawing color
    //g.setColour(Colours::white);
    
    // Get bounds and width
    //auto bounds = getLocalBounds();
    //auto width = bounds.getWidth();
    
    // Declare path and starting point.
    //Path wavePath;
    //wavePath.startNewSubPath(bounds.getX() + 10, bounds.getY() + 300);
    
    // Traverse width and calculate y coordinate for each  x coordinate in width
    //for (auto x = bounds.getX() + 10; x < (width - 20); x++)
    //{
    //    auto y = sin(( x * M_PI) / 180 );
    //    std::cout << x << ", " <<  y;
    //    wavePath.lineTo(x, y);
    //    wavePath.closeSubPath();
    //}
    
    
    //g.strokePath (wavePath, PathStrokeType (5.0f));
}
