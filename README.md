xara-cairo
==========

Yet another port of XaraXL intended to build against modern open source libraries on BSD and Linux.

Requirements
------------

* wxWidgets-2.8
* cairo-1.10
* png-1.5
* ImageMagick-6

* autoconf-2
* gmake-3
* subversion
* unzip

Building - BSD
--------------

    $ AUTOMAKE_VERSION=1.10 AUTOCONF_VERSION=2.68 ./autogen.sh 
    $ AUTOMAKE_VERSION=1.10 AUTOCONF_VERSION=2.68 ./configure
    $ gmake

[libpng-1.5]: http://www.libpng.org/pub/png/libpng-manual.txt
[malloc]: http://stackoverflow.com/questions/3886539/how-to-find-how-much-space-is-allocated-by-a-call-to-malloc
[pngexample]: http://svn.ghostscript.com/ghostscript/tags/libpng-1.2.8/example.c
