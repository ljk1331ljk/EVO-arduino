User Guide
==========

This guide aims to will walk you through the essentials & important features to get your Evo up and running quickly. With clear steps and helpful tips, you’ll be ready to start building exciting projects in no time.

What You'll Learn & Do
^^^^^^^^^^^^^^^^^^^^^^

.. grid:: 1 1 2 2
   :gutter: 2

   .. grid-item-card::
      :link: hardware/overview
      :link-type: doc

      **Hardware Overview**
      ^^^
      Learn about voltage compatibility, logic levels, and power considerations when connecting sensors and servos to the Evo. 

   .. grid-item-card:: 
      :link: programming/evo-connection
      :link-type: doc

      **Connect & Program Evo**
      ^^^
      Learn how to connect the Evo, navigate the IDEs and configure the settings to download your programs into your Evo.

IDEs You Can Use
^^^^^^^^^^^^^^^^

There are 2 platforms you can choose to code your programs. Arduino IDE & PlatformIO in VSCode. 

.. grid:: 1 1 2 2
   :gutter: 2

   .. grid-item-card::
      :link: software/arduino-installation
      :link-type: doc

      **Use Arduino IDE 2 [Recommended]**
      ^^^
      Learn how to install and update Arduino libraries in Arduino IDE, and troubleshoot common installation issues.

      :octicon:`thumbsup` Simple IDE, beginner-friendly
      
      :octicon:`thumbsdown` Slow compilation

   .. grid-item-card::
      :link: software/platformio-installation
      :link-type: doc

      **Use PlatformIO IDE in VSCode**
      ^^^
      Learn how to install and update Arduino libraries in PlatformIO IDE, and troubleshoot common installation issues.

      :octicon:`thumbsup` Faster compilation of programs

      :octicon:`thumbsdown` Sophisticated IDE, not beginner-friendly

.. toctree::
   :maxdepth: 2
   :caption: Hardware
   :hidden:

   hardware/overview
   hardware/first-boot
   hardware/motors/index
   hardware/sensors/index

.. toctree::
   :maxdepth: 2
   :caption: Software
   :hidden:

   software/arduino-installation
   software/platformio-installation

.. toctree::
   :maxdepth: 2
   :caption: Programming
   :hidden:

   programming/evo-connection
   programming/downloading-programs