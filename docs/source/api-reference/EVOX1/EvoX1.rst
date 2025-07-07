Hub Controller
==============

.. doxygenclass:: EVOX1
   :project: API

.. rubric:: Initialisation & Setup

.. doxygenfunction:: EVOX1::begin
   :project: API

I2C Control Functions
---------------------

.. doxygenfunction:: EVOX1::selectI2CChannel
   :project: API

.. doxygenfunction:: EVOX1::scanI2CChannel
   :project: API

Battery Control Functions
-------------------------

.. doxygenfunction:: EVOX1::getTopBattery
   :project: API

.. doxygenfunction:: EVOX1::getBottomBattery
   :project: API

.. doxygenfunction:: EVOX1::getBattery
   :project: API

.. note::
   Battery values are returned in **volts**. Make sure to scale appropriately if using raw ADCs elsewhere.