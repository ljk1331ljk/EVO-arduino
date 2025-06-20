Downloading Your First Program
==============================

Opening Example Code
--------------------

The EVO library comes with example code that you can use to help you get started on using the features of the EVO. 

Click on File :octicon:`arrow-right` Examples :octicon:`arrow-right` EVO :octicon:`arrow-right` EvoBasics :octicon:`arrow-right` EvoBasic

.. figure:: ../_static/images/openexamplecode.png
   :alt: Example Code
   :width: 600px
   :align: center

Connecting to the EVOX1 Board
-----------------------------

1. Connect the EVOX1 to the computer and turn it on. A new port will appear in the drop down on the top left corner.

.. figure:: ../_static/images/selectboard.png
   :alt: Board Selection
   :width: 600px
   :align: center

2. Click on Select other board and port.

3. Search for **ESP32S3 Dev Module** and make sure that the correct ``COM`` port is selected.

.. figure:: ../_static/images/selectboardandport.png
   :alt: Other Board and Port Selection
   :width: 600px
   :align: center

Enabling Serial Port
--------------------

The EVOX1 uses the USB peripheral pins for program upload and serial communication. To enable the serial port, click on tools :octicon:`arrow-right` USB CDC on Boot :octicon:`arrow-right` Enabled

.. figure:: ../_static/images/usbcdcenabled.png
   :alt: USB CDC Enabled
   :width: 600px
   :align: center

Uploading to the EVOX1
----------------------

Click on the upload button on the top left corner to upload your program. The first compile and upload for each Arduino sketch will take the longest. Subsequent compilation will be faster as the compiler uses the already compiled libraries for upload. When upload is complete you should see the following.

.. figure:: ../_static/images/uploadcomplete.png
   :alt: Upload Complete
   :width: 600px
   :align: center
