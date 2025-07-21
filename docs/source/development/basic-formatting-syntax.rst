Basic Formatting Syntax
=======================

Paragraphs
----------

Write plain text separated by a blank line. Paragraphs are automatically wrapped.

Example:

    This is a paragraph.

    This is another paragraph.

---

Headings
--------

Use underlines (and optionally overlines) with these characters:

- `=` for main title
- `-` for section
- `~` for subsection
- `^` for smaller headings

Example:

Main Title
==========

Section
-------

Subsection
~~~~~~~~~~

---

Bold, Italics, Highlights
-------------------------

- **Bold**: Surround text with double asterisks `**bold**`
- *Italics*: Use single asterisks `*italics*`
- ``Inline code``: Use double backticks ``inline code``

Example:

This is **bold** text, this is *italic* text, and this is ``inline code``.

---

Internal Links
--------------

Create labels and link to them inside the document.

Define a label:

.. _my-label:

Then link to it:

See the section :ref:`my-label`.

Example:

.. _example-section:

Example Section
---------------

Go back to the :ref:`example-section`.

---

External Links
--------------

Use backticks and angle brackets:

`Google <https://www.google.com>`_

This will create a clickable link.

---

Lists
-----

- Bullet lists use `-` or `*`

Example:

- Item 1
- Item 2
  - Subitem 2.1
  - Subitem 2.2

1. Numbered lists use numbers with a period

Example:

1. First item
2. Second item
3. Third item

Code Blocks
-----------

Use double colons `::` after a paragraph, then indent the code block.

Example:

::

    def hello():
        print("Hello, world!")

Or use explicit code-block directive for syntax highlighting:

.. code-block:: python

    def hello():
        print("Hello, world!")