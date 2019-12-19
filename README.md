comparepdf
==========

comparepdf is a command-line tool for comparing two PDF files.

The default comparison mode is text mode where the text of each
corresponding pair of pages is compared. As soon as a difference is
detected the program terminates with a message (unless `-v 0` is set) and
an indicative return code.

The options are `-c t` or `--compare=text` (the default) for text mode
comparisons or `-c a` or `--compare=appearance` for visual comparisons
(useful if diagrams or other images have changed), and `-v 1` or
`--verbose=1` for reporting differences (and saying nothing for matching
files): use `-v 0` for no reporting or `-v 2` for reporting both different
and matching files.

(For a GUI tool for showing the detailed differences between PDF files
see http://www.qtrac.eu/diffpdf.html.)

Home page: http://www.qtrac.eu/comparepdf.html


Compiling and Installing comparepdf
===================================

Prerequisites
-------------

- C++ compiler
- CMake and KDE's Extra CMake Modules
- Qt 5 libraries
- Poppler libraries

Linux and BSD users should be able to get everything through their package
management system — and some distros already include comparepdf so you don't
even have to build it.

Mac OS X users can get a compiler by installing Xcode; you'll need to get Qt and
Poppler separately.

Building and installing
-----------------------

1. Clone the repository

2. Change directory into the build directory
    $ cd comparepdf/build

3. Run cmake
    $ cmake ..

4. Run make
    $ make

5. Optional: Install the comparepdf executable
    $ make install


License
=======

This program was written by Mark Summerfield.
Copyright © 2011–2012 Qtrac Ltd. All rights reserved.

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 2 of the License, or (at your
option), any later version. This program is distributed in the hope that
it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License (in file gpl-2.0.txt) for more details.
