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

// Contains general initialisation of the kernel, after InitPostTools1() is called

/*
*/

#include "camtypes.h"
#include "selall.h"
#include "keypress.h"
#include "scunit.h"
#include "finfodlg.h"
#include "aligndlg.h"
#include "bmpprefs.h"
#include "renddlg.h"
#include "tracedlg.h"
#include "appprefs.h"
#include "coldlog.h"
#include "opnudge.h"
#include "combshps.h"
#include "colcomp.h"
#include "bmpcomp.h"
#include "princomp.h"
#include "nodebmp.h"
#include "dragcol.h"
#include "dragpick.h"
#include "dragbmp.h"
//#include "convert.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "diagnost.h"
//#include "rndrgn.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "osrndrgn.h"
//#include "ccobject.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "scrcamvw.h"
//#include "docview.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "document.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "clikmods.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "transop.h"
//#include "attrmgr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "ctrlhelp.h"
//#include "fonts.h"
//#include "units.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "menuops.h"
#include "hotkeys.h"
//#include "oilkeys.h"
//#include "oilbtns.h"
#include "progress.h"
#include "oilmenus.h"
#include "clipint.h"
//#include "fillattr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "fontman.h"
#include "fntcache.h"
#include "pathops.h"
#include "tunemem.h"
//#include "epsfiltr.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "prncamvw.h"
#include "oilruler.h"
//#include "registry.h"
#include "appstate.h"
//#include "basebar.h"
//#include "makebmp.h"
#include "ccpanose.h"
#include "unitcomp.h"	// UnitListComponent
#include "infocomp.h"	// DocInfoComponent
#include "viewcomp.h"
#include "fontcomp.h"
#include "prnmkcom.h"
#include "printprg.h"
#include "hlinkdlg.h"
#include "strkcomp.h"
#include "tmpltdlg.h"
//#include "cxfrech.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "styles.h"
#include "brshcomp.h"
//#include "dlgcthlp.h"
//#include "xpehost.h"
#include "editsel.h"
#include "camview.h"
#include "selmedia.h"

// Normal exe's and standalones
BOOL InitPostTools2()
{
	return (
			SelectAllOp::Init() &&				// Init the SelectAll op
			SelectNoneOp::Init() &&				// Init the SelectNone op
#ifndef EXCLUDE_FROM_XARALX
PORTNOTE("other","Removed a large amount of initialization")
			XPEEditOp::Init() &&				// Init the XPE Edit operation
			EditSelectionOp::Init() &&			// Init the "Edit Selection" op
			KeyPress::Init() &&					// Init the key press system
#endif
			FileInfo::Init() &&					// Init the document info dialogue

			ArrangeAlignment::Init() &&			// Init the arrange alignment dialogue
			OpAlign::Init() &&					// Init the align op
#ifndef EXCLUDE_FROM_XARALX
			BmpPrefsDlg::Init() &&				// Init the export bitmap options dialog
#endif
			TraceDlg::Init() &&					// Init the trace dialog
#ifndef EXCLUDE_FROM_XARALX
			WebAddressDlg::Init() &&
			PhotoCDDlg::Init() &&				// Init the import PhotoCD options dialog
#endif
			RenderDemoDlg::Init() &&			// Init the Render Demo Dialog
			AppPrefsDlg::Init() &&				// Init the application preference/options dialog
#ifndef EXCLUDE_FROM_XARALX
			TemplateDialog::Init() &&
			DocPrefsDlg::Init() &&				// Init the document preference/options dialog
#endif
			StandardUnit::Init() &&				// create some standard scale units (scunit.h)
			ColourEditDlg::Init() &&			// Init the colour editor dialogue
#ifndef EXCLUDE_FROM_XARALX
			OpConvertToBitmap::Init() &&
#endif
			OpNudge::Init() &&					// Init the nudge ops
			OpCombineShapes::Init() &&			// init the shape combining ops

			OpMenuSelectPathPoints::Init() &&
			OpCreateNodeBitmap::Init() &&

			ColourListComponentClass::Init() && // Init & register the colour list component
			BitmapListComponentClass::Init() && // Init & register the bitmap list component
			UnitListComponentClass::Init()	 && // Init & register the units component
			DocInfoComponentClass::Init()	 && // Init & register the document information component
		 	WizOpStyleComponentClass::Init() && // Init & register the styles component

			PrintComponentClass::Init()		 && // Init & register the print component
			PrintMarkComponentClass::Init()	 && // Init & register the print marks component
			ViewComponentClass::Init()		 && // Init & register the view component
			FontComponentClass::Init()		 && // Init & register the font component

// Neville 5/8/97 remove Stroking code
#ifdef VECTOR_STROKING
			StrokeComponentClass::Init()	 && // Init & register the stroke component
#endif // VECTOR_STROKING

			BrushComponentClass::Init()      && // Init & register the brush component
			RenderRegion::InitPrefs() &&		// Get the render region prefs from the .INI
			OSRenderRegion::Init() &&			// init GDI preferences
			SimpleCCObject::Init() &&			// Init the Memory tracking preferences
			ClickModifiers::DeclarePrefs() &&
			DocView::DeclarePreferences() &&	// Deals with DocViews preferences
			Document::ReadPrefs() &&			// read in class Document's preferences
			Convert::Init() &&					// Read number of decimal places, decimal point
												// and thousands seperator characters from
												// operating system .
			ColourDragInformation::Init() &&
			ColourPickerDragInformation::Init() &&
			BitmapDragInformation::Init() &&
PORTNOTE("other","Removed more initialization")
#ifndef EXCLUDE_FROM_XARALX
			InitDiagnosticPrefs() &&			// Get the diagnostic preferences
#endif			
			CCamView::ReadViewPrefs() &&
			PrintMonitor::InitPrefs() &&
			PrintProgressDlg::Init() &&

#ifndef EXCLUDE_FROM_XARALX
			BaseBar::DeclarePreferences() &&

			TransOperation::DeclarePrefs() &&
#endif
			AttributeManager::InitDefaults() &&
PORTNOTE("other","Removed yet more initialization")
#ifndef EXCLUDE_FROM_XARALX
			ControlHelper::Init() &&
			DialogControlHelper::Init() &&
			FontFactory::Init() &&

			// The next three inits must be performed in this order
#endif
			Unit::Init() &&						// init the unit class and default units
			DocUnitList::Init() &&				// Init the doc unit list system
			DimScale::Init()  &&					// Init the dimension scaling system
			OpToolSelect::Init() &&				// Register Tool Selection operation


PORTNOTE("other","Removed even more initialization")
#ifndef EXCLUDE_FROM_XARALX
	        // Must always be initialised after all the tools have been
			ToolBarOp::Init() &&				// Make the bar of tool bitmaps
#endif
			HotKey::Init() &&					// Init hotkey system AFTER the tool op descs have been registered
PORTNOTE("other","Removed even more initialization")
#ifndef EXCLUDE_FROM_XARALX
			InitHotKeySystem() &&				// Initialise Hot Key system
			InitButtonBar() &&					// Initialise ButtonBar
#endif
			Progress::Init() &&					// Initialise progress cursor/bar displays

			InternalClipboard::Initialise()	&&	// Create the application's internal clipboard cache
												// (this is a DOCUMENT, so must be left until fairly late)

			InitMenuSystem() &&					// Initialise Menu system (keep very last)
												// (esp. after all Register'ing has been done)

			AttrFillGeometry::Init() &&			// Initialise the fill editing operations

			EPSFilter::InitPrefs() &&			// Initialise default font mappings and
												// EPS export prefs
#ifndef DISABLE_TEXT_RENDERING
			FontCache::Init() &&
#endif
			TunedMemory::Init()	&&				// declare prefs for the memory manager

			OILRuler::Init() &&					// set the ruler widths depending on .ini font settings

#ifndef EXCLUDE_FROM_XARALX
			InitRegistry() &&					// register us with the shell etc
			InitAppState()	&&					// get workspace prefs
#endif
			SelMediaDlg::Init() &&
			TRUE
			);
}


