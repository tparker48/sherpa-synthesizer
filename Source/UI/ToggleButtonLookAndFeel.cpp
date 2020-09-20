#include "ToggleButtonLookAndFeel.h"

void ToggleButtonLookAndFeel::drawToggleButton(Graphics& g, ToggleButton& t, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
	
	// background
	auto buttonArea = t.getLocalBounds();
	g.setColour(dark);
	g.fillRect(buttonArea);

	float lightUpWidthFactor = 0.1f;

	auto lightUpArea = buttonArea;
	lightUpArea.setHeight(buttonArea.getHeight() * .45);
	lightUpArea.setWidth(buttonArea.getWidth() * (0.5f - lightUpWidthFactor));
	float centerShift = (lightUpArea.getWidth() * .5f) + lightUpWidthFactor;
	// off
	if (!t.getToggleState())
	{
		lightUpArea.setCentre(buttonArea.getCentreX() - centerShift, buttonArea.getCentreY());
	}
	// on
	else
	{
		lightUpArea.setCentre(buttonArea.getCentreX() + centerShift, buttonArea.getCentreY());
	}

	g.setColour(light);
	g.fillRect(lightUpArea);
	
}
