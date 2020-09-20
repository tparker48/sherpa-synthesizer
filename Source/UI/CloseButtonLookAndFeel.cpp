#include "CloseButtonLookAndFeel.h"

void CloseButtonLookAndFeel::drawToggleButton(Graphics& g, ToggleButton& t, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {

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
	lightUpArea.setHeight(buttonArea.getHeight() * 0.3);
	lightUpArea.setWidth(buttonArea.getWidth() * 0.7);
	lightUpArea.setCentre(buttonArea.getCentreX(), buttonArea.getCentreY());

	g.setColour(lightColor);
	g.fillRect(lightUpArea);

}
