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


// An input filter for importing RISC OS Draw format files.

#ifndef INC_DRAWFLTR
#define INC_DRAWFLTR

//#include "ccfile.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "filters.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class Node;

/********************************************************************************************

>	class DrawFileHeader

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/93
	Purpose:	Holds the information contained in the header of an Acorn Draw file.
	SeeAlso:	DrawObjectHeader; AcornDrawFilter

********************************************************************************************/

class DrawFileHeader
{
public:
	// Should be the string "Draw"
	char 		Ident[4];

	// version number and name of program that created the Draw file
	UINT32		MajorVersion;
	UINT32		MinorVersion;
	char		Creator[12];

	// Bounding box of the whole draw file
	DocCoord	BBoxLo;
	DocCoord	BBoxHi;
};

/********************************************************************************************

	typedef DrawObjectType

	This is a simple type to decode the object types in an Acorn Draw file.

********************************************************************************************/

typedef INT32 DrawObjectType;


/********************************************************************************************

>	class DrawObjectHeader

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/11/93
	Purpose:	Contains the information contained in an object header of an Acorn Draw file.
	SeeAlso:	DrawFileHeader; AcornDrawFilter

********************************************************************************************/

class DrawObjectHeader
{
public:
	// Type and size of object
	DrawObjectType 	Type;
	UINT32			Size;

	// Bounding box of this object
	DocCoord		BBoxLo;
	DocCoord		BBoxHi;
};



// Various forward declarations for the AcornDrawFilter class
class PathName;
class Document;
class NodePath;
class Layer;
class AttrLineWidth;
class AttrStrokeColour;
class AttrFillColour;
class OpImportAcornDraw;
class Page;
class DrawPathHeader;

/********************************************************************************************

>	class AcornDrawFilter : public VectorFilter

	Author:		Tim_Browse (Xara Group Ltd) <camelotdev@xara.com>
	Created:	13/10/93
	Purpose:	Encapsulates an RISC OS Draw input filter system.

********************************************************************************************/

class AcornDrawFilter : public VectorFilter
{
	CC_DECLARE_DYNAMIC(AcornDrawFilter);
	
public:
	AcornDrawFilter();
	~AcornDrawFilter();
	BOOL Init();	

	// Works out if opening a file of this type requires a default document to be loaded
	// or does the file format supply the document.
	virtual BOOL IsDefaultDocRequired(const TCHAR* pcszPathName);

	INT32 HowCompatible(PathName& Filename, ADDR HeaderStart, UINT32 HeaderSize, UINT32 FileSize);

	BOOL DoImport(SelOperation *Op, CCLexFile*, Document *DestDoc, 
				  BOOL AutoChosen, ImportPosition *Pos = NULL,
				  KernelBitmap** ppImportedBitmap = NULL,
				  DocCoord* pPosTranslate = NULL, String_256* = NULL);

	BOOL DoExport(Operation*, CCLexFile*, PathName*, Document*, BOOL);

private:
	BOOL PrepareToImport();
	void CleanUpAfterImport();
		
	// The file we are reading
	CCLexFile *DrawFile;
	
	// TRUE if the EOF has been reached
	BOOL eof;
	
	// The layer that objects are placed on
	Layer *pLayer;
	
	// The page that objects appear on
	Page *pPage;
	
	// The Node to which new objects are attached (may be a Layer or a Group node)
	Node *pNode;
	
	// TRUE if a complex path is being constructed
	BOOL ComplexPath;
	
	// TRUE if the path being constructed has not had any attributes added yet
	BOOL NoAttributes;

	// Co-ordinate transformations
	DocCoord Origin;

	// TransformCoord() - converts a DocCoord from Draw units (1/640 of a point) to
	// Camelot units (millipoints). (the factor 1000/640 is reduced to 25/16)
	void TransformCoord(DocCoord& C) 
		{	C.x *= 25; C.x /= 16; C.x += Origin.x;
			C.y *= 25; C.y /= 16; C.y += Origin.y; };

	// Buffers to hold data read from the Draw file.
	DrawFileHeader	 FileHeader;
	DrawObjectHeader ObjectHeader;
	ADDR DataBuf; // Dynamically allocated when the file is read.
	UINT32 DataBufSize;
	UINT32 HeaderSize; // Not necessarily sizeof(DrawObjectHeader)! (Thanks, Acorn...)
	UINT32 DataSize;

	// Functions to read in and process the Draw objects
	BOOL ReadFileHeader();
	BOOL ReadObjectHeader();
	BOOL ReadObjectData();
	BOOL ProcessObject();
	BOOL ProcessPath();
	BOOL ProcessGroup();
	BOOL ProcessTaggedObject();
	BOOL SkipObject();
	BOOL AddAttributes(NodePath *pPath, DrawPathHeader *pHeader);

	// Used to update progress bar etc
	INT32 BytesRead;
	INT32 LastProgressUpdate;
};


#endif
