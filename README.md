xara-cairo
==========

An fast, 100% open source vector drawing program based on XaraLX

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

OpenBSD
-------

    $ export AUTOMAKE_VERSION=1.10 AUTOCONF_VERSION=2.68
    $ ./autogen.sh && ./configure --enable-filters
    $ gmake

FreeBSD
-------

    # cd /usr/X11R6/bin
    # ln wxgtk2u-2.8-config wx-config
    $ ./autogen.sh && ./configure --enable-filters
    $ gmake

Linux
-----

    $ ./autogen.sh && ./configure --enable-filters
    $ make

Fixes and Additions
-------------------

(eradman)

- Adapted to [libpng-1.5](http://www.libpng.org/pub/png/libpng-manual.txt)
- Don't print memory warnings for platforms without malloc_usable_size(3)
- Compile with -Wno-write-strings 
- Use stdlib.h instead of malloc.h on BSD systems
- Removed stale project files for XCode and Visual Studio
- Patched to allow wxWidgets and glib2 to coexist
- Compile on gcc 4.6 without -fpermissive
- Removed conflicting jconfig.h to enable builds against libjpeg-turbo
- Reduced source line count by 142k using a concise Copyright and GPLv2 notice
- Build no longer requires svn and unzip
- No more splash screen
- Exclude files from the repo that are auto-generated or copied
- Removed 4799 to obsolete header file references and DECLARE tags
- Allow user to select so-called virtual fonts, such as 'Monospace'

(ed44)

- Fix the EXTEND_REPEAT and EXTEND_REFLECT options og the bitmap fill
- Fix the bitmap gallery
- Fix the colorline in the HSV coloreditor
- Fix PNG/JPEG bitmap import/handling

History
-------

- 2012-07-03: This fork of xara-cairo builds on Ubuntu 12, Debian 6.0, FreeBSD 9.0 and OpenBSD 5.1
- 2010-05-11: First attempt at replacing CDraw with cairo [announced](http://lists.cairographics.org/archives/cairo/2010-May/019862.html) along with a new Git repo at git://repo.or.cz/xara-cairo.git
- 2007-11-06: Last commit to SVN
- 2007-01-30: Xara LTD [aquired by Magix](http://www.talkgraphics.com/showthread.php?25654-Xara-acquired-by-MAGIX)
- 2007-10-09: Xara Extreme marked broken and removed from FreeBSD ports
- 2006-04-04: XaraXL added to [FreeBSD ports](http://www.freebsdsoftware.org/graphics/xaralx.html)
- 2006-03-16: SVN repository made public at
  [xaraxtreme.org](http://www.xaraxtreme.org/) under the GPLv2 + a binary blob for the CDraw rendering engine


[malloc]: http://stackoverflow.com/questions/3886539/how-to-find-how-much-space-is-allocated-by-a-call-to-malloc
[malloc_usable_size]: http://readlist.com/lists/netbsd.org/current-users/3/17022.html
