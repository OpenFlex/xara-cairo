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
// Declaration of ExportHint class

#ifndef INC_EXPHINT
#define INC_EXPHINT


enum ExportHintBitmapType
{
	HINTTYPE_BAD = 0,
	HINTTYPE_JPEG,
	HINTTYPE_GIF,
	HINTTYPE_PNG,
	HINTTYPE_MAX
};

/********************************************************************************************

>	class ExportHint : public CC_CLASS_MEMDUMP

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/97
	Purpose:	Encapsulates the Export Hint for a document

********************************************************************************************/

class ExportHint : public CC_CLASS_MEMDUMP
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(ExportHint);

public:
	// Construction and initialisation
	ExportHint();
	ExportHint(const ExportHint& other);
	~ExportHint() {};

public:
	// Public access functions
	UINT32 GetType(void) { return(m_Type); };
	UINT32 GetWidth(void) { return(m_Width); };
	UINT32 GetHeight(void) { return(m_Height); };
	UINT32 GetBPP(void) { return(m_BPP); };
	const String_256& GetOptionsString(void) { return(m_sOptions); };

	void SetType(UINT32 Type) { m_Type = Type; };
	void SetWidth(UINT32 Width) { m_Width = Width; };
	void SetHeight(UINT32 Height) { m_Height = Height; };
	void SetBPP(UINT32 BPP) { m_BPP = BPP; };
	void SetOptionsString(const String_256& sOpt) { m_sOptions = sOpt; };

public:
	// Other public functions
	const ExportHint& operator=(const ExportHint& other);

public:
	// Functions solely for the use of the filters...
	BOOL WriteExportHintRecord(BaseCamelotFilter* pFilter);
	BOOL InitFromRecord(CXaraFileRecord* pRecord);

protected:
	UINT32 m_Type;
	UINT32 m_Width;
	UINT32 m_Height;
	UINT32 m_BPP;
	String_256 m_sOptions;
};

/********************************************************************************************

>	class ExportHintRecordHandler : public CamelotRecordHandler

	Author:		Gerry_Iles (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/07/96

	Purpose:	Handles TAG_EXPORT_HINT

********************************************************************************************/

class ExportHintRecordHandler : public CamelotRecordHandler
{
	// Support full runtime classing
	CC_DECLARE_DYNAMIC(ExportHintRecordHandler);

public:
	ExportHintRecordHandler() {};
	virtual ~ExportHintRecordHandler() {};

	// functions that must be implemented.
	virtual UINT32*	GetTagList();
	virtual BOOL	HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
	virtual void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord,StringBase* Str);
	virtual void GetTagText(UINT32 Tag,String_256& Str);
#endif
};

#endif  // INC_EXPHINT
