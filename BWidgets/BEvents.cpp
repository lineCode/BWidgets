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

#include "BEvents.hpp"

namespace BEvents
{
/*****************************************************************************
 * Class BEvents::Event
 *****************************************************************************/

Event:: Event () : Event ((void*) nullptr, NO_EVENT) {}
Event::Event (void* widget, EventType type) : eventWidget (widget), eventType (type) {}
Event::~Event () {}
void* Event::getWidget () {return eventWidget;}
EventType Event::getEventType () {return eventType;}

/*
 * End of class BEvents::Event
 *****************************************************************************/


/*****************************************************************************
 * Class BEvents::ExposeEvent
 *****************************************************************************/

ExposeEvent::ExposeEvent () : ExposeEvent ((void*) nullptr, 0, 0, 0, 0) {}
ExposeEvent::ExposeEvent (void* widget, double x, double y, double width, double height) :
		Event (widget, EXPOSE_EVENT), exposeX0 (x), exposeY0 (y), exposeHeight (height), exposeWidth (width) {}
ExposeEvent::~ExposeEvent () {}
void ExposeEvent::setX (double x) {exposeX0 = x;}
double ExposeEvent::getX () {return exposeX0;}
void ExposeEvent::setY (double y) {exposeY0 = y;}
double ExposeEvent::getY () {return exposeY0;}
void ExposeEvent::setWidth (double width) {exposeWidth = width;}
double ExposeEvent::getWidth () {return exposeWidth;}
void ExposeEvent::setHeight (double height) {exposeHeight = height;}
double ExposeEvent::getHeight () {return exposeHeight;}

/*
 * End of class BEvents::ExposeEvent
 *****************************************************************************/


/*****************************************************************************
 * Class BEvents::PointerEvent
 *****************************************************************************/

PointerEvent::PointerEvent () : PointerEvent ((void*) nullptr, NO_EVENT, 0, 0, NO_BUTTON) {}
PointerEvent::PointerEvent (void* widget, EventType type, double x, double y, InputDevice button) :
		Event (widget, type), xpos (x), ypos (y), buttonNr (button) {}
PointerEvent::~PointerEvent () {}
void PointerEvent::setX (double x) {xpos = x;}
double PointerEvent::getX () {return xpos;}
void PointerEvent::setY (double y) {ypos = y;}
double PointerEvent::getY () {return ypos;}
void PointerEvent::setButton (InputDevice button) {buttonNr = button;}
InputDevice PointerEvent::getButton () {return buttonNr;}

/*
 * End of class BEvents::PointerEvent
 *****************************************************************************/


/*****************************************************************************
 * Class BEvents::ValueChangedEvent
 *****************************************************************************/

ValueChangedEvent::ValueChangedEvent () : ValueChangedEvent ((void*) nullptr, 0.0) {}
ValueChangedEvent::ValueChangedEvent (void* widget, double val) : Event (widget, VALUE_CHANGED_EVENT), value (val) {}
ValueChangedEvent::~ValueChangedEvent () {}
void ValueChangedEvent::setValue (double val) {value = val;}
double ValueChangedEvent::getValue () {return value;}

/*
 * End of class BEvents::ValueChangedEvent
 *****************************************************************************/

}
