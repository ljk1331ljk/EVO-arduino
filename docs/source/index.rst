Welcome to Evolution
====================

Welcome to the documentation for the Evo Microcontroller Platform, a cutting-edge solution designed to empower students, educators, and hobbyists in the fields of robotics, electronics, and IoT development. The Evo platform is built around the powerful ESP32-S3 microcontroller and offers seamless integration with EV3 Mindstorms motors and sensors, as well as support for third-party peripherals.

**Key Features**

Our mission is to make robotics and IoT development accessible, engaging, and scalable for all learners. Whether you’re a beginner exploring programming for the first time or an advanced user working on complex robotics projects, the Evo platform provides the tools and resources you need to succeed.

.. grid:: 2

   .. grid-item-card::
      
      :octicon:`rocket` **High-Performance Hardware**
      ^^^
      Powered by the ESP32-S3, the Evo platform delivers excellent processing power, Wi-Fi, and Bluetooth capabilities.

   .. grid-item-card:: 
      
      :octicon:`apps` **Modular Design**
      ^^^
      Connect EV3 motors, sensors, and third-party peripherals effortlessly.

.. grid:: 2

   .. grid-item-card:: 
      
      :octicon:`cpu` **Software Versatility**
      ^^^
      Program the platform using block-based programming or advanced IDEs, catering to diverse skill levels.

   .. grid-item-card:: 
      
      :octicon:`mortar-board` **Educational Focus**
      ^^^
      Designed for project-based learning and participation in robotics competitions, the Evo platform fosters creativity and innovation.

**What's New!**

.. versionadded:: 25-06-2025

   - Restructured the Navigation Panel, featuring: Hardware, Software & Programming Sections
   - Added a Contributor Guide Tab for developer documentation
   - Use ``custom.css`` for a nicer font (Inter & Poppins) & added a ``h1`` underline for easier readability

.. versionadded:: 20-06-2025

   - Added PyData Sphinx Theme into the Evo Documentation
   - Use ``sphinx.ext.autosectionlabel``, to auto-generated ``ref`` labels from header titles. No need for manual label for each section
   - Replaced ``.. image::`` with ``.. figure::`` for the automatic spacing below. No need to use ``.. raw:: html`` for the ``<br>`` spacing at the end of each image

.. toctree::
   :hidden:
   :maxdepth: 2
   
   user-guide/index
   contributor-guide/index
   library-reference/index
