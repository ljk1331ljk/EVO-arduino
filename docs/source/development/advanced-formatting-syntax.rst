Advanced Formatting Syntax
==========================

Tables
------

.. dropdown:: ``.. list-table::``

   Creates simple tables using lists, useful when you want tables without complex syntax.

   - Use ``* -`` to start a new row.
   - Indent each cell content with spaces.
   - You can add multi-line content inside cells by indenting more.

   .. dropdown:: Options

      - ``:header-rows:`` — Number of rows at the top to treat as headers (usually 1).
      - ``:widths:`` — Controls column width in terms of percentage (numbers add up roughly to 100).
      - ``:align:`` — Table alignment on the page. Can be ``left``, ``center``, or ``right``.
      - ``:stub-columns:`` — Number of stub columns (like row headers) at the left.

   .. list-table:: This is a table
      :widths: 50 50
      :header-rows: 1
      :align: center

      * - Header 1
        - Header 2
      * - Row 1, Column 1
        - Row 1, Column 2
      * - Row 2, Column 1
        - Row 2, Column 2

   .. code-block:: rst

      .. list-table:: This is a table
         :widths: 50 50
         :header-rows: 1
         :align: center

         * - Header 1
           - Header 2
         * - Row 1, Column 1
           - Row 1, Column 2
         * - Row 2, Column 1
           - Row 2, Column 2

Grid
----

.. dropdown:: ``.. grid::`` ``.. grid-item::``

   The ``.. grid::`` directive creates a flexible grid layout container. The Grids are based on a 12 column system, which can adapt to the size of the viewing screen.

   Use it to arrange multiple items in rows and columns with spacing and alignment control using ``.. grid-item::`` under ``.. grid::``

   .. dropdown:: ``.. grid::`` Options

      - ``.. grid::`` — Number of columns One or four integers (for “xs sm md lg”) between ``1`` and ``12``.
      - ``:gutter:`` — Spacing between items. One or four integers (for “xs sm md lg”) between ``0`` and ``5``.
      - ``:margin:`` — Outer margin of grid. One (all) or four (top bottom left right) values from: ``0``, ``1``, ``2``, ``3``, ``4``, ``5``, ``auto``.
      - ``:padding:`` — Inner padding of grid. One (all) or four (top bottom left right) values from: ``0``, ``1``, ``2``, ``3``, ``4``, ``5``.
      - ``:outline:`` — Create a border around the grid.

   .. dropdown:: ``.. grid-item::`` Options 

      - ``:columns:`` — Number of columns the grid-item will take up (out of 12). One or four integers (for “xs sm md lg”) between ``1`` and ``12``, or ``auto`` to adapt to content width.
      - ``:margin:`` — Outer margin of grid item. One (all sides) or four (top bottom left right) values from: ``0``, ``1``, ``2``, ``3``, ``4``, ``5``, ``auto``.
      - ``:padding:`` — Inner padding of grid item. One (all sides) or four (top bottom left right) values from: ``0``, ``1``, ``2``, ``3``, ``4``, ``5``.
      - ``:child-direction:`` — Direction of children inside grid item. Options: ``column`` (default) or ``row``.
      - ``:child-align:`` — Alignment of children along child-direction. Options: ``start`` (default), ``end``, ``center``, ``justify``, ``spaced``.
      - ``:outline:`` — Create a border around the grid item.

   Example:

   .. grid:: 2 2 3 4
         :gutter: 1
         :outline:

         .. grid-item::
            A

         .. grid-item::
            B

         .. grid-item::
            :outline:
            
            C

         .. grid-item::
            D

   .. code-block:: rst

      .. grid:: 2 2 3 4
         :gutter: 1
         :outline:

         .. grid-item::
            A

         .. grid-item::
            B

         .. grid-item::
            :outline:

            C

         .. grid-item::
            D

   .. note::
   
      Try resizing your screen! Notice how the grid changes its columns based on the size of the screen

.. dropdown:: ``.. grid-item-card::``

   The ``.. grid-item-card::`` directive creates a card-style container inside a grid.

   Cards usually have padding, a border, and sometimes a shadow, making them visually stand out as individual items.

   .. dropdown:: Options

      - ``:columns:`` — Number of columns the grid-item will take up (out of 12). One or four integers (for “xs sm md lg”) between ``1`` and ``12``, or ``auto`` to adapt to the content.
      - ``:margin:`` — Outer margin of grid item. One (all sides) or four (top bottom left right) values from: ``0``, ``1``, ``2``, ``3``, ``4``, ``5``, ``auto``.
      - ``:padding:`` — Inner padding of grid item. One (all sides) or four (top bottom left right) values from: ``0``, ``1``, ``2``, ``3``, ``4``, ``5``.
      - ``:link:`` — URL to link the entire grid item.
      - ``:link-type:`` — Type of link. Use ``url`` for external links or ``ref`` for internal references.

   Example:

   .. grid:: 3 3 3 3
      :gutter: 1

      .. grid-item-card::
         :link: https://example.com
         :link-type: url

         **Card A**
         ^^^
         This card links to an external URL. 

      .. grid-item-card::
         :link: grid
         :link-type: ref

         **Card B**
         ^^^
         This card links to a section label named "Grid". 

      .. grid-item-card::
         :link: index
         :link-type: doc

         **Card C**
         ^^^
         This card links to an RST file in the documentation. 

   .. code-block:: rst

      .. grid:: 3 3 3 3
         :gutter: 1

         .. grid-item-card::
            :link: https://example.com
            :link-type: url

            **Card A**
             ^^^
            This card links to an external URL. Use ``:link-type: url``

         .. grid-item-card::
            :link: grid
            :link-type: ref

            **Card B**
            ^^^
            This card links to a section label named "Grid". Use ``:link-type: ref``

         .. grid-item-card::
            :link: index
            :link-type: doc

            **Card C**
            ^^^
            This card links to an RST file in the documentation. Use ``:link-type: doc``

   .. note::

      Cards adapt their size according to the grid columns and support spans to create flexible layouts.


Card
----

Dropdowns
---------

Tabs
----

Badges
------