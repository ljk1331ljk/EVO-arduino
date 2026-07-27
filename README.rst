EVO Arduino Library
===================

One library supports the EVO X1E and EVO X1P. Controller selection is made at
compile time and user code instantiates the concrete controller:

.. code-block:: cpp

   #include <Evo.h>

   EvoX1E evo; // Build with -DEVO_BOARD_X1E

Use ``EvoX1P evo`` with ``-DEVO_BOARD_X1P`` for the X1P. A copy-ready
PlatformIO project is available in ``examples/PlatformIO``.

Documentation: https://evo.readthedocs.io
