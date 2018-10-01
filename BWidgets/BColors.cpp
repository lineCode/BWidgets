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

#include "BColors.hpp"

#ifndef LIMIT
#define LIMIT(val, min, max) (val < min ? min : (val < max ? val : max))
#endif

namespace BColors
{

/*****************************************************************************
 * Class BColors::Color
 *****************************************************************************/

Color::Color () : Color (0.0, 0.0, 0.0, 0.0) {};

Color::Color (double red, double green, double blue, double alpha) :
		red_ (LIMIT (red, 0.0, 1.0)), green_ (LIMIT (green, 0.0, 1.0)), blue_ (LIMIT (blue, 0.0, 1.0)), alpha_ (LIMIT (alpha, 0.0, 1.0)) {}

Color::Color (uint32_t red32, uint32_t green32, uint32_t blue32, uint32_t alpha32) :
		red_ (red32 / 0xFFFF), green_ (green32 / 0xFFFF), blue_ (blue32 / 0xFFFF), alpha_ (alpha32 / 0xFFFF) {}

Color:: ~Color () {}

void Color::setRGBA (double red, double green, double blue, double alpha)
{

	red_ = LIMIT (red, 0.0, 1.0);
	green_ = LIMIT (green, 0.0, 1.0);
	blue_ = LIMIT (blue, 0.0, 1.0);
	alpha_ = LIMIT (alpha, 0.0, 1.0);
}

void Color::setRGB (double red, double green, double blue)
{
	red_ = LIMIT (red, 0.0, 1.0);
	green_ = LIMIT (green, 0.0, 1.0);
	blue_ = LIMIT (blue, 0.0, 1.0);
}

void Color::setAlpha (double alpha)
{
	alpha_ = LIMIT (alpha, 0.0, 1.0);
}

double Color::getRed() {return red_;}
double Color::getGreen() {return green_;}
double Color::getBlue() {return blue_;}
double Color::getAlpha() {return alpha_;}

/*
 * End of class BColors::Color
 *****************************************************************************/

/*****************************************************************************
 * Class BColors::ColorSet
 *****************************************************************************/

ColorSet::ColorSet () : ColorSet ({grey, lightgrey, darkgrey}) {};
ColorSet::ColorSet (std::vector<Color> vectorOfColors) : colors (vectorOfColors) {};
ColorSet::~ColorSet () {};

void ColorSet::addColor (State state, Color color)
{
	// Filling undefined vector elements with Color invisible
	int size = colors.size ();
	for (int i = size; i <= (int) state; ++i) colors.push_back (invisible);

	colors[state] = color;
}

void ColorSet::removeColor (State state)
{
	if (state < colors.size ())
	{
		colors[state] = invisible;
	}

	// TODO shrink vector colors if last element is removed
}

const Color* ColorSet::getColor (State state)
{
	if (state < colors.size ())
	{
		return &colors[state];
	}
	else return &invisible;
}

/*
 * End of class BColors::ColorSet
 *****************************************************************************/

}
