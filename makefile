CC = g++
SRC = BWidgets-demo.cpp BWidgets/DrawingSurface.cpp BWidgets/TextToggleButton.cpp BWidgets/TextButton.cpp BWidgets/ToggleButton.cpp BWidgets/Button.cpp BWidgets/DialWithValueDisplay.cpp BWidgets/VSliderWithValueDisplay.cpp BWidgets/HSliderWithValueDisplay.cpp BWidgets/Dial.cpp BWidgets/VSlider.cpp BWidgets/HSlider.cpp BWidgets/RangeWidget.cpp BWidgets/ValueWidget.cpp BWidgets/Label.cpp BWidgets/Widget.cpp BWidgets/BStyles.cpp BWidgets/BColors.cpp BWidgets/BEvents.cpp BWidgets/BValues.cpp BWidgets/cairoplus.c BWidgets/pugl/pugl_x11.c

all:
	$(CC) -iquote ./ -o demo $(SRC) -DPUGL_HAVE_CAIRO `pkg-config --cflags --libs x11 cairo`