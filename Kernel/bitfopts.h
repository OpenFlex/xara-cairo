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

//

#ifndef INC_BITFOPTS
#define INC_BITFOPTS

/********************************************************************************************

  >	class BitmapImportOptions : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/06/96
	Purpose:   	Base class for storing import options
	Scope:		public

********************************************************************************************/
class BitmapImportOptions : public CC_CLASS_MEMDUMP		// public ImportOptions
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(BitmapImportOptions);
public:
	BitmapImportOptions();

	SelOperation*	m_pSelectionOp;		// Operation used to do import
	BOOL			m_bAutoChosen;		// er?...
	ImportPosition*	m_pImportPosition;	// Where to stick it

	CCLexFile*		m_pFile;			// File to be used for import
	Document*		m_pDestinationDoc;	// Docuement in which to place bitmap

	UINT32			m_uBitmapToImport;	// The number of the bitmap to import

	BOOL			m_bCancelled;		// user cancelled

	BOOL	m_bProvideProgress;	// should BaseBitmapFilter class provide the progress bar?
								// Of course it should (or filter should), but provides backwards
								// compatability with derived classes who provide their own.

	BOOL	m_bValid;			// TRUE if constructed OK
};




/********************************************************************************************

  >	class BitmapImportResults : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/06/96
	Purpose:   	Provides the results for the import
	Notes:		m_bValid should be checked for TRUE after any construction because the
				constructor can fail
	Scope:		public

********************************************************************************************/
class BitmapImportResults : public CC_CLASS_MEMDUMP		// ...public ImportResults
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(BitmapImportResults);
public:
	BitmapImportResults();		// CAN FAIL!!
	virtual ~BitmapImportResults();

	BitmapSequence*		m_pImportedBitmaps;
	INT32					m_nNextAvailableBitmap;	// the next bitmap that can be read

	BOOL	m_bValid;			// TRUE if constructed OK
};



/********************************************************************************************

  >	class GIFImportOptions : public CC_CLASS_MEMDUMP

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/06/96
	Purpose:   	Import options for the GIF filter. Allows a clean method of passing
				assorted parameters for the GIF filter. Specifically, that the
				BaseBitmapFilter should give us a progress bar.
	Scope:		public
	See Also:	BitmapImportOptions

********************************************************************************************/
class GIFImportOptions : public BitmapImportOptions
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(GIFImportOptions);
public:
	GIFImportOptions() : BitmapImportOptions() {m_bProvideProgress = TRUE;}

	// 
};


/********************************************************************************************

  >	class GIFImportResults : public BitmapImportResults

	Author:		Colin_Barfoot (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/06/96
	Purpose:   	Provides the results for the import of a GIF
	Notes:		m_bValid should be checked for TRUE after any construction because the
				constructor can fail
	Scope:		public

********************************************************************************************/
class GIFImportResults : public BitmapImportResults
{
	// Declare the class for memory tracking
	CC_DECLARE_MEMDUMP(GIFImportResults);
public:
	GIFImportResults();

	OILBitmap*			m_pBitmap;
	Filter*				m_pFilter;					// used for progress

	INT32					m_nTransparentColourIndex;	// index of the GIF's transparent colour
													// -1 if none
	UINT32				m_uRepeats;					// for those animated doo-dahs

	enum DISPOSAL_METHOD
	{
		NONE,
		DONT,
		TOBACKGROUND,
		TOPREVIOUS,
	};
	DISPOSAL_METHOD		m_DisposalMethod;			// animation idea

};


#endif	// INC_BITFOPTS
