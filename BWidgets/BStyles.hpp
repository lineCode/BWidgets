/* Copyright (C) 2018 by Sven Jähnichen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef BSTYLES_HPP_
#define BSTYLES_HPP_

#include <stdint.h>
#include <cstring>
#include <string>
#include <cairo/cairo.h>
#include "cairoplus.h"
#include <iostream>

#include "BColors.hpp"

#define STYLEPTR(ptr) (void*) (ptr)

namespace BStyles
{
/**
 * Class BStyles::Line
 *
 * Line style class. A BStyles::Line is defined by its color, width and
 * TODO dashes
 */
class Line
{
public:
	Line ();
	Line (BColors::Color color, double width);
	~Line ();

	/**
	 * Sets color of the line style
	 * @param color BColors::Color
	 */
	void setColor (BColors::Color color);

	/**
	 * Gets (a pointer to the) color of the line style
	 * @return Returns BColors::Color.
	 */
	const BColors::Color* getColor ();

	/**
	 * Sets width of the line
	 * @param width Width of the line in pt.
	 */
	void setWidth (double width);

	/**
	 * Gets width of the line
	 * @return Width of the line in pt.
	 */
	double getWidth ();

private:
	BColors::Color lineColor;
	int lineWidth;
};
/*
 * End of class BWidgets::Line
 *****************************************************************************/

const Line blackLine1pt = Line (BColors::black, 1.0);
const Line whiteLine1pt = Line (BColors::white, 1.0);
const Line noLine = Line (BColors::invisible, 0.0);


/**
 * Class BStyles::Border
 *
 * Border style class. A BStyles::Border is defined by its margin, padding,
 * line and corner radius
 */
class Border
{
public:
	Border ();
	Border (Line line);
	Border (Line line, double margin, double padding);
	Border (Line line, double margin, double padding, double radius);
	~Border ();

	/**
	 * Sets the line of a border style
	 * @param line BStyles::Line
	 */
	void setLine (Line line);

	/**
	 * Gets the line of a border style
	 * @return BStyles::Line
	 */
	Line getLine ();

	/**
	 * Sets the margin of a border style
	 * @param margin Distance from border line to the outer limits of the
	 * 				 border.
	 */
	void setMargin (double margin);

	/**
	 * Gets the margin of a border style
	 * @return Distance from border line to the outer limits of the border.
	 */
	double getMargin ();

	/**
	 * Sets the padding of a border style
	 * @param padding Distance from border line to the inner limits of the
	 * 				  border.
	 */
	void setPadding (double padding);

	/**
	 * Gets the padding of a border style
	 * @return Distance from border line to the inner limits of the border.
	 */
	double getPadding ();

	/**
	 * Sets the radius of the corners of a border style
	 * @param radius Radius of the corners. If (radius != 0), the corners will
	 * 				 be rounded.
	 */
	void setRadius (double radius);

	/**
	 * Gets the radius of the corners of a border style
	 * @param radius Radius of the corners.
	 */
	double getRadius ();

protected:
	Line borderLine;
	double borderRadius;
	double borderPadding;
	double borderMargin;
};
/*
 * End of class BWidgets::Border
 *****************************************************************************/

const Border blackBorder1pt = Border (blackLine1pt);
const Border whiteBorder1pt = Border (whiteLine1pt);
const Border noBorder = Border (noLine);



/**
 * Class BStyles::Fill
 *
 * Fill style class. A BStyles::Fill can be a plain color or a Cairo image
 * surface (higher priority).
 */
class Fill
{
public:
	Fill ();
	Fill (BColors::Color color);
	Fill (std::string filename);
	Fill (const Fill& that);
	Fill& operator= (const Fill& that);
	~Fill ();

	/**
	 * Sets the color of a fill style
	 * @param color BColors::Color
	 */
	void setColor (BColors::Color color);

	/**
	 * Gets (a pointer to) the color of a fill style
	 * @return BColors::Color
	 */
	const BColors::Color* getColor ();

	/**
	 * Loads a PNG file into a Cairo image surface and uses it for the fill
	 * style.
	 * @param filename File name of the PNG file
	 */
	void loadFillFromFile (std::string filename);

	/**
	 * Copies a Cairo image surface and uses it for the fill style.
	 * @param surface Pointer to the source cairo image surface
	 */
	void loadFillFromCairoSurface (cairo_surface_t* surface);

	//TODO purgeFillSurface ();

	/**
	 * Gets a pointer to the cairo image surface used for the fill style.
	 * @return Pointer to a cairo image surface or nullptr if no surface is
	 * 		   used (plain color mode).
	 */
	cairo_surface_t* getCairoSurface ();


protected:
	BColors::Color fillColor;
	cairo_surface_t* fillSurface;

};
/*
 * End of class BWidgets::Fill
 *****************************************************************************/

const Fill blackFill = Fill (BColors::black);
const Fill whiteFill = Fill (BColors::white);
const Fill redFill = Fill (BColors::red);
const Fill greenFill = Fill (BColors::green);
const Fill blueFill = Fill (BColors::blue);
const Fill greyFill = Fill (BColors::grey);
const Fill noFill = Fill (BColors::invisible);


/**
 * Class BStyles::Font
 *
 * Font style class. A BStyles::Font is defined by the Cairo font properties
 * font family, slant, weight and its size
 */
class Font
{
public:
	Font ();
	Font (std::string family, cairo_font_slant_t slant, cairo_font_weight_t weight, double size);
	~Font ();

	/**
	 * Sets font family of the font style
	 * @param family Cairo font family name (as std::string)
	 */
	void setFontFamily (std::string family);

	/**
	 * Gets font family of the font style
	 * @return Cairo font family name (as std::string)
	 */
	std::string getFontFamily ();

	/**
	 * Sets font slant of the font style
	 * @param slant Cairo font slant
	 */
	void setFontSlant (cairo_font_slant_t slant);

	/**
	 * Gets font slant of the font style
	 * @return Cairo font slant
	 */
	cairo_font_slant_t getFontSlant ();

	/**
	 * Sets font weight of the font style
	 * @param weight Cairo font weight
	 */
	void setFontWeight (cairo_font_weight_t weight);

	/**
	 * Gets font weight of the font style
	 * @return Cairo font weight
	 */
	cairo_font_weight_t getFontWeight ();

	/**
	 * Sets font size of the font style
	 * @param size Font size as used by Cairo
	 */
	void setFontSize (double size);

	/**
	 * Gets font size of the font style
	 * @return Font size as used by Cairo
	 */
	double getFontSize ();

	/**
	 * Gets the output dimensions of a text
	 * @param cr Pointer to a Cairo context that will be used to calculate the
	 * 			 output dimensions of the text.
	 * @param text Text to calculate output dimensions for.
	 * @return Output dimensions as Cairo text extents.
	 */
	cairo_text_extents_t getTextExtents (cairo_t* cr, std::string text);

private:
	std::string fontFamily;
	cairo_font_slant_t fontSlant;
	cairo_font_weight_t fontWeight;
	double fontSize;

};

/*
 * End of class BWidgets::Font
 *****************************************************************************/

const Font sans12pt = Font ("Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0);;


/**
 * Struct BStyles::Style
 *
 * A style is defined by its name and (a pointer to) a style element (e.g.,
 * BColors::Color, BColors::ColorSet, BStyle::Line, BStyle::Border,
 * BStyle::Fill, BStyle::Font).
 */
typedef struct {
	std::string name;
	void* stylePtr;
} Style;

/**
 * Class BStyles::StyleSet
 *
 * A BStyles::StyleSet is a collection of different styles (and therefore
 * different style elements). The BStyles::StyleSet itself is defined by its
 * name. A BStyles::StyleSet is intended to be used for an object (like a
 * BWidgets::Widget) to set up its properties.
 *
 * For example, a BStyles::StyleSet can look like this:
 * {"example", {{"color", &BColors::white},
 * 				{"border", &BStyles::noBorder},
 * 				{"font", &BStyles::sans12pt}
 * 			   }
 * }
 *
 * Feature:
 * The style name "uses" means that another BStyles::StyleSet (to which
 * Style.ptr points to) is used to this (pre-)define BStyles::StyleSet.
 */
class StyleSet {
public:
	StyleSet ();
	StyleSet (std::string name, std::vector<Style> styles);
	~StyleSet ();

	/**
	 * Adds a style to (or overwrites an existing of) the BStyles::StyleSet.
	 * @param styleName Name of the style to be added or overwritten.
	 * @param ptr Pointer to the style element.
	 */
	void addStyle (std::string styleName, void* ptr);

	//TODO void addStyle (Style& style);

	/**
	 * Removes an existing style from the BStyles::StyleSet.
	 * @param styleName Name of the style to be removed from the
	 * 					BStyles::StyleSet.
	 * TODO throws style doesn't exist
	 */
	void removeStyle (std::string styleName);

	/**
	 * Gets a pointer to an existing style from the BStyles::StyleSet.
	 * @param styleName Name of the style.
	 * TODO throws style doesn't exist
	 */
	void* getStyle (std::string styleName);

	/**
	 * Sets the name of the BStyles::StyleSet
	 * @param name Name of the BStyles::StyleSet.
	 */
	void setName (std::string name);

	/**
	 * Gets the name of the BStyles::StyleSet
	 * @return Name of the BStyles::StyleSet
	 */
	std::string getName ();

protected:
	std::string stylesetName;
	std::vector<Style> styleVector;
};
/*
 * End of class BWidgets::StyleSet
 *****************************************************************************/

/**
 * Class BStyles::Theme
 *
 * A BStyles::Theme is a collection of different BStyles::StyleSets. A theme is
 * intended to be used set up all properties of objects (like a GUI based on
 * BWidgets) at once.
 */
class Theme
{
public:
	Theme ();
	Theme (std::vector<StyleSet> theme);
	~Theme ();

	/**
	 * Adds (or overwrites an existing) style to an BStyles::StyleSet
	 * within the Theme. If the respective BStyles::StyleSet doesn't
	 * exist yet, it will be created.
	 * @param setName Name of the BStyles::StyleSet
	 * @param styleName Name of the BStyles::Style
	 * @param ptr Pointer to the style element
	 */
	void addStyle (std::string setName, std::string styleName, void* ptr);

	//TODO void addStyle (Style style);
	//TODO void addStyleSet (StyleSet styleSet);
	//TODO StyleSet* getStyleSet (std::string setName);

	/**
	 * Removes an existing style.
	 * @param setName Name of the BStyles::StyleSet
	 * @param styleName Name of the style to be removed.
	 * TODO throws style doesn't exist
	 */
	void removeStyle (std::string setName, std::string styleName);

	/**
	 * Gets an existing style.
	 * @param setName Name of the BStyles::StyleSet
	 * @param styleName Name of the style to be removed.
	 * TODO throws style doesn't exist
	 */
	void* getStyle (std::string setName, std::string styleName);

protected:
	std::vector<StyleSet> stylesetVector;
};
/*
 * End of class BWidgets::Theme
 *****************************************************************************/

}

#endif /* BSTYLES_HPP_ */
