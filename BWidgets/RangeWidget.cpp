#include "RangeWidget.hpp"

#ifndef LIMIT
#define LIMIT(val, min, max) (val < min ? min : (val < max ? val : max))
#endif

namespace BWidgets
{
RangeWidget::RangeWidget () : RangeWidget (0.0, 0.0, 200.0, 200.0, "RangeWidget", 0.0, 0.0, 100.0, 0.0) {}

RangeWidget::RangeWidget (double  x, double y, double width, double height, std::string name, double value, double min, double max, double step) :
		ValueWidget (x, y, width, height, name, value), rangeMin (min <= max ? min : max),
		rangeMax (max), rangeStep (step)
{
	this->value = LIMIT (value, min, max);
}

RangeWidget::~RangeWidget () {}

void RangeWidget::setValue (double val)
{
	double valRounded = val;
	if ((rangeStep != 0.0) && (rangeMax >= rangeMin))
	{
		if (rangeStep > 0.0) valRounded = LIMIT (rangeMin + round ((val - rangeMin) / rangeStep) * rangeStep, rangeMin, rangeMax);
		else valRounded = LIMIT (rangeMax - round ((rangeMax - val) / rangeStep) * rangeStep, rangeMin, rangeMax);
	}
	ValueWidget::setValue (valRounded);
}

void RangeWidget::setMin (double min)
{
	double newMin = (min <= rangeMax ? min: rangeMax);
	if (rangeMin != newMin)
	{
		rangeMin = newMin;
		if (getValue () < rangeMin) setValue (rangeMin);
		else if (isVisible ()) postRedisplay ();
	}
}

double RangeWidget::getMin () {return rangeMin;}

void RangeWidget::setMax (double max)
{
	double newMax = (max >= rangeMin ? max: rangeMin);
	if (rangeMax != newMax)
	{
		rangeMax = newMax;
		if (getValue () > rangeMax) setValue (rangeMax);
		else if (isVisible ()) postRedisplay ();
	}
}

double RangeWidget::getMax () {return rangeMax;}

void RangeWidget::setStep (double step) {rangeStep = step;}

double RangeWidget::getStep () {return rangeStep;}


}
