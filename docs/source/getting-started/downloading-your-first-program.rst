Downloading your first program
===============================

.. _Opening Example Code:

Opening Example Code
---------------------

The EVO library comes with example code that you can use to help you get started on using the features of the EVO. Click on File -> Examples -> EVO -> EvoBasics -> EvoBasic

.. image:: ../pictures/openexamplecode.png
    :align: center

.. raw:: html

   <br><br>


.. _Connecting to the EVOX1 Board:

Connecting to the EVOX1 Board
------------------------------

1. Connect the EVOX1 to the computer and turn it on. A new port will appear in the drop down on the top left corner.

.. image:: ../pictures/selectboard.png
    :align: center

.. raw:: html

   <br><br>


2. Click on Select other board and port.

3. Search for ESP32S3 Dev Module and make sure that the correct COM port is selected.

.. image:: ../pictures/selectboardandport.png
    :align: center

.. raw:: html

   <br><br>

.. _Enabling Serial Port:

Enabling Serial Port
---------------------

The EVOX1 uses the USB peripheral pins for program upload and serial communication. To enable the serial port, click on tools -> USB CDC on Boot -> Enabled

.. image:: ../pictures/usbcdcenabled.png
    :align: center

.. raw:: html

   <br><br>

.. _Uploading to the EVOX1:

Uploading to the EVOX1
-----------------------

Click on the upload button on the top left corner to upload your program. The first compile and upload for each Arduino sketch will take the longest. Subsequent compilation will be faster as the compiler uses the already compiled libraries for upload. When upload is complete you should see the following.

.. image:: ../pictures/uploadcomplete.png
    :align: center

.. raw:: html

   <br><br>

