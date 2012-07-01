#!/bin/sh

AUTORECONF=${AUTORECONF:-autoreconf}

${AUTORECONF} -f -i
( cd filters/SVGFilter ; ${AUTORECONF} -f -i )

# Required by autohell-tools
touch TODO ChangeLog AUTHORS README NEWS
