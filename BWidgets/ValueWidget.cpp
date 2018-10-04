#include "ValueWidget.hpp"

namespace BWidgets
{
ValueWidget::ValueWidget () : ValueWidget (0, 0, 200, 200, "ValueWidget", 0.0) {}

ValueWidget::ValueWidget (const double  x, const double y, const double width, const double height, const std::string& name, const double value) :
		Widget (x, y, width, height, name), value (value) {}

ValueWidget::~ValueWidget () {}

void ValueWidget::setValue (const double val)
{
	if (val != value)
	{
		value = val;
		draw ();
		postValueChanged ();
		if (isVisible ()) postRedisplay ();
	}
}

double ValueWidget::getValue () const {return value;}

void ValueWidget::onValueChanged (BEvents::ValueChangedEvent* event)
{
	cbfunction[BEvents::EventType::VALUE_CHANGED_EVENT] (event);
}

void ValueWidget::postValueChanged ()
{
	if (main_)
	{
		BEvents::ValueChangedEvent* event = new BEvents::ValueChangedEvent (this, value);
		main_->addEventToQueue (event);
	}
}

}
