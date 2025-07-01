Private Classes
===============

.. note::
   The `EVOX1` class is a **singleton**. Use `EVOX1::getInstance()` to interact with it.
   Do not instantiate it manually.

Singleton Access
----------------

.. doxygenfunction:: EVOX1::getInstance
   :project: API

.. admonition:: Internal Construction Details
   :class: hint

   The constructor and copy operations are private or deleted to enforce singleton access.

Internal I2C Functions
----------------------

.. doxygenvariable:: EVOX1::i2CDevice
   :project: API

.. doxygenvariable:: EVOX1::evoPWMDriver
   :project: API

Enums
-----

.. doxygenenum:: ButtonState
   :project: API

.. doxygenenum:: PinState
   :project: API