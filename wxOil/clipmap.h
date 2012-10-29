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

// ClipboardMapping - External clipboard class for encapsulating clipboard data mappings


#ifndef INC_CLIPMAP
#define INC_CLIPMAP

#include "cliptype.h"
#include "cmxfiltr.h"

class InternalClipboard;
class ExternalClipboard;
class OpClipboardExport;
class OpClipboardImport;
class Operation;
class SelOperation;
class Filter;


typedef enum
{
	CLIPMAP_IMPORTONLY	 = 1,
	CLIPMAP_EXPORTONLY	 = 2,
	CLIPMAP_IMPORTEXPORT = 3
} ClipboardMappingType;



/********************************************************************************************

>	class ClipboardMapping : public ListItem

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/4/95
	
	Purpose:	A class which describes and implements an available mapping between internal
				and external data formats. Each filter which can provide a useful clipboard
				export/import format will register with the ExternalClipboard instance,
				using an ClipboardMapping object to describe the available mapping, and
				to provide functions which will invoke that filter on windows clipboard data.

				The ClipboardMapping knows whether it represents an Import or Export mapping,
				and knows what data types are required for the source destination, and 
				holds a pointer to the filter which can supply such a mapping. Two methods
				(HandleImport, HandleExport) are used to invoke the mapping.

				Filters can register several different mappings with the ExtClipboard - 
				typically a filter will register one import and one export mapping.

				A 'Priority' factor is used to determine the most compatible/preferable routes
				for converting data. The factors are integers. A higher number indicates a
				higher priority.
				
	Notes:		There is a document describing all of the available conversions in Camelot.
				It describes the conversions and lists their priorities. Check with this
				doc to determine what priority your conversion should be. Add entries to
				this doc describing all mappings your filter(s) will register.

	SeeAlso:	ExternalClipboard; Filter

*********************************************************************************************/

class CCAPI ClipboardMapping : public ListItem
{
CC_DECLARE_DYNCREATE(ClipboardMapping)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

/////////////////////////////////////////////////////////////////////////////////////////////
//
//	The OLE clipboard
//

#if (_OLE_VER >= 0x200)

public:

	// Call this to set the memory the clipboard should delay-render into.  If hMem is
	// null then the render functions will try to allocate the memory themselves.
	void SetRenderMemory(HGLOBAL hMem, DWORD cbMemSize);

protected:

	// Implementation.
	HGLOBAL		m_hMem;				// the memory to delay-render into
	DWORD		m_cbMemSize;		// the size of the supplied memory
	Document*	m_pDoc;				// the kernel Document to import/export

public:

	// Call this before importing or exporting to set the document to use for import/export
	void SetDocument(Document* pDoc)			{ m_pDoc = pDoc; }

#endif

/////////////////////////////////////////////////////////////////////////////////////////////


public:
	virtual ~ClipboardMapping();

protected:
	ClipboardMapping();
	ClipboardMapping(ClipboardMappingType TheType, Filter *TheFilter,
						InternalClipboardFormat &InternalDataType, UINT32 ExternalDataType,
						UINT32 Priority);

public:			// Public method for constructing a mapping object
	static void CreateAndRegister(ClipboardMappingType TheType, Filter *TheFilter,
						InternalClipboardFormat &InternalDataType, UINT32 ExternalDataType,
						UINT32 Priority);

public:			// public interface
	InternalClipboardFormat *GetInternalDataType(void) { return(&InternalDataType); }


protected:		// Entry points for external clipboard manager
	virtual BOOL HandleImport(SelOperation *Caller, HANDLE ClipboardData, InternalClipboard *Dest);
			// Works out how to call the parent filter to import the given clipboard data
		
	virtual HANDLE HandleExport(Operation *Caller, InternalClipboard *Source);
			// Works out how to call the parent filter to export the given clipboard document

protected:
	BOOL ImportFromTempFile(TCHAR *filename, SelOperation *Caller, InternalClipboard *Dest);
			// Internal helper method to invoke pFilter->DoImport on the given scratch file

	BOOL ExportToTempFile(TCHAR *filename, Operation *Caller, InternalClipboard *Source);
			// Internal handler method to invoke pFilter->DoExport to the given scratch file


protected:	// Bodge to allow use of tempfiles
	char *tempfilename;
	char *GetTempFileName(void);
			// Returns a filename to use for a temporary file. You should only call this once
			// before RemoveTempFile is called

	void RemoveTempFile(void);
			// Removes the last tempfile got with GetTempFileName


protected:
	ClipboardMappingType Type;			// 1=import, 2=export, 3=both import and export
	Filter *pFilter;					// Points to the filter which converts

	InternalClipboardFormat InternalDataType;
										// Identifies the internal data type

	UINT32 ExternalDataType;				// Identifies the external (windows) type that we'll react to
	UINT32 RealExternalType;				// Identifies the external (windows) type that we really import/export
										// NOTE: In the base class, ExternalDataType == RealExternalType!
	UINT32 Priority;						// Higher priority mappings are used in preference

protected:
	BOOL Available;		// Used when scanning to determine the available export formats
};






/********************************************************************************************

>	class BodgeTextClipMap : public ClipboardMapping

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/4/95
	
	Purpose:	Describes and handles import/export mappings for UNICODE text.

				This provides bodge import/export of ASCII text
				A proper text filter will be written one day which will replace this bodge

	Notes:		This mapping is used twice - once for CF_TEXT, and once as an alias for
				CF_OEMTEXT (which the clipboard will convert to CF_TEXT when we ask for it)

	SeeAlso:	ClipboardMapping; ExternalClipboard; Filter

*********************************************************************************************/

class CCAPI BodgeTextClipMap : public ClipboardMapping
{
CC_DECLARE_DYNCREATE(BodgeTextClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

protected:
	BodgeTextClipMap();
	BodgeTextClipMap(ClipboardMappingType TheType, UINT32 ClaimType = 0);

public:			// Public method for constructing a mapping object
	static void CreateAndRegister(ClipboardMappingType TheType, UINT32 ClaimType = 0);
				// NOTE that we can register this for CF_TEXT, SF_UNICODETEXT, and CF_OEMTEXT, and it
				// will respond to any of these by asking for UNICODE text from the clipboard, which
				// will automatically do the conversion for us if necessary. 3 formats for the price of 1.

protected:		// Entry points for external clipboard manager
	virtual BOOL HandleImport(SelOperation *Caller, HANDLE ClipboardData, InternalClipboard *Dest);
			// Works out how to call the parent filter to import the given clipboard data
		
	virtual HANDLE HandleExport(Operation *Caller, InternalClipboard *Source);
			// Works out how to call the parent filter to export the given clipboard document
};






/********************************************************************************************

>	class BodgeUnicodeClipMap : public ClipboardMapping

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	24/4/95
	
	Purpose:	Describes and handles import/export mappings for UNICODE text.

				This provides bodge import/export of unicode text
				A proper text filter will be written one day which will replace this bodge

	SeeAlso:	ClipboardMapping; ExternalClipboard; Filter

*********************************************************************************************/

class CCAPI BodgeUnicodeClipMap : public ClipboardMapping
{
CC_DECLARE_DYNCREATE(BodgeUnicodeClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

protected:
	BodgeUnicodeClipMap();
	BodgeUnicodeClipMap(ClipboardMappingType TheType, UINT32 ClaimType = 0);

public:			// Public method for constructing a mapping object
	static void CreateAndRegister(ClipboardMappingType TheType, UINT32 ClaimType = 0);
				// NOTE that we can register this for CF_TEXT, SF_UNICODETEXT, and CF_OEMTEXT, and it
				// will respond to any of these by asking for UNICODE text from the clipboard, which
				// will automatically do the conversion for us if necessary. 3 formats for the price of 1.

protected:		// Entry points for external clipboard manager
	virtual BOOL HandleImport(SelOperation *Caller, HANDLE ClipboardData, InternalClipboard *Dest);
			// Works out how to call the parent filter to import the given clipboard data
		
	virtual HANDLE HandleExport(Operation *Caller, InternalClipboard *Source);
			// Works out how to call the parent filter to export the given clipboard document
};





/********************************************************************************************

>	class BitmapClipMap : public ClipboardMapping

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/4/95
	
	Purpose:	Describes and handles import/export mappings for bitmaps.

				This mapping does not attach to a filter - it simply scans the tree for
				bitmap objects, and exports the DIB data, or imports DIB data and creates
				a new bitmap object in the document. (i.e. the data is not converted, just
				inserted/extracted from the document tree)

	Notes:		Due to the unbelieveable crapness of windows, it seems to be impossible to
				export a bitmap with a decent palette. So we do like Corel and don't export
				in bitmap format - DIBs are the way of the future anyway.

	SeeAlso:	ClipboardMapping; ExternalClipboard; Filter

*********************************************************************************************/

class CCAPI BitmapClipMap : public ClipboardMapping
{
CC_DECLARE_DYNCREATE(BitmapClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

protected:
	BitmapClipMap();
	BitmapClipMap(ClipboardMappingType TheType, UINT32 ClaimType);

public:			// Public method for constructing a mapping object
	static void CreateAndRegister(ClipboardMappingType TheType, UINT32 ClaimType = 0);

protected:		// Entry points for external clipboard manager
	virtual BOOL HandleImport(SelOperation *Caller, HANDLE ClipboardData, InternalClipboard *Dest);
			// Works out how to call the parent filter to import the given clipboard data
		
	virtual HANDLE HandleExport(Operation *Caller, InternalClipboard *Source);
			// Works out how to call the parent filter to export the given clipboard document
};




#if FALSE
/********************************************************************************************

//>	class PaletteClipMap : public ClipboardMapping

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	3/5/95
	
	Purpose:	Describes and handles an export-only mapping for Palettes.

				This mapping does not attach to a filter - it simply scans the tree for
				bitmap objects, and exports the DIB Palette data. This is used in
				conjunction with the Bitmap exporter to provide a palette for the bmp.

	SeeAlso:	ClipboardMapping; ExternalClipboard; Filter

*********************************************************************************************/

class CCAPI PaletteClipMap : public ClipboardMapping
{
CC_DECLARE_DYNCREATE(PaletteClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

protected:
	PaletteClipMap();

public:			// Public method for constructing a mapping object
	static void CreateAndRegister(void);

protected:		// Entry points for external clipboard manager
	virtual HANDLE HandleExport(Operation *Caller, InternalClipboard *Source);
			// Works out how to call the parent filter to export the given clipboard document
};
#endif





/********************************************************************************************

>	class DIBClipMap : public ClipboardMapping

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	29/4/95
	
	Purpose:	Describes and handles import/export mappings for bitmaps.

				This mapping does not attach to a filter - it simply scans the tree for
				bitmap objects, and exports the DIB data, or imports DIB data and creates
				a new bitmap object in the document. (i.e. the data is not converted, just
				inserted/extracted from the document tree)

	SeeAlso:	ClipboardMapping; ExternalClipboard; Filter

*********************************************************************************************/

class CCAPI DIBClipMap : public ClipboardMapping
{
CC_DECLARE_DYNCREATE(DIBClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

protected:
	DIBClipMap();
	DIBClipMap(ClipboardMappingType TheType, UINT32 ClaimType);

public:			// Public method for constructing a mapping object
	static void CreateAndRegister(ClipboardMappingType TheType, UINT32 ClaimType = 0);

protected:		// Entry points for external clipboard manager
	virtual BOOL HandleImport(SelOperation *Caller, HANDLE ClipboardData, InternalClipboard *Dest);
			// Works out how to call the parent filter to import the given clipboard data
		
	virtual HANDLE HandleExport(Operation *Caller, InternalClipboard *Source);
			// Works out how to call the parent filter to export the given clipboard document
};




/********************************************************************************************

//>	class QuarkPictureClipMap : public ClipboardMapping

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	4/5/95
	
	Purpose:	Describes and handles import mapping for some "QuarkXPress Picture Data"

	SeeAlso:	ClipboardMapping; ExternalClipboard; Filter

*********************************************************************************************/

#if FALSE
class CCAPI QuarkPictureClipMap : public ClipboardMapping
{
CC_DECLARE_DYNCREATE(QuarkPictureClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

protected:
	QuarkPictureClipMap();
	QuarkPictureClipMap(UINT32 MyFormat);

public:			// Public method for constructing a mapping object
	static void CreateAndRegister(void);

protected:		// Entry points for external clipboard manager
	virtual BOOL HandleImport(SelOperation *Caller, HANDLE ClipboardData, InternalClipboard *Dest);
			// Works out how to call the parent filter to import the given clipboard data
};
#endif



#ifdef _DEBUG
/********************************************************************************************
>	class RTFClipMap : public ClipboardMapping

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/12/95
	Purpose:	A class which describes and implements an available mapping between internal
				and external data formats.
				This class implements clipboard import/export functionality for Rich Text
				Format files, using the RTFTextFilter.
	SeeAlso:	ExternalClipboard; Filter; RTFTextFilter
*********************************************************************************************/
class RTFClipMap : public ClipboardMapping
{
	CC_DECLARE_DYNCREATE(RTFClipMap)

	friend class ExternalClipboard;
	friend class OpClipboardExport;
	friend class OpClipboardImport;

protected:
	RTFClipMap() {}
	RTFClipMap(ClipboardMappingType TheType, Filter *TheFilter,
							InternalClipboardFormat &InternalDataType, UINT32 ExternalDataType,
							UINT32 Priority);

public:			// Public method for constructing a mapping object
	static void CreateAndRegister(ClipboardMappingType TheType, Filter *TheFilter,
							InternalClipboardFormat &InternalDataType, UINT32 ExternalDataType,
							UINT32 Priority);


protected:		// Entry points for external clipboard manager
	virtual BOOL HandleImport(SelOperation *Caller, HANDLE ClipboardData, InternalClipboard *Dest);
			// Works out how to call the parent filter to import the given clipboard data
		
	virtual HANDLE HandleExport(Operation *Caller, InternalClipboard *Source);
			// Works out how to call the parent filter to export the given clipboard document
};
#endif	//debug

/********************************************************************************************

>	class CMXClipMap : public ClipboardMapping

	Author:		Ben_Summers (Xara Group Ltd) <camelotdev@xara.com>
	Created:	04/09/96
	
	Purpose:	Describes and handles import/export mappings for CMX files.

	Notes:		This is the base class for 16 and 32 bit varients of CMX files

	SeeAlso:	ClipboardMapping; ExternalClipboard; Filter

*********************************************************************************************/

class CCAPI CMXClipMap : public ClipboardMapping
{
CC_DECLARE_DYNAMIC(CMXClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

protected:
	CMXClipMap() {};
	CMXClipMap(ClipboardMappingType TheType, UINT32 ClaimType, UINT32 nPriority);

public:			// Public method for constructing a mapping object
//	static void CreateAndRegister(ClipboardMappingType TheType, UINT32 ClaimType = 0);
				// NOTE that we can register this for CF_TEXT, SF_UNICODETEXT, and CF_OEMTEXT, and it
				// will respond to any of these by asking for UNICODE text from the clipboard, which
				// will automatically do the conversion for us if necessary. 3 formats for the price of 1.

protected:		// Entry points for external clipboard manager
	virtual BOOL HandleImport(SelOperation *Caller, HANDLE ClipboardData, InternalClipboard *Dest);
			// Works out how to call the parent filter to import the given clipboard data
		
	virtual HANDLE HandleExport(Operation *Caller, InternalClipboard *Source);
			// Works out how to call the parent filter to export the given clipboard document

	// for the various varients
	virtual CMXFilter *CreateExportFilter(void) = 0;
};

class CCAPI CMX16ClipMap : public CMXClipMap
{
CC_DECLARE_DYNCREATE(CMX16ClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

public:
	CMX16ClipMap();
	CMX16ClipMap(ClipboardMappingType TheType, UINT32 ClaimType, UINT32 nPriority)
		: CMXClipMap(TheType, ClaimType, nPriority) {};

static void CreateAndRegister(ClipboardMappingType TheType, UINT32 ClaimType = 0);

protected:
	CMXFilter *CreateExportFilter(void) {return new CMXFilter16;};
};

class CCAPI CMX32ClipMap : public CMXClipMap
{
CC_DECLARE_DYNCREATE(CMX32ClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

public:
	CMX32ClipMap();
	CMX32ClipMap(ClipboardMappingType TheType, UINT32 ClaimType, UINT32 nPriority)
		: CMXClipMap(TheType, ClaimType, nPriority) {};

static void CreateAndRegister(ClipboardMappingType TheType, UINT32 ClaimType = 0);

protected:
	CMXFilter *CreateExportFilter(void) {return new CMXFilter32;};
};



#endif	//include clipmap.h
