#include "Text.hpp"

namespace BWidgets
{
Text::Text () : Text (0.0, 0.0, 0.0, 0.0, "Text") {}

Text::Text (const std::string& text) : Text (0.0, 0.0, 200.0, 20.0, text) {}

Text::Text (const double x, const double y, const double width, const double height, const std::string& text) :
		Widget (x, y, width, height, text), textColors (BColors::whites), textFont (BStyles::sans12pt), textString (text) {}

Text::Text (const Text& that) : Widget (that)
{
	textColors = that.textColors;
	textFont = that.textFont;
	textString = that.textString;

	draw (0, 0, width_, height_);
}

Text::~Text () {}

Text& Text::operator= (const Text& that)
{
	textColors = that.textColors;
	textFont = that.textFont;
	textString = that.textString;
	Widget::operator= (that);
	return *this;
}

void Text::setText (const std::string& text)
{
	if (text != textString)
	{
		textString = text;
		update ();
	}
}
std::string Text::getText () const {return textString;}

void Text::setTextColors (const BColors::ColorSet& colorset)
{
	textColors = colorset;
	update ();
}
BColors::ColorSet* Text::getTextColors () {return &textColors;}

void Text::setFont (const BStyles::Font& font)
{
	textFont = font;
	update ();
}
BStyles::Font* Text::getFont () {return &textFont;}

void Text::update ()
{
	draw (0, 0, width_, height_);
	if (isVisible ()) postRedisplay ();
}

void Text::applyTheme (BStyles::Theme& theme) {applyTheme (theme, name_);}

void Text::applyTheme (BStyles::Theme& theme, const std::string& name)
{
	Widget::applyTheme (theme, name);

	// Color
	void* colorsPtr = theme.getStyle(name, "textcolors");
	if (colorsPtr) textColors = *((BColors::ColorSet*) colorsPtr);

	// Font
	void* fontPtr = theme.getStyle(name, "font");
	if (fontPtr) textFont = *((BStyles::Font*) fontPtr);

	if (colorsPtr || fontPtr) update ();
}



void Text::draw (const double x, const double y, const double width, const double height)
{
	// Draw super class widget elements first
	Widget::draw (x, y, width, height);

	cairo_t* cr = cairo_create (widgetSurface);

	if (cairo_status (cr) == CAIRO_STATUS_SUCCESS)
	{
		// Limit cairo-drawing area
		cairo_rectangle (cr, x, y, width, height);
		cairo_clip (cr);

		double xoff = getXOffset ();
		double yoff = getYOffset ();
		double w = getEffectiveWidth ();
		double h = getEffectiveHeight ();

		BColors::Color lc = *textColors.getColor (BColors::NORMAL);
		cairo_set_source_rgba (cr, lc.getRed (), lc.getGreen (), lc.getBlue (), lc.getAlpha ());
		cairo_select_font_face (cr, textFont.getFontFamily ().c_str (), textFont.getFontSlant (), textFont.getFontWeight ());
		cairo_set_font_size (cr, textFont.getFontSize ());
		cairo_text_decorations decorations = {textFont.getFontFamily ().c_str (), textFont.getFontSize (), textFont.getFontSlant (), textFont.getFontWeight ()};

		struct TextLine
		{
			std::string text = "";
			double xpos = 0;
			double ypos = 0;
		} textline;
		std::vector<TextLine> textblock;

		char* textCString = (char*) malloc (strlen (textString.c_str ()) + 1);
		if (textCString)
		{
			strcpy (textCString, textString.c_str ());

			// Scan text -> textblock
			for (double y0 = 0; (y0 <= h) && (strlen (textCString) > 0); )
			{
				char* outputtext = cairo_create_text_fitted (cr, w, decorations, textCString);
				cairo_text_extents_t ext = textFont.getTextExtents(cr, outputtext);

				switch (textFont.getTextAlign ())
				{
				case BStyles::TEXT_ALIGN_LEFT:		textline.xpos = - ext.x_bearing;
													break;
				case BStyles::TEXT_ALIGN_CENTER:	textline.xpos = w / 2 - ext.width / 2 - ext.x_bearing;
													break;
				case BStyles::TEXT_ALIGN_RIGHT:		textline.xpos = w - ext.width - ext.x_bearing;
													break;
				default:							textline.xpos = 0;
				}

				textline.text = std::string (outputtext);
				textline.ypos = y0 - ext.y_bearing;
				cairo_text_destroy (outputtext);
				textblock.push_back (textline);
				y0 += (ext.height * textFont.getLineSpacing ());
			}

			// Calculate vertical alignment of the textblock
			uint32_t blocksize = textblock.size ();
			double blockheight = textblock.back ().ypos;
			double y0 = 0;
			switch (textFont.getTextVAlign ())
			{
			case BStyles::TEXT_VALIGN_TOP:		y0 = 0;
												break;
			case BStyles::TEXT_VALIGN_MIDDLE:	y0 = h / 2 - blockheight / 2;
												break;
			case BStyles::TEXT_VALIGN_BOTTOM:	y0 = h - blockheight;
												break;
			default:							y0 = 0;
			}

			// Output of textblock
			for (TextLine textline : textblock)
			{
				cairo_move_to (cr, xoff + textline.xpos, yoff + y0 + textline.ypos);
				cairo_show_text (cr, textline.text.c_str ());
			}

			free (textCString);
		}
	}

	cairo_destroy (cr);
}

}
