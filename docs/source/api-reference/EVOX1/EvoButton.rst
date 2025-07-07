Button
======

Button Control Functions
------------------------

.. doxygenfunction:: EVOX1::waitForButton
   :project: API

.. doxygenfunction:: EVOX1::waitForPress
   :project: API

.. doxygenfunction:: EVOX1::waitForRelease
   :project: API

.. doxygenfunction:: EVOX1::waitForBump
   :project: API

.. doxygenfunction:: EVOX1::getButton
   :project: API

.. important::
   Avoid using `waitForButton()` in loops — prefer `waitForBump()` for debounce reliability.