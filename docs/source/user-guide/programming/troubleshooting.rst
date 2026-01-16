Troubleshooting
===============

Serial Monitoring Issues
------------------------

In any case when you encounter issues with serial prints not appearing in the Serial Monitor, you can try the following:

**Why it happens**

On boards like the ESP32-S3, the program may start running immediately after upload. By the time the COM port becomes available and the Serial Monitor is opened, the ESP32S3 may have already begun running its program for a few seconds.

You can make the program wait for the Serial Monitor to open before printing anything. Just add the following line inside your ``setup()`` function:

.. code-block:: cpp

   void setup()
   {
         while (!Serial); //Wait for Serial Monitor to be opened before printing

         //rest of the program
   }

This ensures that your serial prints will only start after the Serial Monitor is ready to receive them.