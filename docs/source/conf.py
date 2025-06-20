# Configuration file for the Sphinx documentation builder.

# -- Project information
# import os
# import sys
# sys.path.insert(0, os.path.abspath('..'))

project = 'EVO'
copyright = '2024, TribalStudioz'
author = 'Lai Jun Kang'

release = '0.1'
version = '0.1.0'

# -- General configuration

extensions = [
    'sphinx.ext.duration',
    'sphinx.ext.doctest',
    'sphinx.ext.autodoc',
    'sphinx.ext.todo',
    'sphinx.ext.autosummary',
    'sphinx.ext.autosectionlabel',
    'sphinx_design',
    'sphinx_copybutton',
    'breathe',
    'myst_parser',
]

# -- Extension configuration

# -- Options for Sphinx Autosummary
autosummary_generate = True

# -- Options for Sphinx Todo
todo_include_todos = True

# -- Options for Intersphinx mapping
intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'sphinx': ('https://www.sphinx-doc.org/en/master/', None),
}
intersphinx_disabled_domains = ['std']

# -- Options for EPUB output
epub_show_urls = 'footnote'

# -- Options for Breathe
breathe_projects = {"API": "../doxygen/xml"}
breathe_default_project = "API"

templates_path = ['_templates']

# -- Options for HTML output

html_title = "Evo Documentation"
html_theme = 'pydata_sphinx_theme'
html_theme_options = {
    # "logo": {
    #     "image_light": "_static/numpylogo.svg",
    #     "image_dark": "_static/numpylogo_dark.svg",
    # },
    "collapse_navigation": True,
    "show_nav_level": 2,
    "show_toc_level": 3,
    "icon_links_label": "Quick Links",
    "icon_links": [
        {
            "name": "GitHub",
            "url": "https://github.com/ljk1331ljk/EVO-arduino",
            "icon": "fa-brands fa-github",
            "type": "fontawesome",
        },
    ],
    "external_links": [
        {
            "name": "Changelog", 
            "url": "https://github.com/ljk1331ljk/EVO-arduino/releases"
        },
    ],
    "footer_start": ["copyright"],
    "footer_center": ["sphinx-version"],
}
html_show_sourcelink = False
html_copy_source = False
html_static_path = ['_static']