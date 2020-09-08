#include "ButtonLookAndFeel.h"

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
