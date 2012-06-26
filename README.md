xara-cairo
==========

Yet another port of XaraXL intended to build against modern open source libraries on BSD and Linux.

Tasks
-----

1. Eradicate implementation-specific use of [malloc]
2. Make it work with [libpng-1.5]

Building
--------

    $ AUTOMAKE_VERSION=1.10 AUTOCONF_VERSION=2.68 ./autogen.sh 
    $ ./configure
    $ gmake

[libpng-1.5]: http://www.libpng.org/pub/png/libpng-manual.txt
[malloc]: http://stackoverflow.com/questions/3886539/how-to-find-how-much-space-is-allocated-by-a-call-to-malloc
