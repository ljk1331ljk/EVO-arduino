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
    'breathe',
    'sphinx.ext.duration',
    'sphinx.ext.doctest',
    'sphinx.ext.autodoc',
    'sphinx.ext.autosummary',
    'sphinx.ext.intersphinx',
    'sphinx_design',
    'sphinx_copybutton',
]

intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'sphinx': ('https://www.sphinx-doc.org/en/master/', None),
}
intersphinx_disabled_domains = ['std']

templates_path = ['_templates']

# -- Options for HTML output

html_theme = 'pydata_sphinx_theme'
html_theme_options = {
    "content_footer_items": ["last-updated"],
    "external_links": [
        {"name": "Changelog", "url": "https://github.com/PhoenixChee/Python-Recipe>"},
    ],
    "icon_links": [
        {
            "name": "GitHub",
            "url": "https://github.com/PhoenixChee/Python-Recipe",
            "icon": "fa-brands fa-square-github",
            "type": "fontawesome",
        },
        {
            "name": "Youtube",
            "url": "https://Yotube.com",
            "icon": "fa-brands fa-square-youtube",
            "type": "fontawesome",
        }
    ],
    "icon_links_label": "Quick Links",
    "announcement": "Here's a <a href='https://pydata.org'>PyData Announcement!</a>",
}

# -- Options for EPUB output
epub_show_urls = 'footnote'

breathe_projects = {"API": "../doxygen/xml"}
breathe_default_project = "API"