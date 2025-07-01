Display Functions
=================

.. doxygenfunction:: EVOX1::flipDisplayOrientation
   :project: API

.. doxygenfunction:: EVOX1::clearDisplay
   :project: API

.. rubric:: Writing to Display

.. doxygenfunction:: EVOX1::writeToDisplay(int, int, int, bool, bool)
   :project: API

.. doxygenfunction:: EVOX1::writeToDisplay(double, int, int, bool, bool)
   :project: API

.. doxygenfunction:: EVOX1::writeToDisplay(const char *, int, int, bool, bool)
   :project: API

.. note::
   These overloaded functions write data to the display at specific coordinates (x, y).
   You can write integers, floating-point values, or C-style strings.
   The optional `clear` parameter clears the display before writing,
   and the optional `draw` parameter immediately renders the display buffer.

.. doxygenfunction:: EVOX1::writeLineToDisplay(int, int, bool, bool)
   :project: API

.. doxygenfunction:: EVOX1::writeLineToDisplay(double, int, bool, bool)
   :project: API

.. doxygenfunction:: EVOX1::writeLineToDisplay(const char *, int, bool, bool)
   :project: API

.. note::
   These methods write a value to a specified line on the display.
   Overloads accept integers, floating point numbers, or C-style strings.

.. tip::
   For centered or multiline display, calculate position before calling these methods.

.. doxygenfunction:: EVOX1::drawDisplay
   :project: API

.. doxygenfunction:: EVOX1::setFontSize
   :project: API