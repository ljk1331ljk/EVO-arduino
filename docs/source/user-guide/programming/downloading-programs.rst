Downloading Your First Program
==============================

The Evo library comes with example program that you can use to help you get started on using the features of the Evo.

EvoBasic
--------

Arduino
^^^^^^^

Click on File :octicon:`arrow-right` Examples :octicon:`arrow-right` EVO :octicon:`arrow-right` EvoBasics :octicon:`arrow-right` EvoBasic

.. figure:: /_static/images/open-example-program.png
   :alt: Example Program
   :width: 100%
   :align: center

Click on the upload button on the top left corner to upload your program. The first compile and upload for each Arduino sketch will take the longest. Subsequent compilation will be faster as the compiler uses the already compiled libraries for upload. When upload is complete you should see the following.

.. figure:: /_static/images/uploadcomplete.png
   :alt: Upload Complete
   :width: 100%
   :align: center

PlatformIO
^^^^^^^^^^

1. The ``EvoBasic.ino`` can be found under ``lib/Evo/examples/basic/EvoBasic``
2. Copy & paste the program into the ``main.ino`` in the ``src`` folder

.. important:: 

   PlatformIO compilies the programs only in the ``src`` folder. If you wish to use example programs, copy & paste them inside the ``src/main.ino``.

3. Upload the program using the PlatformIO IDE Toolbar located in the left corner. It contains quick access buttons for the popular commands.

   - PlatformIO: Home
   - PlatformIO: Build
   - **PlatformIO: Upload [Select This]**
   - PlatformIO: Clean
   - PlatformIO: Serial Monitor
   - Set Port

.. figure:: /_static/images/toolbar-upload-pio.png
   :alt: PlatformIO Toolbar
   :width: 100%
   :align: center

.. figure:: /_static/gifs/upload-example-program-pio.gif
   :alt: Upload Example Program
   :width: 100%
   :align: center

4. When upload is complete you should see the following

.. figure:: /_static/images/upload-success-pio.png
   :alt: Upload Success
   :width: 100%
   :align: center

EvoHC05
-------

If you want to continue experimentaing with the Evo. You can try connecting the Evo via HC05 (Bluetooth). A guide on how to enable Bluetooth is explain :ref:`here<Bluetooth>`.