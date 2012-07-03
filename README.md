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
* png-1.5
* autoconf-2.6
* automake-1.10
* gettext-0.18
* libtool-2.4
* gmake-3.8
* subversion

OpenBSD
-------

    $ export AUTOMAKE_VERSION=1.10 AUTOCONF_VERSION=2.68
    $ ./autogen.sh && ./configure
    $ gmake

FreeBSD
-------

    # cd /usr/X11R6/bin
    # ln wxgtk2u-2.8-config wx-config
    $ ./autogen.sh && ./configure
    $ gmake

Linux
-----

    $ ./autogen.sh && ./configure
    $ make

News
----

- 2012-07-03: Builds on Ubuntu 12
- 2012-07-02: Builds on Debian 6.0
- 2012-06-29: Builds on FreeBSD 9.0
- 2012-06-27: Builds on OpenBSD 5.1

Delta from xara-cairo-0.7
-------------------------

- Adapted to [libpng-1.5](http://www.libpng.org/pub/png/libpng-manual.txt)
- Don't print memory warnings for platforms without malloc_usable_size(3)
- Build no longer requires unzip utility
- Compile with -Wno-write-strings 
- Use stdlib.h instead of malloc.h on BSD systems
- Removed stale project files for XCode and Visual Studio
- Patched to allow wxWidgets and glib2 to coexist
- Compile on gcc 4.6 without -fpermissive
- Removed conflicting jconfig.h to enable builds against libjpeg-turbo

History
-------

- 2010-05-11: First attempt at replacing CDraw with cairo [announced](http://lists.cairographics.org/archives/cairo/2010-May/019862.html) along with a new Git repo at git://repo.or.cz/xara-cairo.git
- 2007-11-06: Last commit to SVN
- 2007-01-30: Xara LTD [aquired by Magix](http://www.talkgraphics.com/showthread.php?25654-Xara-acquired-by-MAGIX)
- 2007-10-09: Xara Extreme marked broken and removed from FreeBSD ports
- 2006-04-04: XaraXL added to [FreeBSD ports](http://www.freebsdsoftware.org/graphics/xaralx.html)
- 2006-03-16: SVN repository made public at
  [xaraxtreme.org](http://www.xaraxtreme.org/) under the GPLv2 + a binary blob for the CDraw rendering engine


[malloc]: http://stackoverflow.com/questions/3886539/how-to-find-how-much-space-is-allocated-by-a-call-to-malloc
[malloc_usable_size]: http://readlist.com/lists/netbsd.org/current-users/3/17022.html
