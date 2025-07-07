LED & Buzzer
============

Buzzer Control Functions
------------------------

.. doxygenfunction:: EVOX1::playTone
   :project: API

.. warning::
   `playTone` is **blocking** — it will delay program execution.

LED Control Functions
---------------------

.. doxygenfunction:: EVOX1::setRGB
   :project: API

.. tip::
   Use colors to indicate system states — e.g., red = error, green = ready.