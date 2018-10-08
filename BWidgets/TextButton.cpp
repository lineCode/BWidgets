#include "TextButton.hpp"

namespace BWidgets
{
TextButton::TextButton () : TextButton (0.0, 0.0, 50.0, 50.0, "dial", 0.0) {}

TextButton::TextButton (const double x, const double y, const double width, const double height, const std::string& name, const double defaultValue) :
		Button (x, y, width, height, name, defaultValue), buttonLabel (0, 0, width - 2, height - 2, name)
{
	setValue (defaultValue);
	buttonLabel.setCallbackFunction (BEvents::EventType::BUTTON_PRESS_EVENT, TextButton::redirectPostButtonPressed);
	buttonLabel.setCallbackFunction (BEvents::EventType::BUTTON_RELEASE_EVENT, TextButton::redirectPostButtonReleased);
	add (buttonLabel);
}

TextButton:: ~TextButton () {}

void TextButton::setValue (const double val)
{
	if (val) buttonLabel.moveTo (2, 2);
	else buttonLabel.moveTo (0, 0);
	Button::setValue (val);
}

Label* TextButton::getLabel () {return &buttonLabel;}

void TextButton::applyTheme (BStyles::Theme& theme) {applyTheme (theme, name_);}
void TextButton::applyTheme (BStyles::Theme& theme, const std::string& name)
{
	Button::applyTheme (theme, name);
	buttonLabel.applyTheme (theme, name);
	update ();
}

void TextButton::redirectPostButtonPressed (BEvents::Event* event)
{

	BEvents::PointerEvent* ev = (BEvents::PointerEvent*) event;
	if ((ev) && (ev->getWidget ()))
	{
		Widget* w = (Widget*) ev->getWidget();
		TextButton* p = (TextButton*) w->getParent();
		if ((p) && (p->main_))
		{
			BEvents::PointerEvent* newEvent = new BEvents::PointerEvent (p, BEvents::BUTTON_PRESS_EVENT, ev->getX (), ev->getY (), ev->getButton ());
			p->main_->addEventToQueue ((BEvents::Event*) newEvent);
		}
	}
}

void TextButton::redirectPostButtonReleased (BEvents::Event* event)
{

	BEvents::PointerEvent* ev = (BEvents::PointerEvent*) event;
	if ((ev) && (ev->getWidget ()))
	{
		Widget* w = (Widget*) ev->getWidget();
		TextButton* p = (TextButton*) w->getParent();
		if ((p) && (p->main_))
		{
			BEvents::PointerEvent* newEvent = new BEvents::PointerEvent (p, BEvents::BUTTON_RELEASE_EVENT, ev->getX (), ev->getY (), ev->getButton ());
			p->main_->addEventToQueue ((BEvents::Event*) newEvent);
		}
	}
}


}
