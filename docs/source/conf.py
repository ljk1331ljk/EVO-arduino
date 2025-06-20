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

autosummary_generate = True

intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'sphinx': ('https://www.sphinx-doc.org/en/master/', None),
}
intersphinx_disabled_domains = ['std']

templates_path = ['_templates']

# -- Options for HTML output

html_title = "Evo Documentation"
html_theme = 'pydata_sphinx_theme'
html_theme_options = {
    # "logo": {
    #     "image_light": "_static/numpylogo.svg",
    #     "image_dark": "_static/numpylogo_dark.svg",
    # },
    "content_footer_items": ["last-updated"],
    "show_nav_level": 2,
    "external_links": [
        {
            "name": "Changelog", 
            "url": "https://github.com/PhoenixChee/Python-Recipe>"
        },
    ],
    "icon_links": [
        {
            "name": "GitHub",
            "url": "https://github.com/PhoenixChee/Python-Recipe",
            "icon": "fa-brands fa-github",
            "type": "fontawesome",
        },
        {
            "name": "Youtube",
            "url": "https://Yotube.com",
            "icon": "fa-brands fa-youtube",
            "type": "fontawesome",
        }
    ],
    "icon_links_label": "Quick Links",
    "announcement": "Here's a <a href='https://pydata.org'>PyData Announcement!</a>",
    "footer_start": ["copyright"],
    "footer_center": ["sphinx-version"],
}
html_show_sourcelink = False
html_copy_source = False
html_static_path = ['_static']
html_css_files = ["custom.css"]
html_js_files = ["custom.js"]

def setup(app):
    app.add_css_file("custom.css")
    app.add_js_file("custom.js")

# -- Options for EPUB output
epub_show_urls = 'footnote'

breathe_projects = {"API": "../doxygen/xml"}
breathe_default_project = "API"