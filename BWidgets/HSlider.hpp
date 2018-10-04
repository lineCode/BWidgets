#ifndef BWIDGETS_HSLIDER_HPP_
#define BWIDGETS_HSLIDER_HPP_

#include "RangeWidget.hpp"

namespace BWidgets
{
/**
 * Class BWidgets::HSlider
 *
 * RangeWidget class for a horizontal slider
 */
class HSlider : public RangeWidget
{
public:
	HSlider ();
	HSlider (const double x, const double y, const double width, const double height, const std::string& name,
			 const double value, const double min, const double max, const double step);
	~HSlider ();

	/**
	 * Scans theme for widget properties and applies these properties.
	 * @param theme Theme to be scanned
	 */
	virtual void applyTheme (BStyles::Theme& theme);

	/**
	 * Scans theme for widget properties and applies these properties.
	 * @param theme Theme to be scanned
	 * @param name Name of the BStyles::StyleSet within the theme to be
	 * 		  	   applied.
	 */
	virtual void applyTheme (BStyles::Theme& theme, const std::string& name);

	/**
	 * Handles the BEvents::BUTTON_PRESS_EVENT to move the slider.
	 * @param event Pointer to a poiter event emitted by the same widget.
	 */
	virtual void onButtonPressed (BEvents::PointerEvent* event) override;

	/**
	 * Handles the BEvents::BUTTON_PRESS_EVENT to move the slider.
	 * @param event Pointer to a poiter event emitted by the same widget.
	 */
	virtual void onPointerMotionWhileButtonPressed (BEvents::PointerEvent* event) override;

protected:
	virtual void draw () override;
	virtual void draw (const double x, const double y, const double width, const double height) override;

	BColors::ColorSet fgColors;
	BColors::ColorSet bgColors;
};

}

#endif /* BWIDGETS_HSLIDER_HPP_ */
