Battery Functions
=================

.. doxygenvariable:: EVOX1::charger
   :project: API

.. doxygenfunction:: EVOX1::getTopBattery
   :project: API

.. doxygenfunction:: EVOX1::getBottomBattery
   :project: API

.. doxygenfunction:: EVOX1::getBattery
   :project: API

.. note::
   Battery values are returned in **volts**. Make sure to scale appropriately if using raw ADCs elsewhere.