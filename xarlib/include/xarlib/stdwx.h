/*
 * xara-cairo, a vector drawing program
 *
 * Based on Xara XL, Copyright (C) 1993-2006 Xara Group Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */


// First the main include file
#include <wx/wx.h>

// Now specialized bits we might not have got through the above
#include <wx/bitmap.h>
#include <wx/cmdline.h>
#include <wx/cmdproc.h>
#include <wx/config.h>
#include <wx/cshelp.h>
#include <wx/dcbuffer.h>
#include <wx/debugrpt.h>
#include <wx/dcps.h>
#include <wx/display.h>
#include <wx/dir.h>
#include <wx/docmdi.h>
#include <wx/docview.h>
#include <wx/event.h>
#include <wx/except.h>
#include <wx/fileconf.h>
#include <wx/file.h>
#include <wx/filedlg.h>
#include <wx/filesys.h>
#include <wx/fontenum.h>
#include <wx/fs_mem.h>
#include <wx/fs_zip.h>
#include <wx/hashmap.h>
#include <wx/image.h>
#include <wx/imagpng.h>
#include <wx/ipc.h>
#include <wx/log.h>
#include <wx/rawbmp.h>
#include <wx/snglinst.h>
#include <wx/splash.h>
#include <wx/stdpaths.h>
#include <wx/sysopt.h>
#include <wx/tokenzr.h>
#include <wx/tooltip.h>
#include <wx/treectrl.h>
#include <wx/wxchar.h>
#include <wx/wxprec.h>
#include <wx/propdlg.h>
#include <wx/process.h>
#include <wx/xrc/xh_all.h>
#include <wx/xrc/xmlres.h>
#if wxUSE_LISTBOOK
#include <wx/listbook.h>
#endif
#if wxUSE_CHOICEBOOK
#include <wx/choicebk.h>
#endif
#if wxUSE_TREEBOOK
#include <wx/treebook.h>
#endif
#if wxUSE_TOOLBOOK
#include <wx/toolbook.h>
#endif
#if wxUSE_LIBGNOMEPRINT
#include <wx/gtk/gnome/gprint.h>
#endif

// Now platform dependent stuff
// FreeBSD does not provide backtrace()
#if !defined(__WXMAC__) && !defined(__FreeBSD__)
#include <wx/stackwalk.h>
#endif

#if defined(__WXMSW__)
#include <wx/msw/regconf.h>
#endif

#if !defined(EXCLUDE_FROM_XARLIB)
#include "xarlib/wxXtra.h"
#endif

#include <memory>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <new>
#if !defined(__WXMAC__)
#include <malloc.h>
#else
#include <malloc/malloc.h>
#endif

#if !defined(EXCLUDE_FROM_XARLIB)
#include <libxml/tree.h>
#include <libxml/parser.h>
#endif

#if wxUSE_DEBUGREPORT && wxUSE_XML
#define HAVE_DEBUGREPORT
#else
#undef HAVE_DEBUGREPORT
#endif

template< typename T >
T Abs( T val )
{
	return val < 0 ? -val : val;
}

#ifndef ABS
#define ABS(a) ( ((a) < 0) ? -(a) : (a) )
#endif

#if defined(__WXMSW__)
// min and max macros - only MSW because they blow up some of the headers
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#define camMax(a,b)  (((a) > (b)) ? (a) : (b))
#define camMin(a,b)  (((a) < (b)) ? (a) : (b))

// Defines and types moved from awindows.h

#define nobreak

// Defines and types moved from oiltypes.h

#define CAMAPI
#define CCAPI

#define DECLARE_SOURCE(String)
#define BASED_CODE

#include "xarlib/compatdef.h"
#include "xarlib/ensure.h"
#include "xarlib/errors.h"
#include "xarlib/memdebug.h"
#include "xarlib/exception.h"
#include "xarlib/mfccontainer.h"

#if !defined(EXCLUDE_FROM_XARLIB)
#include "xarlib/binreloc.h"
#endif
