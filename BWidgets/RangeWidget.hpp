#ifndef BWIDGETS_RANGEWIDGET_HPP_
#define BWIDGETS_RANGEWIDGET_HPP_

#include <math.h>
#include "ValueWidget.hpp"

namespace BWidgets
{
/**
 * Class BWidgets::RangeWidget
 *
 * Root class for all widget with a value that should kept in a range.
 */
class RangeWidget : public ValueWidget
{
public:
	RangeWidget ();
	RangeWidget (double  x, double y, double width, double height, std::string name, double value, double min, double max, double step);
	~RangeWidget ();

	/**
	 * Changes the value of the widget and keeps it within the defined range.
	 * Emits a value changed event and (if visible) an expose event.
	 * @param val Value
	 */
	virtual void setValue (double val) override;

	/**
	 * Sets the lower limit. Forces the value into the new range. Emits a value
	 * changed event (if value changed) and (if visible) an expose event.
	 * @param min Lower limit
	 */
	void setMin (double min);

/**
	 * Gets the lower limit.
	 * @return Lower limit
	 */
	double getMin ();

	/**
	 * Sets the upper limit. Forces the value into the new range. Emits a value
	 * changed event (if value changed) and (if visible) an expose event.
	 * @param max Upper limit
	 */
	void setMax (double max);

	/**
	 * Gets the upper limit.
	 * @return Upper limit
	 */
	double getMax ();

	/**
	 * Sets the increment steps for the value.
	 * @param step Increment steps.
	 * 			   A positive value means that increments start from the lower
	 * 			   limit to the upper limit.
	 * 			   0.0 menas stepless increments.
	 * 			   A negative value however means that decrements start from
	 * 			   the upper to the lowe limit. A negative value may also cause
	 * 			   display of dependent widgets (dials, sliders, ... ) in the
	 * 			   opposite direction.
	 */
	void setStep (double step);

	/**
	 * Gets the increment steps for the value.
	 * @return Increment steps.
	 */
	double getStep ();

protected:
	double rangeMin;
	double rangeMax;
	double rangeStep;

};

}

#endif /* BWIDGETS_RANGEWIDGET_HPP_ */
