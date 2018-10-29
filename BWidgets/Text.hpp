#ifndef BWIDGETS_TEXT_HPP_
#define BWIDGETS_TEXT_HPP_

#include "Widget.hpp"

namespace BWidgets
{

/**
 * Class BWidgets::Text
 *
 * Text output widget with line breaks. Line breaks occur
 * (i) on "\n" or
 * (ii) on spaces when text length exceed the widget width or
 * (iii) on any position when text length exceed the widget width.
 */
class Text : public Widget
{
public:
	Text ();
	Text (const std::string& text);
	Text (const double x, const double y, const double width, const double height, const std::string& text);

	/**
	 * Creates a new (orphan) text widget and copies the text widget properties
	 * from a source text widget. This method doesn't copy any parent or child
	 * widgets.
	 * @param that Source text widget
	 */
	Text (const Text& that);

	~Text ();

	/**
	 * Assignment. Copies the text widget properties from a source text widget
	 *  and keeps its name and its position within the widget tree. Emits a
	 * BEvents::ExposeEvent if the text widget is visible.
	 * @param that Source text widget
	 */
	Text& operator= (const Text& that);

	/**
	 * Sets the output text.
	 * @param text Output text
	 */
	void setText (const std::string& text);

	/**
	 * Gets the output text
	 * @return Output text
	 */
	std::string getText () const;

	/**
	 * Sets the BColors::ColorSet for this widget
	 * @param colors Color set.
	 */
	void setTextColors (const BColors::ColorSet& colorset);

	/**
	 * Gets (a pointer to) the BColors::ColorSet of this widget.
	 * @return Pointer to the color set.
	 */
	BColors::ColorSet* getTextColors ();

	/**
	 * Sets the font for the text output.
	 * @param font Font
	 */
	void setFont (const BStyles::Font& font);

	/**
	 * Gets (a pointer to) the font for the text output.
	 * @return Pointer to font
	 */
	BStyles::Font* getFont ();

	/**
	 * Calls a redraw of the widget and calls postRedisplay () if the the
	 * Widget is visible.
	 * This method should be called if the widgets properties are indirectly
	 * changed.
	 */
	virtual void update () override;

	/**
	 * Scans theme for widget properties and applies these properties.
	 * @param theme Theme to be scanned.
	 * 				Styles used are:
	 * 				"textcolors" for BColors::ColorSet
	 * 				"font" for BStyles::Font
	 * @param name Name of the BStyles::StyleSet within the theme to be
	 * 		  	   applied.
	 */
	virtual void applyTheme (BStyles::Theme& theme);
	virtual void applyTheme (BStyles::Theme& theme, const std::string& name);

protected:
	virtual void draw (const double x, const double y, const double width, const double height) override;

	BColors::ColorSet textColors;
	BStyles::Font textFont;
	std::string textString;
};

}

#endif /* BWIDGETS_TEXT_HPP_ */
