comparepdf
==========

comparepdf is a command-line tool for comparing two PDF files.

For a GUI tool for showing the detailed differences between PDF files
see: http://www.qtrac.eu/diffpdf.html

Home page: http://www.qtrac.eu/comparepdf.html


Usage
-----

```
comparepdf [options] file1.pdf file2.pdf
```

The default comparison mode is text mode where the text of each
corresponding pair of pages is compared. As soon as a difference is
detected the program terminates with a message (unless `-v 0` is set) and
an indicative return code.


### Options

There are two comparison modes (`-c` or `--compare`):

  - `t` / `text` (default): Compare only the textual content of the PDFs.
  - `a` / `appearance`: Compare the PDFs visually.

There are three verbosity levels (`-v` or `--version`):

  - `0`: No text output
  - `1` (default): Text output only for differences
  - `2`: Text output for matching and differing files


Compiling and Installing comparepdf
-----------------------------------

### Prerequisites

- C++ compiler
- CMake and KDE's Extra CMake Modules
- Qt 5 libraries
- Poppler libraries

Linux and BSD users should be able to get everything through their package
management system — and some distros already include comparepdf so you don't
even have to build it.

Mac OS X users can get a compiler by installing Xcode; you'll need to get Qt and
Poppler separately.


### Building and installing

1. Clone the repository

    ```
    git clone https://github.com/tschoppi/comparepdf.git
    ```

2. Change directory into the build directory

    ```
    $ cd comparepdf/build
    ```

3. Run cmake

    ```
    $ cmake ..
    ```

4. Run make

    ```
    $ make
    ```

5. Optional: Install the comparepdf executable

    ```
    $ make install
    ```


License
-------

This program was written by Mark Summerfield.

Copyright © 2011–2012 Qtrac Ltd. All rights reserved.

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 2 of the License, or (at your
option), any later version. This program is distributed in the hope that
it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License (in file LICENSE) for more details.
