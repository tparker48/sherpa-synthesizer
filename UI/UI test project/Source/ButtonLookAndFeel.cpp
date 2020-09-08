#include "ButtonLookAndFeel.h"

void ButtonLookAndFeel::drawTickBox(Graphics& g, Component& c, float x, float y, float w, float h, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	//Rectangle<int> rect = c.getBounds();
	//int coordX = rect.getX();
	//int coordY = rect.getY();
	//int width = rect.getWidth();
	//int height = rect.getHeight();
	//
	//g.setColour(dark);
	//g.fillRect(coordX,coordY, width,height);
	//
	//g.setColour(light);
	//g.drawRect(x, y, w, h);
}



void ButtonLookAndFeel::drawToggleButton(Graphics& g, ToggleButton& t, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
	
	// background
	auto buttonArea = t.getLocalBounds();
	g.setColour(dark);
	g.fillRect(buttonArea);

	// on
	if (t.getToggleState())
	{
		auto lightUpArea = buttonArea;
		lightUpArea.setHeight(buttonArea.getHeight()*.25);
		lightUpArea.setWidth(buttonArea.getHeight() * .65);
		lightUpArea.setCentre(buttonArea.getCentreX(), buttonArea.getCentreY() - buttonArea.getHeight() * .17);
		g.setColour(light);
		g.fillRect(lightUpArea);
	}
	
}
