#ifndef BWIDGETS_VALUEWIDGET_HPP_
#define BWIDGETS_VALUEWIDGET_HPP_

#include "Widget.hpp"

namespace BWidgets
{

/**
 * Class BWidgets::ValueWidget
 *
 * Root class for all widgets that deal with values (dials, sliders, ...).
 */
class ValueWidget : public Widget
{
public:
	ValueWidget ();
	ValueWidget (double  x, double y, double width, double height, std::string name, double value);
	~ValueWidget ();

	/**
	 * Changes the value of the widget. Emits a value changed event and (if
	 * visible) an expose event.
	 * @param val Value
	 */
	virtual void setValue (double val);

	/**
	 * Gets the value of the widget.
	 * @return Value
	 */
	double getValue ();

	/**
	 * Handler for BEvents::ValueChangedEvent. Simply calls the callback
	 * function defined using setCallbackFunction.
	 */
	virtual void onValueChanged (BEvents::ValueChangedEvent* event) override;

protected:
	void postValueChanged ();
	double value;
};

}

#endif /* BWIDGETS_VALUEWIDGET_HPP_ */
