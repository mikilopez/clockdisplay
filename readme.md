Description
===========

**clockdisplay** is a library for seven-segment 4-digits displays, typically used in alarm clocks.
This library is designed for use in Arduino projects.

How to install
==============

* Copy this folder into arduino sketchs folder\libraries
* Restart the Arduino IDE.
* Enjoy!

How to use
==========

There are a couple of examples, you can see them in your Arduino IDE, in File > Examples > clockdisplay.

Displays
========

This kind of displays usually have 16 pins to control all the segments:
* Two common cathodes.
* Seven pins for controlling first and second digit segments.
* Seven pins for controlling third and fourth digit segments.

They also have another pins for dots and some extra function, not deemed on this library.

Supported displays
==================

In ***models*** folder there is a pinout of wich pin activates wich segment with each cathode, for each model implemented in the library.

Display models supported:
* GC-5062S
* SL-2042-69TB

Related libraries
=================

If your display has a cathode (or anode) for each digit and a pin for each segment, then there is a [more suitable library for you](http://code.google.com/p/arduino-seven-segment "Arduino Seven Segment").
