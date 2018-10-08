#include "TextToggleButton.hpp"

namespace BWidgets
{
TextToggleButton::TextToggleButton () : TextToggleButton (0.0, 0.0, 50.0, 50.0, "dial", 0.0) {}

TextToggleButton::TextToggleButton (const double x, const double y, const double width, const double height, const std::string& name, const double defaultValue) :
		ToggleButton (x, y, width, height, name, defaultValue), buttonLabel (0, 0, width - 2, height - 2, name)
{
	setValue (defaultValue);
	buttonLabel.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, TextToggleButton::redirectPostButtonPressed);
	add (buttonLabel);
}

TextToggleButton:: ~TextToggleButton () {}

void TextToggleButton::setValue (const double val)
{
	if (val) buttonLabel.moveTo (2, 2);
	else buttonLabel.moveTo (0, 0);
	ToggleButton::setValue (val);
}

Label* TextToggleButton::getLabel () {return &buttonLabel;}

void TextToggleButton::applyTheme (BStyles::Theme& theme) {applyTheme (theme, name_);}
void TextToggleButton::applyTheme (BStyles::Theme& theme, const std::string& name)
{
	ToggleButton::applyTheme (theme, name);
	buttonLabel.applyTheme (theme, name);
	update ();
}

void TextToggleButton::redirectPostButtonPressed (BEvents::Event* event)
{

	BEvents::PointerEvent* ev = (BEvents::PointerEvent*) event;
	if ((ev) && (ev->getWidget ()))
	{
		Widget* w = (Widget*) ev->getWidget();
		TextToggleButton* p = (TextToggleButton*) w->getParent();
		if ((p) && (p->main_))
		{
			BEvents::PointerEvent* newEvent = new BEvents::PointerEvent (p, BEvents::BUTTON_PRESS_EVENT, ev->getX (), ev->getY (), ev->getButton ());
			p->main_->addEventToQueue ((BEvents::Event*) newEvent);
		}
	}
}

}
