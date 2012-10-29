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

#ifndef INC_HTMLEXPORTFILTERS
#define INC_HTMLEXPORTFILTERS


class CCLexFile;

const UINT32 HTMLEXPORT_DEFAULTWORDWRAP = 100;

/**************************************************************************************

>	class HTMLExportFilter : public Filter

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Purpose:	The HTML export filter base class.

				This filter itself will not be added into the filter system - 
				derived classes of this will be added. At the moment, the
				only derived class is ImagemapFilter.

				This class contains the functionality for writing out
				HTML tags.

				

**************************************************************************************/
class HTMLExportFilter : public Filter
{
	// Declare the class for memory tracking
	CC_DECLARE_DYNCREATE(HTMLExportFilter);

	//Constructor
public:
	HTMLExportFilter();

	//Write functions
	//These functions either write to files or text buffers
	//These functions are static so that any object can use them
	//to write itself out to a text file
public:
	INT32 Write(UINT32 uiResource, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	
	INT32 Write(TCHAR* pcToWrite, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);

	INT32 Write(DocCoord dcToWrite, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);
	INT32 WriteNumber(INT32 lToWrite, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);
						  			
	INT32 WriteTag(UINT32 uiResource, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	
	INT32 WriteCloseTag(UINT32 uiResource, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	INT32 WriteStartOfTag(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	
	INT32 WriteStartOfTag(UINT32 uiResource, CCLexFile* pfileToWrite, TCHAR* pcBuffer);
	INT32 WriteStartOfTag(TCHAR* pcTag, CCLexFile* pfileToWrite, TCHAR* pcBuffer);
											  																	  
	INT32 WriteStartOfCloseTag(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	INT32 WriteEndOfTag(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	INT32 WriteParameter(UINT32 uiParameter, UINT32 uiValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	
	INT32 WriteParameter(UINT32 uiParameter, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	
	INT32 WriteParameter(TCHAR* pcParameter, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	INT32 WriteParameterInQuotes(UINT32 uiParameter, UINT32 uiValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	
	INT32 WriteParameterInQuotes(UINT32 uiParameter, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	
	INT32 WriteParameterInQuotes(TCHAR* pcParameter, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	INT32 WriteCoords(DocRect rectToWrite, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	
	INT32 WriteCoords(Path* ppthToWrite, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	
	INT32 WriteCircleCoords(DocCoord dcCentre, INT32 lRadius, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);	

	INT32 WriteEOL(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);
	INT32 WriteTab(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);

	INT32 WriteIndent(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL);

	//Indent functions
public:
	INT32 GetIndent()
	{
		return m_lIndent;
	}

	void SetIndent(INT32 lIndent)
	{
		m_lIndent=lIndent;
	}

	void Indent(INT32 lIndentInc=1)
	{
		m_lIndent+=lIndentInc;
	}

	void Unindent(INT32 lIndentDec=1)
	{
		m_lIndent-=lIndentDec;
	}

	void CancelIndent()
	{
		m_lIndent=0;
	}

	//Word wrap functions
public:

	void EnableWordWrap(BOOL fShouldWordWrap=TRUE)
	{
		m_fShouldWordWrap=fShouldWordWrap;
	}

	INT32 GetWordWrap()
	{
		return m_lWordWrap;
	}

	void SetWordWrap(INT32 lWordWrap)
	{
		m_lWordWrap=lWordWrap;
	}

				 
	//GetString functions
public:
	String_256 GetTagString(UINT32 uiResource);	
	String_256 GetCloseTagString(UINT32 uiResource);	

	//Member variables
public:
	//The number of characters written on the current line
	INT32 m_lCharsOnThisLine;

	//Whether to do word wrapping
	BOOL m_fShouldWordWrap;
	
	//The number of characters that should be written on a line before this
	//filter automatically puts an EOL in
	INT32 m_lWordWrap;

	//The number of tab stops by which the current text is indented
	INT32 m_lIndent;


};



#endif	// INC_HTMLEXPORTFILTER
