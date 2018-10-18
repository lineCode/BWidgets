# BWidgets
Widget toolkit based on Cairo and Pugl.

This is a simple widget toolkit for small programs and plugins that can directly be included. 

Version 0.1 alpha (status: testing)

Dependencies
------------
* Cairo
* X11 (for Linux systems, for MacOS X and Windows see description)

Install the developers versions of these packages first. BWidgets may also be adapted to MacOS X and Windows. For these systems, take hands on and adapt the final parameter in line 2 of the makefile. 

Installation
------------
Clone this repository. To build the demo simply call
```
make
```
from the root directory of the clone.

Run the demo
------------
Simply call
```
./demo
```

Usage
-----
BWidgets is a toolkit intended to use directly in your projects. Simply copy the BWidgets folder (includig its subfolders)
into your project folder. Remove the widgets you don't need, but take care for dependencies.

A more detailed description about the toolkit itself and its widgets will follow soon.
