#include <cairo/cairo.h>
#include "cairoplus.h"
#include "pugl/pugl.h"
#include <stdint.h>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <functional>

#include "BColors.hpp"
#include "BStyles.hpp"
#include "BEvents.hpp"

#define LIMIT(val, min, max) (val < min ? min : (val < max ? val : max))
#define PI 3.14159265

namespace BWidgets
{
/*****************************************************************************
 * Class BWidgets::Widget
 *****************************************************************************/
class Window; // Forward declaration

class Widget
{
public:
	Widget ();
	Widget (double x, double y, double width, double height);
	Widget (double x, double y, double width, double height, std::string name);
	virtual ~Widget ();
	void show ();
	void hide ();
	void add (Widget& child);
	void release (Widget* child);
	void moveTo (double x, double y);
	void setWidth (double width);
	void setHeight (double height);
	void setBorder (BStyles::Border border);
	void setBackground (BStyles::Fill background);
	std::string getName ();
	void setCallbackFunction (BEvents::EventType eventType, std::function<void (BEvents::Event*)> callbackFunction);

	bool isThisVisible ();
	bool isPointInWidget (double x, double y);
	Widget* getWidgetAt (double x, double y);
	double getOriginX ();
	double getOriginY ();
	virtual void applyTheme (BStyles::Theme theme);
	virtual void applyTheme (BStyles::Theme theme, std::string name);

	virtual void onConfigure ();
	virtual void onExpose (BEvents::ExposeEvent* event);
	virtual void onClose ();
	virtual void onButtonPressed (BEvents::PointerEvent* event);
	virtual void onButtonReleased (BEvents::PointerEvent* event);
	virtual void onPointerMotion (BEvents::PointerEvent* event);
	virtual void onPointerMotionWhileButtonPressed (BEvents::PointerEvent* event);
	virtual void onValueChanged (BEvents::Event* event);
	static void defaultCallback (BEvents::Event* event);


protected:
	void passProperties (Widget* child);
	void postRedisplay ();
	void postRedisplay (double x, double y, double width, double height);
	void redisplay ();
	void redisplay (double x, double y, double width, double height);
	virtual void draw ();
	virtual void draw (double x, double y, double width, double height);

	bool fitToArea (double& x, double& y, double& width, double& height);

	double x_, y_, width_, height_;
	bool isVisible_;
	Window* main_;
	Widget* parent_;
	std::vector <Widget*> children_;
	BStyles::Border border_;
	BStyles::Fill background_;
	std::string name_;
	std::array<std::function<void (BEvents::Event*)>, BEvents::EventType::NO_EVENT> cbfunction;
};

/*****************************************************************************
 * Class BWidgets::Window
 *****************************************************************************/
class Window : public Widget
{
public:
	Window ();
	Window (double width, double height, std::string title, PuglNativeWindow nativeWindow);
	~Window ();
	PuglView* getPuglView ();
	cairo_t* getPuglContext ();
	void run ();
	void addEventToQueue (BEvents::Event* event);
	void setInput (BEvents::InputDevice device, Widget* widget);
	Widget* getInput (BEvents::InputDevice device);
	void handleEvents ();

	virtual void onExpose (BEvents::ExposeEvent* event) override;
	virtual void onClose () override;

protected:
	static void translatePuglEvent (PuglView* view, const PuglEvent* event);
	void purgeEventQueue ();

	std::string title_;
	PuglView* view_;
	PuglNativeWindow nativeWindow_;
	bool quit_;
	struct {
		Widget* leftButton;
		Widget* rightButton;
	} input;

	std::vector<BEvents::Event*> eventQueue;
};

/*****************************************************************************
 * Class BWidgets::Label
 *****************************************************************************/
class Label : public Widget
{
public:
	Label ();
	Label (std::string text);
	Label (double x, double y, double width, double height, std::string text);
	~Label ();
	void setText (std::string text);
	std::string getText ();
	void setTextColors (BColors::ColorSet color);
	BColors::ColorSet getTextColors ();
	void setFont (BStyles::Font font);
	BStyles::Font getFont ();
	virtual void applyTheme (BStyles::Theme theme);
	virtual void applyTheme (BStyles::Theme theme, std::string name);


protected:
	virtual void draw () override;
	virtual void draw (double x, double y, double width, double height) override;

	BColors::ColorSet labelColors;
	BStyles::Font labelFont;
	std::string labelText;
};

/*****************************************************************************/

/*****************************************************************************
 * Class BWidgets::ValueWidget
 *****************************************************************************/
class ValueWidget : public Widget
{
public:
	ValueWidget ();
	ValueWidget (double  x, double y, double width, double height, std::string name, double value);
	~ValueWidget ();
	virtual void setValue (double val);
	double getValue ();
	virtual void onValueChanged (BEvents::Event* event) override;

protected:
	void postValueChanged ();
	double value;
};
/*****************************************************************************/

/*****************************************************************************
 * Class BWidgets::RangeWidget
 *****************************************************************************/
class RangeWidget : public ValueWidget
{
public:
	RangeWidget ();
	RangeWidget (double  x, double y, double width, double height, std::string name, double value, double min, double max, double step);
	~RangeWidget ();
	virtual void setValue (double val) override;
	void setMin (double min);
	double getMin ();
	void setMax (double max);
	double getMax ();
	void setStep (double step);
	double getStep ();

protected:
	double rangeMin;
	double rangeMax;
	double rangeStep;

};
/*****************************************************************************/

/*****************************************************************************
 * Class BWidgets::Slider
 *****************************************************************************/
class Slider : public RangeWidget
{
public:
	Slider ();
	Slider (double  x, double y, double width, double height, std::string name, double value, double min, double max, double step);
	~Slider ();
	virtual void applyTheme (BStyles::Theme theme);
	virtual void applyTheme (BStyles::Theme theme, std::string name);

	virtual void onButtonPressed (BEvents::PointerEvent* event) override;
	virtual void onPointerMotionWhileButtonPressed (BEvents::PointerEvent* event) override;

protected:
	virtual void draw () override;
	virtual void draw (double x, double y, double width, double height) override;

	BColors::ColorSet fgColors;
	BColors::ColorSet bgColors;
};

/*****************************************************************************/


/*****************************************************************************
 * Class BWidgets::Dial
 *****************************************************************************/
class Dial : public RangeWidget
{
public:
	Dial ();
	Dial (double x, double y, double width, double height, std::string name, double value, double min, double max, double step);
	~Dial ();
	virtual void applyTheme (BStyles::Theme theme);
	virtual void applyTheme (BStyles::Theme theme, std::string name);

	virtual void onButtonPressed (BEvents::PointerEvent* event) override;
	virtual void onPointerMotionWhileButtonPressed (BEvents::PointerEvent* event) override;


protected:
	virtual void draw () override;
	virtual void draw (double x, double y, double width, double height) override;

	BColors::ColorSet fgColors;
	BColors::ColorSet bgColors;
};

/*****************************************************************************/


Widget::Widget () : Widget (0.0, 0.0, 200.0, 200.0, "Widget") {}

Widget::Widget (double x, double y, double width, double height) : Widget (x, y, width, height, "Widget") {}

Widget::Widget(double x, double y, double width, double height, std::string name) :
		x_ (x), y_ (y), width_ (width), height_ (height), isVisible_ (true),
		main_ (nullptr), parent_ (nullptr), children_ (), border_ (BStyles::noBorder), background_ (BStyles::blackFill), name_ (name)
{
	cbfunction.fill (Widget::defaultCallback);
}

Widget::~Widget() {}

void Widget::show ()
{
	isVisible_ = true;
	if ((parent_) && parent_->isThisVisible ()) postRedisplay ();
}

void Widget::hide ()
{
	isVisible_ = false;
	if ((parent_) && parent_->isThisVisible ()) postRedisplay ();
}

void Widget::add (Widget& child)
{
	child.main_ = main_;
	child.parent_ = this;
	passProperties (&child);
	children_.push_back (&child);

	if (isThisVisible ()) postRedisplay ();
}

void Widget::release (Widget* child)
{
	if (child)
	{
		// Delete child's connection to this widget
		child->parent_ = nullptr;

		if (child->main_)
		{
			// Release child from main window input connections
			if (child->main_-> getInput (BEvents::LEFT_BUTTON) == child) child->main_-> setInput (BEvents::LEFT_BUTTON, nullptr);
			if (child->main_-> getInput (BEvents::RIGHT_BUTTON) == child) child->main_-> setInput (BEvents::RIGHT_BUTTON, nullptr);

			// Remove connection to main window
			child->main_ = nullptr;
		}

		// Delete connection to released child
		for (std::vector<Widget*>::iterator it = children_.begin (); it !=children_.end (); ++it)
		{
			if ((Widget*) *it == child)
			{
				children_.erase (it);

				// Remove it from display
				if (isThisVisible ()) postRedisplay ();

				return;
			}
		}

		std::cerr << "Msg from BWidgets::Widget::release(): Child " << child->name_ << " doesn't exist." << std::endl;
	}
}

void Widget::moveTo (double x, double y)
{
	if ((x_ != x) || (y_ != y))
	{
		if (isThisVisible ())
		{
			bool vis = isVisible_;
			isVisible_ = false;
			postRedisplay ();
			x_ = x;
			y_ = y;
			isVisible_ = vis;
			postRedisplay ();
		}
		else
		{
			x_ = x;
			y_ = y;
		}
	}
}

void Widget::setWidth (double width)
{
	if (width_ != width)
	{
		if (isThisVisible ())
		{
			bool vis = isVisible_;
			isVisible_ = false;
			postRedisplay ();
			width_ =width;
			isVisible_ = vis;
			postRedisplay ();
		}
		else
		{
			width_ =  width;
		}
	}
}
void Widget::setHeight (double height)
{
	if (height_ != height)
	{
		if (isThisVisible ())
		{
			bool vis = isVisible_;
			isVisible_ = false;
			postRedisplay ();
			height_ = height;
			isVisible_ = vis;
			postRedisplay ();
		}
		else
		{
			height_ = height;
		}
	}
}

void Widget::setBorder (BStyles::Border border)
{
	border_ = border;
	if (isThisVisible ()) postRedisplay ();
}

void Widget::setBackground (BStyles::Fill background)
{
	background_ = background;
	if (isThisVisible ()) postRedisplay ();
}

std::string Widget::getName () {return name_;}

void Widget::setCallbackFunction (BEvents::EventType eventType, std::function<void (BEvents::Event*)> callbackFunction)
{
	if (eventType <= BEvents::EventType::NO_EVENT) cbfunction[eventType] = callbackFunction;
}

bool Widget::isThisVisible()
{
	for (Widget* w = this; w; w = w->parent_)
	{
		if (!w->isVisible_) return false;
	}
	return true;
}

bool Widget::isPointInWidget (double x, double y) {return ((x >= 0.0) && (x <= width_) && (y >= 0.0) && (y <= height_));}

Widget* Widget::getWidgetAt (double x, double y)
{
	if (main_ && isVisible_ && isPointInWidget (x, y))
	{
		Widget* finalw = this;
		for (Widget* w : children_)
		{
			double xNew = x - w->x_;
			double yNew = y - w->y_;
			Widget* nextw = w->getWidgetAt (xNew, yNew);
			if (nextw)
			{
				finalw = nextw;
			}
		}
		return finalw;
	}

	else return nullptr;
}

double Widget::getOriginX ()
{
	double x = 0.0;
	for (Widget* w = this; w->parent_; w = w->parent_) x += w->x_;
	return x;
}

double Widget::getOriginY ()
{
	double y = 0.0;
	for (Widget* w = this; w->parent_; w = w->parent_) y += w->y_;
	return y;
}

void Widget::applyTheme (BStyles::Theme theme) {applyTheme (theme, name_);}

void Widget::applyTheme (BStyles::Theme theme, std::string name)
{
	// Border
	void* borderPtr = theme.getStyle(name, "border");
	if (borderPtr) border_ = *((BStyles::Border*) borderPtr);

	// Background
	void* backgroundPtr = theme.getStyle(name, "background");
	if (backgroundPtr) background_ = *((BStyles::Fill*) backgroundPtr);

	if ((borderPtr || backgroundPtr) && isThisVisible ()) postRedisplay ();
}

void Widget::onConfigure () {} // Empty, only Windows handle configure events
void Widget::onExpose (BEvents::ExposeEvent* event) {} // Empty, only Windows handle expose events
void Widget::onClose () {} // Empty, only Windows handle close events
void Widget::onButtonPressed (BEvents::PointerEvent* event) {}
void Widget::onButtonReleased (BEvents::PointerEvent* event) {}
void Widget::onPointerMotion (BEvents::PointerEvent* event) {}
void Widget::onPointerMotionWhileButtonPressed (BEvents::PointerEvent* event) {}
void Widget::onValueChanged (BEvents::Event* event) {}

void Widget::defaultCallback (BEvents::Event* event)
{
	if ((event) && (event->getWidget ()))
	{
		std::cerr << "Msg from BWidgets::Widget::defaultCallback (): defaultCallback called from " << ((Widget*) event->getWidget ())->getName () <<std::endl;
	}
}

void Widget::passProperties (Widget* child)
{
	for (Widget* w : child->children_)
	{
		w->main_ = main_;
		passProperties (w);
	}
}

void Widget::postRedisplay () {postRedisplay (0, 0, width_, height_);}

void Widget::postRedisplay (double x, double y, double width, double height)
{
	if (main_)
	{
		BEvents::ExposeEvent* event = new BEvents::ExposeEvent (this, x, y, width, height);
		main_->addEventToQueue (event);
	}
}

void Widget::redisplay () {redisplay (0.0, 0.0, width_, height_);}

void Widget::redisplay (double x, double y, double width, double height)
{
	if (main_ && isVisible_ && fitToArea (x, y, width, height))
	{
		draw (x, y, width, height);
		for (Widget* w : children_)
		{
			double xNew = x - w->x_;
			double yNew = y - w->y_;
			w->redisplay (xNew, yNew, width, height);
		}
	}
}

void Widget::draw ()
{
	draw (0.0, 0.0, width_, height_);
}

void Widget::draw (double x, double y, double width, double height)
{
	// cairo
	if (isVisible_ && main_)
	{
		double x0 = getOriginX ();
		double y0 = getOriginY ();
		cairo_t* cr = main_->getPuglContext ();
		if (cr)
		{
			cairo_save (cr);

			// Limit cairo-drawing area
			cairo_rectangle (cr, x + x0, y + y0, width, height);
			cairo_clip (cr);

			double radius = border_.getRadius ();

			// Draw background
			double innerBorders = border_.getMargin () + border_.getLine().getWidth() + border_.getPadding ();
			double innerRadius = (radius > border_.getPadding () ? radius - border_.getPadding () : 0);
			cairo_surface_t* fillSurface = background_.getCairoSurface ();
			BColors::Color bc = *background_.getColor();


			if ((width_ >= 2 * innerBorders) && (height_ >= 2 * innerBorders))
			{
				// Background_image ?
				if (cairo_surface_status (fillSurface) == CAIRO_STATUS_SUCCESS)
				{
					cairo_set_source_surface (cr, fillSurface, 0, 0);

					// If drawing area < background are, draw only a rectangle for the drawing area (faster)
					if ((x >= innerBorders) && (x + width <= width_ - 2 * innerBorders) &&
						(y >= innerBorders) && (y + height <= height_ - 2 * innerBorders))
					{
						cairo_rectangle (cr, x + x0, y + y0, width, height);
					}
					else
					{
						cairo_rectangle_rounded (cr, x0 + innerBorders, y0 + innerBorders,
												 width_ - 2 * innerBorders, height_ - 2 * innerBorders, innerRadius);
					}
					cairo_fill (cr);

					cairo_surface_destroy (fillSurface);
				}

				// Plain Background color ?
				else if (bc.getAlpha() != 0.0)
				{
					cairo_set_source_rgba (cr, bc.getRed(), bc.getGreen(), bc.getBlue(), bc.getAlpha());

					// If drawing area < background are, draw only a rectangle for the drawing area (faster)
					if ((x >= innerBorders) && (x + width <= width_ - 2 * innerBorders) &&
						(y >= innerBorders) && (y + height <= height_ - 2 * innerBorders))
					{
						cairo_rectangle (cr, x + x0, y + y0, width, height);
					}
					else
					{
						cairo_rectangle_rounded (cr, x0 + innerBorders, y0 + innerBorders,
												 width_ - 2 * innerBorders, height_ - 2 * innerBorders, innerRadius);
					}
					cairo_fill (cr);
				}

			}

			// Draw border frame
			double outerBorders = border_.getMargin ();
			if ((border_.getLine().getColor().getAlpha() != 0.0) &&
				(border_.getLine().getWidth() != 0.0) &&
				(width_ >= 2 * outerBorders) &&
				(height_ >= 2 * outerBorders))
			{
				cairo_rectangle_rounded (cr, x0 + outerBorders, y0 + outerBorders,
										 width_ - 2 * outerBorders, height_ - 2 * outerBorders, radius);

				cairo_set_source_rgba (cr, border_.getLine().getColor().getRed(),
										   border_.getLine().getColor().getGreen(),
										   border_.getLine().getColor().getBlue(),
										   border_.getLine().getColor().getAlpha());
				cairo_set_line_width (cr, border_.getLine().getWidth());
				cairo_stroke (cr);
			}

			cairo_restore (cr);
		}
	}

	{
		if (background_.getColor().getAlpha() != 0.0)
		{

		}
	}

}

bool Widget::fitToArea (double& x, double& y, double& width, double& height)
{
	bool isInArea = true;
	if (x < 0.0)
	{
		if (x + width < 0.0)
		{
			x = 0.0;
			width = 0.0;
			isInArea = false;
		}
		else
		{
			width = x + width;
			x = 0.0;

		}
	}
	if (x + width > width_)
	{
		if (x > width_)
		{
			x = width_;
			width = 0.0;
			isInArea = false;
		}
		else
		{
			width = width_ - x;
		}
	}
	if (y < 0.0)
	{
		if (y + height < 0.0)
		{
			y = 0.0;
			height = 0.0;
			isInArea = false;
		}
		else
		{
			height = y + height;
			y = 0.0;

		}
	}
	if (y + height > height_)
	{
		if (y > height_)
		{
			y = height_;
			height = 0.0;
			isInArea = false;
		}
		else
		{
			height = height_ - x;
		}
	}

	return isInArea;
}

/*****************************************************************************/

Window::Window () : Window (200.0, 200.0, "Main Window", 0.0) {}

Window::Window (double width, double height, std::string title, PuglNativeWindow nativeWindow) :
		Widget (0.0, 0.0, width, height, title), title_ (title), view_ (NULL), nativeWindow_ (nativeWindow), quit_ (false),
		input ({nullptr, nullptr})
{
	main_ = this;
	view_ = puglInit(NULL, NULL);

	if (nativeWindow_ != 0)
	{
		puglInitWindowParent(view_, nativeWindow_);
	}

	puglInitWindowSize (view_, width_, height_);
	puglInitResizable (view_, true);
	puglInitContextType (view_, PUGL_CAIRO);
	puglIgnoreKeyRepeat (view_, true);
	puglCreateWindow (view_, title.c_str ());
	puglShowWindow (view_);
	puglSetHandle (view_, this);

	puglSetEventFunc (view_, Window::translatePuglEvent);
}

Window::~Window ()
{
	purgeEventQueue ();
	puglDestroy(view_);
}

PuglView* Window::getPuglView () {return view_;}

cairo_t* Window::getPuglContext ()
{
	if (view_) return (cairo_t*) puglGetContext (view_);
	else return NULL;
}

void Window::run ()
{
	while (!quit_)
	{
		puglWaitForEvent (view_);
		puglProcessEvents (view_);
		handleEvents ();
	}
}

void Window::onClose ()
{
	quit_ = true;
}

void Window::onExpose (BEvents::ExposeEvent* event)
{
	if (event)
	{
		Widget* widget = (Widget*) event->getWidget ();
		redisplay (widget->getOriginX () + event->getX (), widget->getOriginY () + event->getY (),
				   event->getWidth (), event->getHeight ());
	}
}

void Window::addEventToQueue (BEvents::Event* event)
{
	eventQueue.push_back (event);
}

void Window::setInput (BEvents::InputDevice device, Widget* widget)
{
	switch (device) {
	case BEvents::LEFT_BUTTON:
		input.leftButton = widget;
		break;
	case BEvents::RIGHT_BUTTON:
		input.rightButton = widget;
		break;
	default:
		break;
	}
}

Widget* Window::getInput (BEvents::InputDevice device)
{
	switch (device) {
	case BEvents::LEFT_BUTTON: return input.leftButton;
	case BEvents::RIGHT_BUTTON: return input.rightButton;
	default: return nullptr;
	}
}

void Window::handleEvents ()
{
	while (eventQueue.size () > 0)
	{
		BEvents::Event* event = eventQueue.front ();
		if (event)
		{
			Widget* widget = (Widget*) event->getWidget ();
			if (widget)
			{
				BEvents::EventType eventType = event->getEventType ();

				switch (eventType)
				{
				case BEvents::EXPOSE_EVENT:
					onExpose ((BEvents::ExposeEvent*) event);
					break;

				case BEvents::CLOSE_EVENT:
					onClose ();
					break;

				case BEvents::BUTTON_PRESS_EVENT:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						setInput (be->getButton (), widget);
						widget->onButtonPressed (be);
					}
					break;

				case BEvents::BUTTON_RELEASE_EVENT:
					{
						BEvents::PointerEvent* be = (BEvents::PointerEvent*) event;
						setInput (be->getButton (), nullptr);
						widget->onButtonReleased (be);
					}
					break;

				case BEvents::POINTER_MOTION_EVENT:
					widget->onPointerMotion((BEvents::PointerEvent*) event);
					break;

				case BEvents::POINTER_MOTION_WHILE_BUTTON_PRESSED_EVENT:
					widget->onPointerMotionWhileButtonPressed((BEvents::PointerEvent*) event);
					break;

				case BEvents::VALUE_CHANGED_EVENT:
					widget->onValueChanged((BEvents::ValueChangedEvent*) event);
					break;

				default:
					break;
				}

			}
			delete event;
		}
		eventQueue.erase (eventQueue.begin ());
	}
}

void Window::translatePuglEvent (PuglView* view, const PuglEvent* event)
{
	Window* w = (Window*) puglGetHandle (view);
	switch (event->type) {
	case PUGL_BUTTON_PRESS:
		{
			Widget* widget = w->getWidgetAt (event->button.x, event->button.y);
			if (widget)
			{
				w->addEventToQueue (new BEvents::PointerEvent (widget,
															  BEvents::BUTTON_PRESS_EVENT,
															  event->button.x - widget->getOriginX (),
															  event->button.y - widget->getOriginY (),
															  (BEvents::InputDevice) event->button.button));
			}
		}
		break;

	case PUGL_BUTTON_RELEASE:
		{
			Widget* widget = w->getInput ((BEvents::InputDevice) event->button.button);
			if (widget)
			{
				w->addEventToQueue (new BEvents::PointerEvent (widget,
															  BEvents::BUTTON_RELEASE_EVENT,
															  event->button.x - widget->getOriginX (),
															  event->button.y - widget->getOriginY (),
															  (BEvents::InputDevice) event->button.button));
			}
		}
		break;

	case PUGL_MOTION_NOTIFY:
		{
			BEvents::EventType eventType = BEvents::POINTER_MOTION_EVENT;
			BEvents::InputDevice device = BEvents::NO_BUTTON;
			if (w->input.leftButton)
			{
				device = BEvents::LEFT_BUTTON;
				eventType = BEvents::POINTER_MOTION_WHILE_BUTTON_PRESSED_EVENT;
			}
			if (w->input.rightButton)
			{
				device = BEvents::RIGHT_BUTTON;
				eventType = BEvents::POINTER_MOTION_WHILE_BUTTON_PRESSED_EVENT;
			}

			Widget* widget = (device != BEvents::NO_BUTTON ? w->getInput (device) : w->getWidgetAt (event->motion.x, event->motion.y));

			if (widget)
			{

				w->addEventToQueue (new BEvents::PointerEvent (widget,
															  eventType,
															  event->motion.x - widget->getOriginX (),
															  event->motion.y - widget->getOriginY (),
															  device));
			}
		}
		break;

	case PUGL_EXPOSE:
		w->postRedisplay ();
		break;
	case PUGL_CLOSE:
		w->addEventToQueue (new BEvents::Event (w, BEvents::CLOSE_EVENT));
		break;
	default: break;
	}

}

void Window::purgeEventQueue ()
{
	while (eventQueue.size () > 0)
	{
		BEvents::Event* event = eventQueue.front ();
		if (event) delete event;
		eventQueue.erase (eventQueue.begin ());
	}
}


/*****************************************************************************/

Label::Label () : Label (0.0, 0.0, 0.0, 0.0, "Label") {}
Label::Label (std::string text) : Label (0.0, 0.0, 200.0, 20.0, text) {}
Label::Label (double x, double y, double width, double height, std::string text) :
		Widget (x, y, width, height, text), labelColors (BColors::whites), labelFont (BStyles::sans12pt), labelText (text) {}
Label::~Label () {}

void Label::setText (std::string text) {labelText = text;}
std::string Label::getText () {return labelText;}
void Label::setTextColors (BColors::ColorSet colorset) {labelColors = colorset;}
BColors::ColorSet Label::getTextColors () {return labelColors;}
void Label::setFont (BStyles::Font font) {labelFont = font;}
BStyles::Font Label::getFont () {return labelFont;}

void Label::applyTheme (BStyles::Theme theme) {applyTheme (theme, name_);}

void Label::applyTheme (BStyles::Theme theme, std::string name)
{
	Widget::applyTheme (theme, name);

	// Color
	void* colorsPtr = theme.getStyle(name, "colors");
	if (colorsPtr) labelColors = *((BColors::ColorSet*) colorsPtr);

	// Font
	void* fontPtr = theme.getStyle(name, "font");
	if (fontPtr) labelFont = *((BStyles::Font*) fontPtr);

	if ((colorsPtr || fontPtr) && isThisVisible ()) postRedisplay ();
}

void Label::draw (){draw (0.0, 0.0, width_, height_);}

void Label::draw (double x, double y, double width, double height)
{
	Widget::draw (x, y, width, height);

	// cairo
	if (isVisible_ && main_)
	{
		double x0 = getOriginX ();
		double y0 = getOriginY ();
		cairo_t* cr = main_->getPuglContext ();
		if (cr)
		{
			cairo_save (cr);

			// Limit cairo-drawing area
			cairo_rectangle (cr, x + x0, y + y0, width, height);
			cairo_clip (cr);

			cairo_text_extents_t ext = labelFont.getTextExtents(cr, labelText);

			cairo_set_source_rgba (cr, labelColors.getColor (BColors::NORMAL).getRed (),
									   labelColors.getColor (BColors::NORMAL).getGreen (),
									   labelColors.getColor (BColors::NORMAL).getBlue (),
									   labelColors.getColor (BColors::NORMAL).getAlpha ());
			cairo_select_font_face (cr, labelFont.getFontFamily ().c_str (), labelFont.getFontSlant (), labelFont.getFontWeight ());
			cairo_set_font_size (cr, labelFont.getFontSize ());
			cairo_move_to (cr, x0 + width_ / 2 - ext.width / 2 - ext.x_bearing, y0 + height_ / 2 - ext.height / 2 - ext.y_bearing);
			cairo_show_text (cr, labelText.c_str ());

			cairo_restore (cr);
		}
	}
}

/*****************************************************************************/

ValueWidget::ValueWidget () : ValueWidget (0, 0, 200, 200, "ValueWidget", 0.0) {}

ValueWidget::ValueWidget (double  x, double y, double width, double height, std::string name, double value) :
		Widget (x, y, width, height, name), value (value) {}

ValueWidget::~ValueWidget () {}

void ValueWidget::setValue (double val)
{
	if (val != value)
	{
		value = val;
		postValueChanged ();
		if (isThisVisible ()) postRedisplay ();
	}
}

double ValueWidget::getValue () {return value;}

void ValueWidget::onValueChanged (BEvents::Event* event)
{
	cbfunction[BEvents::EventType::VALUE_CHANGED_EVENT] (event);
}

void ValueWidget::postValueChanged ()
{
	if (main_)
	{
		BEvents::ValueChangedEvent* event = new BEvents::ValueChangedEvent (this, value);
		main_->addEventToQueue (event);
	}
}

/*****************************************************************************/
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
		else if (isThisVisible ()) postRedisplay ();
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
		else if (isThisVisible ()) postRedisplay ();
	}
}

double RangeWidget::getMax () {return rangeMax;}

void RangeWidget::setStep (double step) {rangeStep = step;}

double RangeWidget::getStep () {return rangeStep;}


/*****************************************************************************/

Slider::Slider () : Slider (0, 0, 12, 100, "Slider", 0.0, 0.0, 100.0, 0.0) {}

Slider::Slider (double  x, double y, double width, double height, std::string name, double value, double min, double max, double step) :
		RangeWidget (x, y, width, height, name, value, min, max, step), fgColors (BColors::greens), bgColors (BColors::greys) {}

Slider::~Slider () {}

void Slider::applyTheme (BStyles::Theme theme) {applyTheme (theme, name_);}

void Slider::applyTheme (BStyles::Theme theme, std::string name)
{
	Widget::applyTheme (theme, name);

	// Color
	void* fgPtr = theme.getStyle(name, "fgColors");
	if (fgPtr) fgColors = *((BColors::ColorSet*) fgPtr);

	// Font
	void* bgPtr = theme.getStyle(name, "bgColors");
	if (bgPtr) bgColors = *((BColors::ColorSet*) bgPtr);

	if ((fgPtr || bgPtr) && isThisVisible ()) postRedisplay ();
}

void Slider::onButtonPressed (BEvents::PointerEvent* event)
{
	// Perform only if minimum requirements are satisfied
	if (main_ && isThisVisible () && (height_ >= 4) && (width_ >= 4) && (event->getButton() == BEvents::LEFT_BUTTON))
	{
		// Get pointer coords
		double y = event->getY ();
		double x = event->getX ();
		if (width_ > height_) std::swap (x, y); // Swap x <-> y if horizontal

		// Calculate aspect ratios and orientation first
		double w0 = (height_ >= width_ ? width_ : height_);
		double h0 = (height_ >= width_ ? height_ : width_);
		double w = (w0 > 24.0 ? 12.0 : 0.5 * w0);
		double h = (h0 / w0 >= 2 ? h0 - 2 * w : h0 - (h0 / w0) * w);

		// Pointer within the scale area ? Set value!
		if ((y >= h0/2 - h/2) && (y <= h0/2 + h/2 -1) && (x >= 0) && (x <= w0 - 1))
		{
			double frac = (y - h0/2 + h/2) / h;
			if (getStep () >= 0) frac = 1 - frac;
			if (width_ > height_) frac = 1 - frac;

			double min = getMin ();
			double max = getMax ();
			setValue (min + frac * (max - min));
		}
	}
}

void Slider::onPointerMotionWhileButtonPressed (BEvents::PointerEvent* event) {onButtonPressed (event);}

void Slider::draw () {draw (0, 0, width_, height_);}

void Slider::draw (double x, double y, double width, double height)
{
	// Draw super class widget elements first
	Widget::draw (x, y, width, height);

	// Draw slider
	// only if minimum requirements satisfied
	if (isThisVisible () && main_ && (height_ >= 4) && (width_ >= 4))
	{
		double x0 = getOriginX ();
		double y0 = getOriginY ();
		cairo_t* cr = main_->getPuglContext ();
		if (cr)
		{
			cairo_save (cr);

			cairo_pattern_t* pat;

			// Limit cairo-drawing area
			cairo_rectangle (cr, x + x0, y + y0, width, height);
			cairo_clip (cr);

			// Calculate aspect ratios and orientation first
			double w0 = (height_ >= width_ ? width_ : height_);
			double h0 = (height_ >= width_ ? height_ : width_);
			double w = (w0 > 24.0 ? 12.0 : 0.5 * w0);
			double h = (h0 / w0 >= 2 ? h0 - 2 * w : h0 - (h0 / w0) * w);

			// Relative Value (0 .. 1) for calculation of value line
			double relVal = (getValue () - getMin ()) / (getMax () - getMin ());
			if (getStep() < 0) relVal = 1 - relVal;		// Swap if reverse orientation
			if (width_ > height_) relVal = 1 - relVal;	// Swap (again) if horizontal

			double x1 = w0/2 - w / 2; double y1 = h0/2 - h/2;	// Top left
			double x2 = w0/2 + w / 2 - 1; double y2 = h0/2 - h/2 + (1 - relVal)*(h-2) + 1; // Value line right
			double x3 = w0/2 - w / 2; double y3 = h0/2 - h/2 + (1 - relVal)*(h-2) + 1;	// Value line left
			double x4 = w0/2 + w / 2 - 1; double y4 = h0/2 + h/2 -1; // Bottom right

			if (getStep () < 0) std::swap (y1, y4); // Swap top <-> bottom if reverse orientation

			// Swap top <-> bottom and x <-> y if horizontal
			if (width_ > height_)
			{
				std::swap (y1, y4);
				std::swap (x1, y1);
				std::swap (x2, y2);
				std::swap (x3, y3);
				std::swap (x4, y4);
			}

			// Colors uses within this method
			BColors::Color fgInact = fgColors.getColor (BColors::INACTIVE);
			BColors::Color fgActive = fgColors.getColor (BColors::ACTIVE);
			BColors::Color fgNormal = fgColors.getColor (BColors::NORMAL);
			BColors::Color bgNormal = bgColors.getColor (BColors::NORMAL);
			BColors::Color bgActive = bgColors.getColor (BColors::ACTIVE);
			BColors::Color bgInact = bgColors.getColor (BColors::INACTIVE);
			BColors::Color bgOff = bgColors.getColor (BColors::OFF);

			// Frame background
			cairo_rectangle (cr, x0 + x1, y0 + y1, x4 - x1 + 1, y4 - y1 + 1);
			cairo_set_line_width (cr, 0.5);
			cairo_set_source_rgba (cr, bgInact.getRed (), bgInact.getGreen (), bgInact.getBlue (), bgInact.getAlpha ());
			cairo_fill_preserve (cr);
			cairo_stroke (cr);

			// Scale background
			cairo_rectangle (cr, x0 + x1, y0 + y1, x4 - x1, y4 - y1);
			cairo_set_source_rgba (cr, fgInact.getRed (), fgInact.getGreen (), fgInact.getBlue (), fgInact.getAlpha ());
			cairo_fill_preserve (cr);
			cairo_set_source_rgba (cr, bgOff.getRed (), bgOff.getGreen (), bgOff.getBlue (), bgOff.getAlpha ());
			cairo_stroke (cr);

			// Scale active
			pat = cairo_pattern_create_linear (x0 + x3, y0 + y3, x0 + x2, y0 + y2);
			cairo_pattern_add_color_stop_rgba (pat, 0.0, fgNormal.getRed (), fgNormal.getGreen (), fgNormal.getBlue (), fgNormal.getAlpha ());
			cairo_pattern_add_color_stop_rgba (pat, 0.25, fgActive.getRed (), fgActive.getGreen (), fgActive.getBlue (), fgActive.getAlpha ());
			cairo_pattern_add_color_stop_rgba (pat, 1, fgNormal.getRed (), fgNormal.getGreen (), fgNormal.getBlue (), fgNormal.getAlpha ());
			cairo_rectangle (cr, x0 + x3, y0 + y3, x4 - x3, y4 - y3);
			cairo_set_source (cr, pat);
			cairo_fill_preserve (cr);
			cairo_stroke (cr);
			cairo_pattern_destroy (pat);

			//Shadow
			cairo_move_to (cr, x0 + (x1 < x4 ? x1 : x4), y0 + (y4 > y1 ? y4 : y1));
			cairo_line_to (cr, x0 + (x1 < x4 ? x1 : x4), y0 + (y1 < y4 ? y1 : y4));
			cairo_line_to (cr, x0 + (x4 > x1 ? x4 : x1), y0 + (y1 < y4 ? y1 : y4));
			cairo_set_source_rgba (cr, 1.0, 1.0, 1.0, 1.0);
			cairo_set_line_width (cr, 1.0);
			cairo_set_source_rgba (cr, bgOff.getRed (), bgOff.getGreen (), bgOff.getBlue (), 0.5 * bgOff.getAlpha ());
			cairo_stroke (cr);


			// Knob
			pat = cairo_pattern_create_radial (x0 + (x2 + x3) / 2 - w / 4, y0 + (y2 + y3) / 2 - w / 4, 0.1 * w,
											   x0 + (x2 + x3) / 2, y0 + (y2 + y3) / 2, 1.5 * w);
			cairo_arc (cr, x0 + (x2 + x3) / 2, y0 + (y2 + y3) / 2, w - 1, 0, 2 * PI);
			cairo_pattern_add_color_stop_rgba (pat, 0, bgActive.getRed (), bgActive.getGreen (), bgActive.getBlue (), bgActive.getAlpha ());
			cairo_pattern_add_color_stop_rgba (pat, 1, bgNormal.getRed (), bgNormal.getGreen (), bgNormal.getBlue (), bgNormal.getAlpha ());
			cairo_set_source (cr, pat);
			cairo_fill_preserve (cr);
			cairo_pattern_destroy (pat);

			pat = cairo_pattern_create_radial (x0 + (x2 + x3) / 2 - w / 4, y0 + (y2 + y3) / 2 - w / 4, 0.1 * w,
											   x0 + (x2 + x3) / 2, y0 + (y2 + y3) / 2, 1.2 * w);
			cairo_pattern_add_color_stop_rgba (pat, 0, bgInact.getRed (), bgInact.getGreen (), bgInact.getBlue (), bgInact.getAlpha ());
			cairo_pattern_add_color_stop_rgba (pat, 1, bgOff.getRed (), bgOff.getGreen (), bgOff.getBlue (), bgOff.getAlpha ());
			cairo_set_line_width (cr, 0.5);
			cairo_set_source (cr, pat);
			cairo_stroke (cr);
			cairo_pattern_destroy (pat);

			cairo_restore (cr);
		}
	}
}

/*****************************************************************************/


Dial::Dial () : Dial (0.0, 0.0, 50.0, 50.0, "dial", 0.0, 0.0, 100.0, 1.0) {}

Dial::Dial (double x, double y, double width, double height, std::string name, double value, double min, double max, double step) :
		RangeWidget (x, y, width, height, name, value, min, max, step), fgColors (BColors::greens), bgColors (BColors::greys) {}

Dial:: ~Dial () {}

void Dial::applyTheme (BStyles::Theme theme) {applyTheme (theme, name_);}

void Dial::applyTheme (BStyles::Theme theme, std::string name)
{
	Widget::applyTheme (theme, name);

	// Color
	void* fgPtr = theme.getStyle(name, "fgColors");
	if (fgPtr) fgColors = *((BColors::ColorSet*) fgPtr);

	// Font
	void* bgPtr = theme.getStyle(name, "bgColors");
	if (bgPtr) bgColors = *((BColors::ColorSet*) bgPtr);

	if ((fgPtr || bgPtr) && isThisVisible ()) postRedisplay ();
}

void Dial::onButtonPressed (BEvents::PointerEvent* event)
{
	// Perform only if minimum requirements are satisfied
	if (main_ && isThisVisible () && (event->getButton () == BEvents::LEFT_BUTTON))
	{
		double x = event->getX ();
		double y = event->getY ();
		double size = (height_ < width_ ? height_ : width_);
		double dist = (sqrt (pow (x - width_ / 2, 2) + pow (y - height_ / 2, 2)));

		if ((dist >= 0.1 * size) && (dist <= 0.7 * size))
		{
			double angle = atan2 (x - width_ / 2, height_ / 2 - y) + PI;
			if ((angle >= 0.2 * PI) && (angle <= 1.8 * PI))
			{
				double corrAngle = LIMIT (angle, 0.3 * PI, 1.7 * PI);
				if (angle < 0.3 * PI) corrAngle = 0.3 * PI;
				if (angle > 1.7 * PI) corrAngle = 1.7 * PI;
				double frac = (corrAngle - 0.3 * PI) / (1.4 * PI);
				if (getStep () < 0) frac = 1 - frac;
				setValue (getMin () + frac * (getMax () - getMin ()));

			}
		}
	}
}

void Dial::onPointerMotionWhileButtonPressed (BEvents::PointerEvent* event) {onButtonPressed (event);}

void Dial::draw ()
{
	draw (0.0, 0.0, width_, height_);
}

void Dial::draw (double x, double y, double width, double height)
{
	// Draw super class widget elements first
	Widget::draw (x, y, width, height);

	// Draw dial
	// only if minimum requirements satisfied
	if (isThisVisible () && main_ && (height_ >= 12) && (width_ >= 12))
	{
		double x0 = getOriginX ();
		double y0 = getOriginY ();
		double size = (height_ < width_ ? height_ : width_);

		cairo_t* cr = main_->getPuglContext ();
		if (cr)
		{
			cairo_save (cr);

			cairo_pattern_t* pat;

			// Limit cairo-drawing area
			cairo_rectangle (cr, x + x0, y + y0, width, height);
			cairo_clip (cr);

			// Relative Value (0 .. 1) for calculation of value line
			double relVal = (getValue () - getMin ()) / (getMax () - getMin ());
			if (getStep() < 0) relVal = 1 - relVal;		// Swap if reverse orientation

			// Colors uses within this method
			BColors::Color fgInact = fgColors.getColor (BColors::INACTIVE);
			BColors::Color fgActive = fgColors.getColor (BColors::ACTIVE);
			BColors::Color fgNormal = fgColors.getColor (BColors::NORMAL);
			BColors::Color bgNormal = bgColors.getColor (BColors::NORMAL);
			BColors::Color bgActive = bgColors.getColor (BColors::ACTIVE);
			BColors::Color bgInact = bgColors.getColor (BColors::INACTIVE);
			BColors::Color bgOff = bgColors.getColor (BColors::OFF);

			// Outer arc
			cairo_set_source_rgba (cr, fgInact.getRed (), fgInact.getGreen (), fgInact.getBlue (), fgInact.getAlpha ());
			cairo_set_line_width (cr, 0.5);
			cairo_arc (cr, x0 + 0.5 * width_, y0 + 0.5 * height_, 0.48 * size, PI * 0.8, PI * 2.2);
			cairo_arc_negative (cr, x0 + 0.5 * width_, y0 + 0.5 * height_,  0.35 * size, PI * 2.2, PI * 0.8);
			cairo_close_path (cr);
			cairo_fill_preserve (cr);
			cairo_set_source_rgba (cr, bgInact.getRed (), bgInact.getGreen (), bgInact.getBlue (), bgInact.getAlpha ());
			cairo_stroke (cr);

			// Filled part (= active) of outer arc
			pat = cairo_pattern_create_linear (x0 + 0.5 * width_ - 0.5 * size, y0 + 0.5 * height - 0.5 * size,
											   x0 + 0.5 * width_ + 0.5 * size, y0 + 0.5 * height + 0.5 * size);
			cairo_pattern_add_color_stop_rgba (pat, 0.0, fgNormal.getRed (), fgNormal.getGreen (), fgNormal.getBlue (), fgNormal.getAlpha ());
			cairo_pattern_add_color_stop_rgba (pat, 0.25, fgActive.getRed (), fgActive.getGreen (), fgActive.getBlue (), fgActive.getAlpha ());
			cairo_pattern_add_color_stop_rgba (pat, 1, fgNormal.getRed (), fgNormal.getGreen (), fgNormal.getBlue (), fgNormal.getAlpha ());
			if (getStep () >= 0)
			{
				cairo_arc (cr, x0 + 0.5 * width_, y0 + 0.5 * height_,  0.48 * size, PI * 0.8, PI * (0.8 + 1.4 * relVal));
				cairo_arc_negative (cr, x0 + 0.5 * width_, y0 + 0.5 * height_, 0.35 * size, PI * (0.8 + 1.4 * relVal), PI * 0.8);
			}
			else
			{
				cairo_arc (cr, x0 + 0.5 * width_, y0 + 0.5 * height_,  0.48 * size, PI * (0.8 + 1.4 * relVal), PI * 2.2);
				cairo_arc_negative (cr, x0 + 0.5 * width_, y0 + 0.5 * height_, 0.35 * size, PI * 2.2, PI * (0.8 + 1.4 * relVal));
			}
			cairo_close_path (cr);
			cairo_set_source (cr, pat);
			cairo_fill (cr);

			// Inner circle
			cairo_arc (cr, x0 + 0.5 * width_, y0 + 0.5 * height_, 0.3 * size, 0, 2 * PI);
			cairo_close_path (cr);


			pat = cairo_pattern_create_radial (x0 + 0.5 * width_ - 0.25 * size, y0 + 0.5 * height_ - 0.25 * size, 0.1 * size,
											   x0 + 0.5 * width_, y0 + 0.5 * height_, 1.5 * size);
			cairo_pattern_add_color_stop_rgba (pat, 0, bgActive.getRed (), bgActive.getGreen (), bgActive.getBlue (), bgActive.getAlpha ());
			cairo_pattern_add_color_stop_rgba (pat, 1, bgNormal.getRed (), bgNormal.getGreen (), bgNormal.getBlue (), bgNormal.getAlpha ());
			cairo_set_source (cr, pat);
			cairo_fill_preserve (cr);
			cairo_pattern_destroy (pat);

			pat = cairo_pattern_create_radial (x0 + 0.5 * width_ - 0.25 * size, y0 + 0.5 * height_ - 0.25 * size, 0.1 * size,
											   x0 + 0.5 * width_, y0 + 0.5 * height_, 1.5 * size);
			cairo_pattern_add_color_stop_rgba (pat, 0, bgInact.getRed (), bgInact.getGreen (), bgInact.getBlue (), bgInact.getAlpha ());
			cairo_pattern_add_color_stop_rgba (pat, 1, bgOff.getRed (), bgOff.getGreen (), bgOff.getBlue (), bgOff.getAlpha ());
			cairo_set_line_width (cr, 0.5);
			cairo_set_source (cr, pat);
			cairo_stroke (cr);
			cairo_pattern_destroy (pat);

			// Dot
			cairo_set_source_rgba (cr, fgActive.getRed (), fgActive.getGreen (), fgActive.getBlue (), fgActive.getAlpha ());
			cairo_arc (cr, x0 + 0.5 * width_ + 0.23 * size * cos (PI * (0.8 + 1.4 *relVal)),
					   y0 + 0.5 * height_ + 0.23 * size * sin (PI * (0.8 + 1.4 *relVal)),
					   0.05 * size, 0, PI * 2);
			cairo_close_path (cr);
			cairo_fill (cr);

			cairo_restore (cr);
		}
	}
}

} // namespace BWidgets



