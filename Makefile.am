export XARAFLAGS = -Wno-write-strings \
	-I../PreComp -I../wxOil -I$(TOPDIR)/Kernel -I$(TOPDIR)/wxOil -I$(TOPDIR)/wxOil/Res \
	-I$(TOPDIR)/tools -I$(TOPDIR)/GDraw -I$(TOPDIR)/PreComp -I$(TOPDIR)/wxXtra \
	-DUSE_NATIVE_XLONG -DBUILDSHADOWS -DOLD_MATRIX_TRANSFORMATIONS \
	-DVECTOR_STROKING -DEXCLUDE_FROM_XARALX -DNEW_SHADOW_RENDER -DNO_XARACMS \
	-DNEW_FEATURES -DSHOWPORTNOTE -DDO_EXPORT
export TOPDIR

if PRECOMPILE_ENABLE
     PRECOMPILE_DIR = PreComp
else
     PRECOMPILE_DIR =
endif

if XARLIB_ENABLE
     XARLIB_DIR = xarlib
else
     XARLIB_DIR =
endif

if FILTERS_ENABLE
     FILTERS_DIRS = filters/SVGFilter
else
     FILTERS_DIRS =
endif

# Do not compile po directory if WXRC is broken (gentoo wxWidgets 2.6.3.2)
# Leave the '#po' on the end to keep automake quiet
if INTERNATIONAL_ENABLE
SUBDIRS = $(PRECOMPILE_DIR) wxXtra wxOil Kernel tools GDraw $(XARLIB_DIR) $(FILTERS_DIRS) po
else
SUBDIRS = $(PRECOMPILE_DIR) wxXtra wxOil Kernel tools GDraw $(XARLIB_DIR) $(FILTERS_DIRS)
endif

# We clean these here not in the wxOil makefile to prevent a loop
MOSTLYCLEANFILES=wxOil/xrc/xrc.d wxOil/xrc/xrc.stamp Resources/*

bin_PROGRAMS		= xara-cairo

xaracairo_CXXFLAGS = $(XARALXCXXFLAGS)
xaracairo_CPPFLAGS = $(XARALXCPPFLAGS)

if DARWIN_LINK
    xaracairo_SOURCES	= Kernel/*.o wxOil/*.o tools/*.o wxXtra/*.o GDraw/*.o
    xaracairo_LDSOURCE = $(xaracairo_SOURCES)
else
    xaracairo_SOURCES	= Kernel/libKernel.a wxOil/libwxOil.a tools/libTools.a wxXtra/libwxXtra.a GDraw/libGDraw-cairo.a
    xaracairo_LDSOURCE = -Wl,--start-group $(xaracairo_SOURCES) -Wl,--end-group
endif
xaracairo_LDFLAGS		= --debug $(WX_LIBS) $(LIBS) $(LIBXML2_LIBS)
xaracairo_LD			?= $(CXX)

xara-cairo$(EXEEXT) : $(xaracairo_SOURCES)
	$(xaracairo_LD) $(xaracairo_LDSOURCE) $(xaracairo_LDFLAGS) -o $@

UNZIP = unzip

release: all

resources:
	( rm -rf Resources ; mkdir -p Resources ; cd Resources ; $(UNZIP) -q ../wxOil/xrc/resources.xrs )

ACLOCAL_AMFLAGS = -I m4
