#include "NextButtonLookAndFeel.h"

void NextButtonLookAndFeel::drawToggleButton(Graphics& g, ToggleButton& t, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {

	// background
	auto buttonArea = t.getLocalBounds();
	g.setColour(dark);
	g.fillRect(buttonArea);

	// light area
	Colour lightColor = light;
	if (shouldDrawButtonAsHighlighted)
	{
		lightColor = lightColor.darker(0.6f);
	}

	auto lightUpArea = buttonArea;
	lightUpArea.setHeight(buttonArea.getHeight() * 0.7);
	lightUpArea.setWidth(buttonArea.getWidth() * 0.3);

	int xShift;
	if (pointingRight)
	{
		xShift = (buttonArea.getWidth() * 0.2f);
	}
	else
	{
		xShift = -(buttonArea.getWidth() * 0.2f);
	}

	lightUpArea.setCentre(buttonArea.getCentreX() + xShift, buttonArea.getCentreY());

	g.setColour(lightColor);
	g.fillRect(lightUpArea);

}
