xara-cairo
==========

Yet another port of XaraXL intended to build against modern open source
libraries on BSD and Linux.

Build Requirements
------------------

* wxWidgets-2.8
* gtk2-2.0
* cairo-1.10
* libxml-2.7
* png-1.5.6
* autoconf-2.6
* automake-1.10
* gettext-0.18
* libtool-2.4
* gmake-3.8
* ImageMagick-6.6
* subversion
* g++
* unzip

OpenBSD
-------

    $ AUTOMAKE_VERSION=1.10 AUTOCONF_VERSION=2.68 ./autogen.sh 
    $ AUTOMAKE_VERSION=1.10 AUTOCONF_VERSION=2.68 ./configure
    $ gmake

FreeBSD
-------

    # cd /usr/X11R6/bin
	# ln wxgtk2u-2.8-config wx-config

    $ ./autogen.sh 
    $ ./configure
    $ gmake

Ubuntu
------

    $ ./autogen.sh 
    $ ./configure
    $ make

[libpng-1.5]: http://www.libpng.org/pub/png/libpng-manual.txt
[malloc]: http://stackoverflow.com/questions/3886539/how-to-find-how-much-space-is-allocated-by-a-call-to-malloc
[pngexample]: http://svn.ghostscript.com/ghostscript/tags/libpng-1.2.8/example.c
[malloc_usable_size]: http://readlist.com/lists/netbsd.org/current-users/3/17022.html
