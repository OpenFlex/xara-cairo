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

// svgexportdialog.h: This defines the XAR --> SVG export dialogbox

#ifndef SVGEXPORTDIALOG_H
#define SVGEXPORTDIALOG_H

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10000
#define SYMBOL_SVGEXPORTDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxDIALOG_MODAL
#define SYMBOL_SVGEXPORTDIALOG_TITLE _("SVG Export Settings")
#define SYMBOL_SVGEXPORTDIALOG_IDNAME ID_DIALOG
#define SYMBOL_SVGEXPORTDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_SVGEXPORTDIALOG_POSITION wxDefaultPosition
#define ID_SPECIFICATION_COMBOBOX 10001
#define ID_CHECKBOX 10002
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/***************************************************************************************************

>	class SVGExportDialog

	Author:		Sandro Sigala <sandro@sigala.it>
	Created:	20 June 2006
	Purpose:	Export (SVG --> XAR) dialogbox with the common user settings.

***************************************************************************************************/

class SVGExportDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS(SVGExportDialog)
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    SVGExportDialog();
    SVGExportDialog(wxWindow* parent, wxWindowID id = SYMBOL_SVGEXPORTDIALOG_IDNAME, const wxString& caption = SYMBOL_SVGEXPORTDIALOG_TITLE, const wxPoint& pos = SYMBOL_SVGEXPORTDIALOG_POSITION, const wxSize& size = SYMBOL_SVGEXPORTDIALOG_SIZE, long style = SYMBOL_SVGEXPORTDIALOG_STYLE);

    /// Creation
    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_SVGEXPORTDIALOG_IDNAME, const wxString& caption = SYMBOL_SVGEXPORTDIALOG_TITLE, const wxPoint& pos = SYMBOL_SVGEXPORTDIALOG_POSITION, const wxSize& size = SYMBOL_SVGEXPORTDIALOG_SIZE, long style = SYMBOL_SVGEXPORTDIALOG_STYLE);

    /// Creates the controls and sizers
    void CreateControls();

////@begin SVGExportDialog event handler declarations

////@end SVGExportDialog event handler declarations

////@begin SVGExportDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end SVGExportDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin SVGExportDialog member variables
    wxComboBox* m_SVGVersionComboBox;
    wxCheckBox* m_VerboseCheckBox;
////@end SVGExportDialog member variables
};

#endif // !SVGEXPORTDIALOG_H
