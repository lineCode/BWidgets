#ifndef BWIDGETS_HSLIDERWITHVALUEDISPLAY_HPP_
#define BWIDGETS_HSLIDERWITHVALUEDISPLAY_HPP_

#include "RangeWidget.hpp"
#include "Label.hpp"
#include "HSlider.hpp"

namespace BWidgets
{
/**
 * Enumeration of positions where the value should appear
 */
typedef enum {
	ON_TOP,
	ON_BOTTOM,
	ON_LEFT,
	ON_RIGHT
} ValueDisplayPosition;


/**
 * Class BWidgets::HSliderWithValueDisplay
 *
 * Composite RangeWidget consisting of a horizontal slider and a label widget.
 */
class HSliderWithValueDisplay : public RangeWidget
{
public:
	HSliderWithValueDisplay ();
	HSliderWithValueDisplay (const double x, const double y, const double width, const double height, const std::string& name,
			  	  	  	  	 const double value, const double min, const double max, const double step,
							 const std::string& valueFormat, const ValueDisplayPosition position);
	~HSliderWithValueDisplay ();

	/**
	 * Sets the value output format.
	 * @valueFormat Format of the output in printf standard for type double.
	 */
	void setValueFormat (const std::string& valueFormat);

	/**
	 * Gets the value output format.
	 * @return Format of the output in printf standard for type double.
	 */
	std::string getValueFormat () const;

	/**
	 * Sets the position where the value should appear
	 * @param position Enumeration of position
	 */
	void setValuePosition (const ValueDisplayPosition position);

	/**
	 * Gets the position where the value should appear
	 * @return Enumeration of position
	 */
	ValueDisplayPosition getValuePosition () const;

	/**
	 * Gets (a pointer to) the slider widget for direct access
	 * @return Pointer to BWidgets::HSlider
	 */
	HSlider* getSlider ();

	/**
	 * Gets (a pointer to) the Label for direct access.
	 * @return Pointer to the label
	 */
	Label* getValueDisplay ();

	/**
	 * Scans theme for widget properties and applies these properties.
	 * @param theme Theme to be scanned.
	 * 				For styles used see BWidgets::Dial::applyTheme and
	 * 				BWidgets::Label::applyTheme.
	 * @param name Name of the BStyles::StyleSet within the theme to be
	 * 		  	   applied.
	 */
	virtual void applyTheme (BStyles::Theme& theme);
	virtual void applyTheme (BStyles::Theme& theme, const std::string& name);

protected:
	static void redirectPostValueChanged (BEvents::Event* event);
	void updateChildCoords ();
	virtual void draw () override;
	virtual void draw (const double x, const double y, const double width, const double height) override;

	HSlider slider;
	Label valueDisplay;

	std::string valFormat;
	ValueDisplayPosition valPosition;
};

}

#endif /* BWIDGETS_HSLIDERWITHVALUEDISPLAY_HPP_ */
