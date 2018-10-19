#include "BWidgets/BWidgets.hpp"

static void showValue (BEvents::Event* event)
{
	if ((event) && (event->getWidget ()))
	{
		std::cout << ((BWidgets::ValueWidget*) event->getWidget ())->getValue () << std::endl;
	}
}

int main ()
{
	//Define Styles and Colors first
	BColors::ColorSet defaultFgColors = {{{0.0, 0.75, 0.2, 1.0}, {0.0, 1.0, 0.4, 1.0}, {0.0, 0.2, 0.0, 1.0}, {0.0, 0.0, 0.0, 0.0}}};
	BColors::ColorSet defaultToolColors = BColors::greys;
	BStyles::Fill bgPicture = BStyles::Fill ("example-romedalen.png");

	BStyles::StyleSet defaultStyles = {"Widget", {{"background", STYLEPTR (&BStyles::noFill)},
											 	  {"border", STYLEPTR (&BStyles::noBorder)}}};

	BStyles::Border frameBorder = {BStyles::whiteLine1pt, 3.0, 3.0, 10.0};

	BStyles::Font defaultFont = BStyles::Font ("Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0);

	// And a theme makes global definition of styles much easier
	BStyles::Theme defaultTheme = BStyles::Theme ({
		defaultStyles,
		{"Window", {{"background", STYLEPTR (&BStyles::blackFill)},
					{"border", STYLEPTR (&BStyles::noBorder)}}
		},
		{"Frame", {{"background", STYLEPTR (&BStyles::greyFill)},
				   {"border", STYLEPTR (&frameBorder)}}
		},
		{"Label", {{"uses", STYLEPTR (&defaultStyles)},
				   {"textcolors", STYLEPTR (&BColors::blues)},
				   {"font", STYLEPTR (&defaultFont)}}
		},
		{"Slider", {{"uses", STYLEPTR (&defaultStyles)},
					{"fgcolors", STYLEPTR (&defaultFgColors)},
					{"bgcolors", STYLEPTR (&defaultToolColors)}}
		},
		{"Dial", {{"uses", STYLEPTR (&defaultStyles)},
				  {"fgcolors", STYLEPTR (&defaultFgColors)},
				  {"bgcolors", STYLEPTR (&defaultToolColors)}}
		},
		{"DialVal", {{"uses", STYLEPTR (&defaultStyles)},
			   	     {"fgcolors", STYLEPTR (&defaultFgColors)},
					 {"bgcolors", STYLEPTR (&defaultToolColors)},
					 {"textcolors", STYLEPTR (&BColors::darks)},
					 {"font", STYLEPTR (&defaultFont)}}
		},
		{"Button", {{"uses", STYLEPTR (&defaultStyles)},
					{"buttoncolors", STYLEPTR (&BColors::darks)},
					{"textcolors", STYLEPTR (&defaultFgColors)},
					{"font", STYLEPTR (&defaultFont)}}
		}
	});

	// The starting point is the main window. All widgets will be added to this
	// window later.
	BWidgets::Window* MainWindow = new BWidgets::Window (640, 480, "Window", 0);

	// Definition of a few container widgets.
	BWidgets::Widget Widget2 = BWidgets::Widget (100, 100, 460, 260, "BackgroundWidget");
	Widget2.setBorder (BStyles::Border (BStyles::Line (BColors::blue, 3.0), 0.0, 0.0, 0.0));
	Widget2.setBackground (BStyles::Fill (BColors::grey));
	BWidgets::Widget Widget = BWidgets::Widget (20, 20, 460, 260, "Frame");
	Widget.applyTheme (defaultTheme);
	Widget.setBackground(bgPicture);
	Widget.setClickable (true);
	Widget.setDragable (true);

	// Label widgets
	BWidgets::Label Label1 = BWidgets::Label (100, 120, 340, 16, "This is a long text and it will be hidden partially!");
	Label1.applyTheme (defaultTheme, "Label");
	BWidgets::Label Label2 (Label1);
	Label2.applyTheme (defaultTheme, "Label");
	Label2.moveTo (100,140);
	BWidgets::Label Label2a = Label1;
	Label2a.applyTheme (defaultTheme, "Label");
	Label2a.moveTo (100,160);
	BWidgets::Label Label3 = BWidgets::Label (100, 180, 340, 16, "This is a long text and it will be shown fully!");
	Label3.applyTheme (defaultTheme, "Label");
	BWidgets::Label Label4 = BWidgets::Label (10, 10, 240, 16, "This is a too long text and it will be clipped!");
	Label4.applyTheme (defaultTheme, "Label");

	// Slider widgets
	BWidgets::VSlider Slider1 = BWidgets::VSlider (10, 10, 20, 240, "Slider", 80.0, 0.0, 100.0, 0.0);
	Slider1.applyTheme (defaultTheme);
	BWidgets::VSlider Slider2 = BWidgets::VSlider (40, 10, 20, 240, "Slider", 80.0, 0.0, 100.0, -10.0);
	Slider2.applyTheme (defaultTheme);
	BWidgets::HSlider Slider3 = BWidgets::HSlider (100, 10, 240, 20, "Slider", 80.0, 0.0, 100.0, 0.0);
	Slider3.applyTheme (defaultTheme);
	BWidgets::HSlider Slider4 = BWidgets::HSlider (100, 40, 240, 20, "Slider", 80.0, 0.0, 100.0, -0.01);
	Slider4.applyTheme (defaultTheme);
	BWidgets::HSliderWithValueDisplay Slider5 = BWidgets::HSliderWithValueDisplay (100, 70, 240, 20, "DialVal",
																				   80.0, 0.0, 100.0, 0.0, "%4.0f", BWidgets::ON_RIGHT);
	Slider5.applyTheme (defaultTheme);
	BWidgets::VSliderWithValueDisplay Slider6 = BWidgets::VSliderWithValueDisplay (70, 10, 20, 240, "DialVal",
																					   80.0, 0.0, 100.0, 1.0, "%4.0f", BWidgets::ON_TOP);
	Slider6.applyTheme (defaultTheme);

	// Dial widgets
	BWidgets::Dial Dial1 = BWidgets::Dial (100, 120, 80, 80, "Dial", 80.0, 0.0, 100.0, 0.0);
	Dial1.applyTheme (defaultTheme);
	BWidgets::Dial Dial2 = BWidgets::Dial (200, 120, 80, 80, "Dial", 80.0, 0.0, 100.0, -10.0);
	Dial2.applyTheme (defaultTheme);
	BWidgets::DialWithValueDisplay Dial3 = BWidgets::DialWithValueDisplay (300, 120, 80, 80, "DialVal", 80.0, 0.0, 100.0, 1.0, "%4.0f");
	Dial3.applyTheme (defaultTheme);

	// Button widgets
	BWidgets::Button Button1 = BWidgets::Button (100, 220, 60, 20, "Button", 0.0);
	Button1.applyTheme (defaultTheme);
	BWidgets::ToggleButton Button2 = BWidgets::ToggleButton (180, 220, 60, 20, "Button", 0.0);
	Button2.applyTheme (defaultTheme);
	BWidgets::TextButton Button3 = BWidgets::TextButton (260, 220, 60, 20, "Button", 0.0);
	Button3.applyTheme (defaultTheme);
	BWidgets::TextToggleButton Button4 = BWidgets::TextToggleButton (340, 220, 60, 20, "Button", 0.0);
	Button4.applyTheme (defaultTheme);

	// Drawing surface widgets for direct Cairo drawing
	BWidgets::DrawingSurface Surface = BWidgets::DrawingSurface (20, 340, 320, 60, "Frame");
	Surface.applyTheme (defaultTheme);
	Surface.getBorder ()->setRadius (0.0);
	Surface.getBackground ()->getColor ()->setAlpha (0.5);
	cairo_t* cr = cairo_create (Surface.getDrawingSurface ());
	cairo_set_line_width (cr, 3.0);
	cairo_set_source_rgba (cr, 1.0, 1.0, 0.0, 1.0);
	cairo_arc (cr, 30.0, 30.0, 20.0, 0, 6.28);
	cairo_close_path (cr);
	cairo_fill_preserve (cr);
	cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 1.0);
	cairo_stroke (cr);
	cairo_arc (cr, 30.0, 0.0, 40.0, 1.26, 1.88);
	cairo_stroke (cr);
	cairo_arc (cr, 20.0, 25.0, 3.0, 0.0, 6.28);
	cairo_close_path (cr);
	cairo_fill (cr);
	cairo_arc (cr, 40.0, 25.0, 3.0, 0.0, 6.28);
	cairo_close_path (cr);
	cairo_fill (cr);
	cairo_set_font_size (cr, 12.0);
	cairo_move_to (cr, 60, 28);
	cairo_show_text (cr, "Surface widget for direct Cairo drawing.");
	cairo_move_to (cr, 60, 44);
	cairo_show_text (cr, "And this widget was set 'dragable'.");
	cairo_destroy (cr);
	Surface.update ();
	Surface.setClickable (true);
	Surface.setDragable (true);

	// Add the background widget container to the main window and add all label
	// widgets to the background widget container
	MainWindow->add (Widget2);
	Widget2.add (Label1);
	Widget2.add (Label2);
	Widget2.add (Label2a);
	Widget2.add (Label3);
	Widget2.add (Label4);

	// Add the drawing surface widget directly to the main window
	MainWindow->add (Surface);

	// Add the foreground widget container to the main window and all sliders,
	// buttons and dials to the foreground widget container
	MainWindow->add (Widget);
	Widget.add (Slider1);
	Widget.add (Slider2);
	Widget.add (Slider3);
	Widget.add (Slider4);
	Widget.add (Dial1);
	Widget.add (Dial2);
	Widget.add (Dial3);
	Widget.add (Slider5);
	Widget.add (Slider6);
	Widget.add (Button1);
	Widget.add (Button2);
	Widget.add (Button3);
	Widget.add (Button4);
	Dial2.setCallbackFunction (BEvents::EventType::VALUE_CHANGED_EVENT, showValue);
	Label4.moveTo (150, 200);

	Surface.moveFrontwards ();

	// Run until main window is closed
	MainWindow->run ();
	delete MainWindow;

}
