#!/usr/bin/env python
"""
Toolbit Library
https://github.com/toolbitorg/ToolbitSDK
"""

from distutils.core import setup, Extension
import platform
from os import path

# Get the long description from the README file
here = path.abspath(path.dirname(__file__))
with open(path.join(here, 'README.md'), encoding='utf-8') as f:
    long_description = f.read()

sources = ['toolbit/toolbit_wrap.cxx','toolbit/tbi_core.cpp',
    'toolbit/tbi_device.cpp', 'toolbit/tbi_service.cpp', 'toolbit/attribute.cpp',
    'toolbit/tbit.cpp', 'toolbit/basicdemo.cpp', 'toolbit/chopper.cpp',
    'toolbit/dmm.cpp', 'toolbit/tbi_device_manager.cpp', 'toolbit/adc.cpp',
    'toolbit/adc_hw.cpp', 'toolbit/gpio_hw.cpp', 'toolbit/i2c_hw.cpp',
    'toolbit/pin.cpp']

osname = platform.system()
if osname == 'Linux':
    toolbit_module = Extension('toolbit._toolbit',
        sources + ['toolbit/linux/hid.c'],
        include_dirs=['toolbit'],
        libraries=['udev'],
        extra_compile_args=["-std=gnu++11"],
    )
elif osname == 'Darwin':
# Cannot mix .c and .cpp files because of -std=c++11 option
# 'hid.c',
    toolbit_module = Extension('toolbit._toolbit',
        sources + ['toolbit/macos/hid.c'],
        include_dirs=['toolbit'],
#       libraries=['stdc++ -framework IOKit -framework Carbon'],
        extra_compile_args=['-std=c++11'],
    )
elif osname == 'Windows':
    toolbit_module = Extension('toolbit._toolbit',
        sources + ['toolbit/mswin/hid.c'],
        include_dirs=['toolbit'],
        libraries=['setupapi'],
    )

setup (
    name = 'toolbit-lib',
    version = '0.0.1',
    description = 'Toolbit library',
    long_description = long_description,
    long_description_content_type='text/markdown',
    url = 'https://github.com/toolbitorg/ToolbitSDK',
    author ='Junji Ohama',
    author_email = 'junji.ohama@toolbit.org',
    classifiers=[  # Optional
        # How mature is this project? Common values are
        #   3 - Alpha
        #   4 - Beta
        #   5 - Production/Stable
        'Development Status :: 4 - Beta',

        # Indicate who your project is intended for
        'Intended Audience :: Developers',
        'Topic :: Measurement and automation',

        # Pick your license as you wish
        'License :: OSI Approved :: GPL-2.0',
        'Programming Language :: Python :: 3',
        #'Programming Language :: Python :: 3.7',
    ],
    keywords = 'toolbit sdk library',
    packages=['toolbit'],
    python_requires='>=3.5',
    #install_requires = [''],
    #entry_points={  # Optional
    #    'console_scripts': [
    #        'sample=sample:main',
    #    ],
    #},
    ext_modules = [toolbit_module],
    project_urls={
        'Bug Reports': 'https://github.com/toolbitorg/ToolbitSDK/issues',
        'Source': 'https://github.com/toolbitorg/ToolbitSDK',
    },
)
