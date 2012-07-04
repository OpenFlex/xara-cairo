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


// Filters that are a bit on the OILy side e.g. Metafile, Aldus

#ifndef INC_METAFILT
#define	INC_METAFILT

//#include "oilfltrs.h" - in camtypes.h [AUTOMATICALLY REMOVED]
#include "clipmap.h"
//#include "doccolor.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class WinBitmap;
class NodeBitmap;
class MetafileView;



// This is to get access to the 16 bit windows types
typedef short INT16;

#ifdef _MSC_VER
	// Make sure structures correspond to Win16 equivalents.
	// (pack to 1 byte boundaries)
	#pragma pack(push, 1)

	typedef struct
	{
		INT16     lfHeight;
		INT16     lfWidth;
		INT16     lfEscapement;
		INT16     lfOrientation;
		INT16     lfWeight;
		BYTE      lfItalic;
		BYTE      lfUnderline;
		BYTE      lfStrikeOut;
		BYTE      lfCharSet;
		BYTE      lfOutPrecision;
		BYTE      lfClipPrecision;
		BYTE      lfQuality;
		BYTE      lfPitchAndFamily;
		CHAR      lfFaceName[LF_FACESIZE];
	} LOGFONT_16;

	#pragma pack(pop)
#else
	#error Don't know how to pack structures with this compiler!
#endif // _MSC_VER

/********************************************************************************************

>	class MetaFileClipMap : public ClipboardMapping

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/4/95
	
	Purpose:	A class which describes and implements an available mapping between internal
				and external data formats.

				This class implements clipboard import/export functionality for Windows
				MetaFiles, using the MetaFile Filter.

	SeeAlso:	ExternalClipboard; Filter; MetaFileFilter

*********************************************************************************************/

class MetaFileClipMap : public ClipboardMapping
{
CC_DECLARE_DYNCREATE(MetaFileClipMap)

friend class ExternalClipboard;
friend class OpClipboardExport;
friend class OpClipboardImport;

protected:
	MetaFileClipMap() {}
	MetaFileClipMap(ClipboardMappingType TheType, Filter *TheFilter,
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





// Forward reference for MetaFileFilter (see oilfltrs.cpp for declaration).
class HandleTable;
class CCLexFile;

/********************************************************************************************

< METAHEADER

	Comment:	This structure is used when loading a MetaFile.

				MonoOn
				typedef struct 
				{
					BOOL Placeable;
					METAFILEHEADER Header;
				} METADATA;
				MonoOff

	SeeAlso:	MetaFileFilter; MetaFileFilter::GetMetaFileHandle

********************************************************************************************/ 

typedef struct 
{
	BOOL Placeable;
	METAFILEHEADER Header;
} METADATA;


/********************************************************************************************

>	class MetaFileFilter : public VectorFilter

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	08/03/94
	Purpose:	Encapsulates a filter for importing Windows MetaFiles (16-bit only at the
				moment)
	SeeAlso:	Filter

********************************************************************************************/

class MetaFileFilter : public VectorFilter
{
friend class MetaFileClipMap;		// Allow access to GetMetaFileHandle()

	CC_DECLARE_MEMDUMP(MetaFileFilter);
	
public:
	MetaFileFilter();
	~MetaFileFilter();

	BOOL Init();	

	// Works out if opening a file of this type requires a default document to be loaded
	// or does the file format supply the document.
	virtual BOOL IsDefaultDocRequired(const TCHAR* pcszPathName);

	INT32 HowCompatible( PathName& Filename, ADDR HeaderStart, UINT32 HeaderSize,
					   UINT32 FileSize );

	BOOL DoImport(SelOperation *Op, CCLexFile*, Document *DestDoc, 
				  BOOL AutoChosen, ImportPosition *Pos = NULL,
				  KernelBitmap** ppImportedBitmap = NULL,
				  DocCoord* pPosTranslate = NULL, String_256* URL=NULL);
	
	// Exporting functions
	BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);
	BOOL DoExport(Operation*, CCLexFile* pFile, Document* pDoc, METAFILEPICT* pMetaInfo);

	// Set the font ready for use
	void SetLogicalFont(LOGFONT_16* pNewFont);

protected:
	BOOL PrepareToImport();
	void CleanUpAfterImport();
		
	// The file we are reading, and the DC for it.
	HMETAFILE 	MetaFile;
	HDC			MetaFileDC;

	BOOL MetaFileHeaderIsOk(METAHEADER *pHeader);

	// this is virtual so that inherited classes can override it
	virtual BOOL OpenAndIterateMetafile( CCLexFile *pDiskFile );

	// Given a metafile filename, return a metafile handle to it.
	HMETAFILE GetMetaFileHandle(LPSTR Filename, METADATA *);

	INT32 DecodeMetafileRecord( METARECORD *pMetaRec );
	// This must be static as it needs to be registered as a Windows callback.
	static INT32 CALLBACK DecodeMetaFile(HDC hdc, HANDLETABLE FAR* pHandleTable, 
		        			  		   METARECORD FAR* pMetaRec, INT32 cObj, LPARAM lParam);


	// Functions for decoding MetaFile records.
	BOOL DecodePolygon(METARECORD* pRec, BOOL FillPolygon);
	BOOL DecodePolyPolygon(METARECORD *);
	BOOL DecodeLineTo(METARECORD* pMetaRec);
	BOOL DecodeRectangle(METARECORD* pMetaRec);
	BOOL DecodeEllipse(METARECORD* pMetaRec);
	BOOL DecodeTextStory(METARECORD* pMetaRec);
	BOOL DecodeExtTextStory(METARECORD* pMetaRec);
	
	// All the bitmap decoding functions
	BOOL DecodeStretchDIB(METARECORD*);
	BOOL DecodeDIBStretchBlt(METARECORD* pMetaRec);
	BOOL DecodeBitBlt(METARECORD* pMetaRec);
	BOOL DecodeStretchBlt(METARECORD* pMetaRec);
	BOOL DecodeDIBToDevice(METARECORD* pMetaRec);
	BOOL DecodeDIBBitBlt(METARECORD* pMetaRec);

	// common code for the bitmap decoding
	KernelBitmap* CreateBitmap(BITMAPINFO* pBitmapStart);
	NodeBitmap* BuildNodeBitmap(KernelBitmap* pBitmap, const DocRect& Position);

	// The Selected Font
	LOGFONT SelectedFont;

	// TransformCoord() - converts a metafile coord to a DocCoord, taking into account the origin.
	void TransformCoord(DocCoord* C);

	// ScaleCoord() - converts a metafile coord to a DocCoord.
	void ScaleCoord(DocCoord* C);

	// Scale factors for coordinates
	INT32 CurrentMappingMode;
	DocCoord MetaFileOrigin;
	BOOL FlipYCoords;
	BOOL IsYExtentNegative;
	INT32 YShift;

	// The layer that objects are placed on
	Layer *pLayer;
	
	// The Node to which new objects are attached (may be a Layer or a Group node)
	Node *pNode;
	
	struct CImportInfo
	{
		// The operation that caused the import
		SelOperation *pOp;

		// Where the file was dropped for drag'n'drop, or NULL if drag'n'drop was not used.
		ImportPosition Pos;
	};

	CImportInfo ImportInfo;

	// Attribute stuff
	BOOL AddAttributes(Node* pNewNode);
	DocColour TextColour;

	// Array of GDI object handles
	HandleTable *Handles;

	// Allow HandleTable objects to set our LineColour/FillColour variables.
	friend HandleTable;

	// For progress cursor
	INT32 FileSize;
	INT32 BytesRead, 
		 LastProgressUpdate;

	// TRUE if we're loading a placeable metafile.
	BOOL Placeable;

	// How many units to the inch for a placeable metafile
	MILLIPOINT ScaleFactor;
	INT32 Dpi;

	// Remembers the current point for operations such as moveto, lineto etc.
	DocCoord CurrentPoint;

	// Need to know if we found anything in this file that we did not understand
	BOOL AllUnderstood;

	//
	// Export related functions
	//
	virtual BOOL PrepareToExport(CCLexFile*, Spread *pSpread);
	virtual void CleanUpAfterExport();
	virtual BOOL WriteToFile(HMETAFILE, METAFILEHEADER*);

	CCLexFile* OutputFile;					// where the metafile is going to (was CCLexFile*)
	CDC ReferenceDC;						// reference DC for the metafile
	CMetaFileDC MetafileDC;					// the CDC that actually gets rendered to
	RenderRegion *ExportRegion;				// where rendering goes
	DocRect ExportClipRect;					// The Clip rect of the export region
	MetafileView* pMetaView;				// The metafile view to help with the rendering

private:
	Node *pLastInsertedNode;				// where we put the last node in the tree so we can
											// insert new nodes as NEXT using this pointer

	inline void AddNodeToMetaFileGroup(NodeRenderableBounded *pNode);
											// Add a node into the group we are importing the
											// metafile into

	HFILE InFile;
};

/********************************************************************************************

>	class AldusFormatFilter : public MetaFileFilter

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/3/95
	Purpose:	Base class for various Aldus-format filters.
	SeeAlso:	MetaFileFilter

********************************************************************************************/
/*
class AldusFormatFilter : public MetaFileFilter
{
	CC_DECLARE_MEMDUMP(AldusFormatFilter);
	
public:
	static BOOL InitAll(List&);

	AldusFormatFilter();
	~AldusFormatFilter();
	BOOL Init(LPTCHAR, LPTCHAR, LPTCHAR);
	BOOL Init();

	INT32 HowCompatible( PathName& Filename, ADDR HeaderStart, UINT32 HeaderSize,
					   UINT32 FileSize );

protected:

	BOOL OpenAndIterateMetafile( CCLexFile *pDiskFile );

	void UnloadDLL();

	LPTCHAR DLLPath;								// complete path to filter DLL
	HMODULE DLLHandle;								// handle of above DLL, NULL=not loaded
	HANDLE DLLPrefHandle;							// for filters preference info

	static UINT32 AutomaticID;						// dynamic filter ID
	static BOOL DeclareFilter( List&, LPTCHAR , LPTCHAR , LPTCHAR );

};
*/
#endif
