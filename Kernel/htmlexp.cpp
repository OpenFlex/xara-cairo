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


#include "camtypes.h"
#include "htmlexp.h"


//#include "resimmap.h"		// For all the HTML tag resources




CC_IMPLEMENT_DYNAMIC(HTMLExportFilter, Filter)


/********************************************************************************************

  Constructor

*********************************************************************************************/

/********************************************************************************************

  >	INT32 HTMLExportFilter::HTMLExportFilter()

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Purpose:	Default constructor

********************************************************************************************/

HTMLExportFilter::HTMLExportFilter()
{
	//Set all member variables to defaults
	m_lCharsOnThisLine=0;
	m_lWordWrap=HTMLEXPORT_DEFAULTWORDWRAP;
	m_lIndent=0;
	m_fShouldWordWrap=TRUE;
}


/********************************************************************************************

  Write functions

*********************************************************************************************/

/********************************************************************************************

  >	INT32 HTMLExportFilter::Write(UINT32 uiResource, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		uiResource		The resource to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		Pointer to the text buffer to write to (may be NULL)
				fWrap			Whether to do word wrapping or not
								Set to FALSE if you want to write something
								(e.g. a tag) without this function putting
								word wrapping end of lines in.

	Returns:	The number of TCHARs written
	Purpose:	Writes the specified uiResource to the file, or the text buffer,
				or both, or neither.

				This function returns the number of TCHARS written. So you
				can call this function first with all parameters NULL to find out
				the length of the text buffer you need, then set up that text buffer,
				then call this function again to write to that text buffer.

********************************************************************************************/
INT32 HTMLExportFilter::Write(UINT32 uiResource, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Construct our string
	String_256 strToWrite(uiResource);

	//Then call our sister function to write out the string
	return Write(strToWrite, pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::Write(TCHAR* pcToWrite, CCLexFile* pfileToWrite, TCHAR* pcBuffer)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		pcToWrite		The string to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)

	Returns:	The number of TCHARs written
	Purpose:	Writes the specified string to the file, or the text buffer,
				or both, or neither.

				This function returns the number of TCHARS written. So you
				can call this function first with all parameters NULL to find out
				the length of the text buffer you need, then set up that text buffer,
				then call this function again to write to that text buffer.

				Note that this should be the *only* function that actually writes
				to the file. All other write functions must call this one. That's
				because this function handles the word wrapping.

  Notes:		This is how the word wrapping works:

				First this function writes out the string passed to it (e.g. "<HTML>").
				It does not put any EOLs in the middle of this string.

				Then it checks to see if word wrapping is turned on (from our 
				member flag m_fShouldWordWrap).

				If so, it checks to see if the number of characters written on the
				line so far is greater than the word wrap limit.

				If so, this function puts an EOL line after the string that has
				been written.

				Note that, if you write an end of line string ("\r\n") directly to
				the write function without calling WriteEOL, the word wrapping
				will not work properly.


********************************************************************************************/
INT32 HTMLExportFilter::Write(TCHAR* pcToWrite, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//If we've been passed a NULL pointer, then simply write nothing
	if (pcToWrite==NULL)
		return 0;

	//If we have a file, then write to it
	if (pfileToWrite)
		pfileToWrite->write(pcToWrite, camStrlen(pcToWrite));

	//If we have a text buffer, then write to it
	if (pcBuffer)
	{
		//We want to start writing at the NULL character where the text
		//buffer ends at the moment.
		
		//So find the length of the buffer
		INT32 lBufLen=camStrlen(pcBuffer);

		//And start writing at the NULL character
		camStrcpy(pcBuffer+lBufLen*sizeof(TCHAR), pcToWrite);
	}

	//So, the number of characters written is equal to the length of the string
	INT32 lCharsWritten= camStrlen(pcToWrite);

	//Now, if we should be doing word wrapping
	if (m_fShouldWordWrap)
	{
		//Then update the number of characters on this line
		m_lCharsOnThisLine+=lCharsWritten;

		//And if we have now exceeded the maximum number of characters
		//that should be written on this line
		if (m_lCharsOnThisLine > m_lWordWrap)
		{
			//Then write out an end of line
			//This will also reset m_lCharsOnThisLine to zero
			lCharsWritten+=WriteEOL(pfileToWrite, pcBuffer);
		}
	}

	//And return the number of characters written
	return lCharsWritten;
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::Write(INT32 lToWrite, CCLexFile* pfileToWrite, TCHAR* pcBuffer)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		lToWrite		The number to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes the number to the file

********************************************************************************************/
INT32 HTMLExportFilter::WriteNumber(INT32 lToWrite, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Format our number
	String_256 strFormat;

	strFormat.MakeMsg(_R(IDS_HTMLEXPORT_NUMBERFORMAT), lToWrite);

	//And write it out
	return Write(strFormat, pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::Write(DocCoord dcToWrite, CCLexFile* pfileToWrite, TCHAR* pcBuffer)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		pcToWrite		The coordinate to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes the coordinate to the file, separated by
				a comma:

				200,100

********************************************************************************************/
INT32 HTMLExportFilter::Write(DocCoord dcToWrite, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Format our coords
	String_256 strFormat;

	strFormat.MakeMsg(_R(IDS_HTMLEXPORT_COORDFORMAT), dcToWrite.x, dcToWrite.y);

	//And write it out
	return Write(strFormat, pfileToWrite, pcBuffer);
}


/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteTag(UINT32 uiResource, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		uiResource		The resource to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out the specified UI resource enclosed by < and >.

********************************************************************************************/
INT32 HTMLExportFilter::WriteTag(UINT32 uiResource, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Get our tag string
	String_256 strToWrite=GetTagString(uiResource);

	//Then call our sister function to write out the string
	return Write(strToWrite, pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteCloseTag(UINT32 uiResource, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		uiResource		The resource to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out the specified UI resource enclosed by </ and >.

********************************************************************************************/
INT32 HTMLExportFilter::WriteCloseTag(UINT32 uiResource, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Get our close tag string
	String_256 strToWrite=GetCloseTagString(uiResource);

	//Then call our sister function to write out the string
	return Write(strToWrite, pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteStartOfTag(UINT32 uiResource, CCLexFile* pfileToWrite, TCHAR* pcBuffer)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		uiResource		The resource to write after the start of the tag
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a < followed by a resource (e.g. "<IMG")

********************************************************************************************/
INT32 HTMLExportFilter::WriteStartOfTag(UINT32 uiResource, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Get our start tag string
	String_256 strToWrite(_R(IDS_HTMLEXPORT_TAGSTART));

	//Add the resource string to the end of it
	strToWrite+=String_256(uiResource);

	//Then call our sister function to write out the string
	//making sure the write function doesn't put an EOL
	//after it
	return Write(strToWrite, pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteStartOfTag(TCHAR* pcTag, CCLexFile* pfileToWrite, TCHAR* pcBuffer)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		pcTag			The string to write after the start of the tag
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a < followed by a resource (e.g. "<IMG")

********************************************************************************************/
INT32 HTMLExportFilter::WriteStartOfTag(TCHAR* pcTag, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Get our start tag string
	String_256 strToWrite(_R(IDS_HTMLEXPORT_TAGSTART));

	//Add the resource string to the end of it
	strToWrite+=pcTag;

	//Then call our sister function to write out the string
	//making sure the write function doesn't put an EOL
	//after it
	return Write(strToWrite, pfileToWrite, pcBuffer);
}




/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteStartOfTag(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		uiResource		The resource to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a <

********************************************************************************************/
INT32 HTMLExportFilter::WriteStartOfTag(CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Get our close tag string
	String_256 strToWrite(_R(IDS_HTMLEXPORT_TAGSTART));

	//Then call our sister function to write out the string
	//making sure the write function doesn't put an EOL
	//after it
	return Write(strToWrite, pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteStartOfCloseTag(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		uiResource		The resource to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a <\

********************************************************************************************/
INT32 HTMLExportFilter::WriteStartOfCloseTag(CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Get our close tag string
	String_256 strToWrite(_R(IDS_HTMLEXPORT_CLOSETAGSTART));

	//Then call our sister function to write out the string
	//making sure the write function doesn't put an EOL
	//after it
	return Write(strToWrite, pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteEndOfTag(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a >

********************************************************************************************/
INT32 HTMLExportFilter::WriteEndOfTag(CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Get our close tag string
	String_256 strToWrite(_R(IDS_HTMLEXPORT_TAGEND));

	//Then call our sister function to write out the string
	return Write(strToWrite, pfileToWrite, pcBuffer);
}


/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteParameter(UINT32 uiParameter, UINT32 uiValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		uiParameter		The resource of the parameter to write (e.g. SHAPE)
				uiValue			The resource of the value of the parameter (e.g. RECTANGLE)
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a parameter, e.g. SHAPE=RECTANGLE

********************************************************************************************/
INT32 HTMLExportFilter::WriteParameter(UINT32 uiParameter, UINT32 uiValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Get our two strings
	String_256 strParameterToWrite(uiParameter);
	String_256 strValueToWrite(uiValue);
	
	//Then call our sister function to write out the string
	return WriteParameter((TCHAR*) strParameterToWrite, (TCHAR*) strValueToWrite, pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteParameter(UINT32 uiParameter, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		uiParameter	The parameter to write (e.g. SHAPE)
				pcValue			The value of the parameter (e.g. RECTANGLE)
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a parameter, e.g. SHAPE=RECTANGLE

********************************************************************************************/
INT32 HTMLExportFilter::WriteParameter(UINT32 uiParameter, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//This is the value we will return
	INT32 lCharsWritten=0;

	//First write out a space, to separate this parameter from the one before
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_SPACE), pfileToWrite, pcBuffer);

	//Now write out the parameter
	lCharsWritten+=Write(uiParameter, pfileToWrite, pcBuffer);
				   
	//And an equals sign
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_EQUALS), pfileToWrite, pcBuffer);

	//And the value
	lCharsWritten+=Write(pcValue, pfileToWrite, pcBuffer);

	//And return the number of characters written
	return lCharsWritten;
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteParameter(TCHAR* pcParameter, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		pcParameter	The parameter to write (e.g. SHAPE)
				pcValue			The value of the parameter (e.g. RECTANGLE)
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a parameter, e.g. SHAPE=RECTANGLE

********************************************************************************************/
INT32 HTMLExportFilter::WriteParameter(TCHAR* pcParameter, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//This is the value we will return
	INT32 lCharsWritten=0;

	//First write out a space, to separate this parameter from the one before
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_SPACE), pfileToWrite, pcBuffer);

	//Now write out the parameter
	lCharsWritten+=Write(pcParameter, pfileToWrite, pcBuffer);
				   
	//And an equals sign
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_EQUALS), pfileToWrite, pcBuffer);

	//And the value
	lCharsWritten+=Write(pcValue, pfileToWrite, pcBuffer);

	//And return the number of characters written
	return lCharsWritten;
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteParameterWithQuotes(UINT32 uiParameter, UINT32 uiValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		uiParameter		The resource of the parameter to write (e.g. SHAPE)
				uiValue			The resource of the value of the parameter (e.g. RECTANGLE)
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a parameter, putting the value in quotes,
				e.g. COORDS="146, 145, 234, 132, 12, 456"

********************************************************************************************/
INT32 HTMLExportFilter::WriteParameterInQuotes(UINT32 uiParameter, UINT32 uiValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Get our two strings
	String_256 strParameterToWrite(uiParameter);
	String_256 strValueToWrite(uiValue);
	
	//Then call our sister function to write out the string
	return WriteParameterInQuotes(strParameterToWrite, strValueToWrite, pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteParameterInQuotes(UINT32 uiParameter, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		uiParameter	The parameter to write (e.g. SHAPE)
				pcValue			The value of the parameter (e.g. RECTANGLE)
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a parameter with the value in quotes, e.g.
				HREF="http://www.xara.com"

********************************************************************************************/
INT32 HTMLExportFilter::WriteParameterInQuotes(UINT32 uiParameter, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//This is the value we will return
	INT32 lCharsWritten=0;

	//First write out a space, to separate this parameter from the one before
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_SPACE), pfileToWrite, pcBuffer);

	//Now write out the parameter
	lCharsWritten+=Write(uiParameter, pfileToWrite, pcBuffer);
				   
	//And an equals sign
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_EQUALS), pfileToWrite, pcBuffer);

	//And an opening quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//And the value
	lCharsWritten+=Write(pcValue, pfileToWrite, pcBuffer);

	//And a closing quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//And return the number of characters written
	return lCharsWritten;
}


/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteParameterInQuotes(TCHAR* pcParameter, TCHAR* pcValue, CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		pcParameter	The parameter to write (e.g. SHAPE)
				pcValue			The value of the parameter (e.g. RECTANGLE)
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a parameter with the value in quotes, e.g.
				HREF="http://www.xara.com"

********************************************************************************************/
INT32 HTMLExportFilter::WriteParameterInQuotes(TCHAR* pcParameter, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//This is the value we will return
	INT32 lCharsWritten=0;

	//First write out a space, to separate this parameter from the one before
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_SPACE), pfileToWrite, pcBuffer);

	//Now write out the parameter
	lCharsWritten+=Write(pcParameter, pfileToWrite, pcBuffer);
				   
	//And an equals sign
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_EQUALS), pfileToWrite, pcBuffer);

	//And an opening quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//And the value
	lCharsWritten+=Write(pcValue, pfileToWrite, pcBuffer);

	//And a closing quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//And return the number of characters written
	return lCharsWritten;
}

/********************************************************************************************

INT32 HTMLExportFilter::WriteCoords(DocRect rectToWrite, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		rectToWrite		The rectangle to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out the coordinates of a rectangular area,
				e.g. COORDS="0,0,100,100"

********************************************************************************************/
INT32 HTMLExportFilter::WriteCoords(DocRect rectToWrite, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//This is the value we will return
	INT32 lCharsWritten=0;

	//First write out a space
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_SPACE), pfileToWrite, pcBuffer);

	//Now write out COORDS
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_COORDS), pfileToWrite, pcBuffer);
				   
	//And an equals sign
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_EQUALS), pfileToWrite, pcBuffer);

	//And an opening quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//And the coords
	lCharsWritten+=Write(rectToWrite.lo, pfileToWrite, pcBuffer);
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_COMMA), pfileToWrite, pcBuffer);
	lCharsWritten+=Write(rectToWrite.hi, pfileToWrite, pcBuffer);
	
	//And a closing quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//And return the number of characters written
	return lCharsWritten;
}

/********************************************************************************************

	INT32 HTMLExportFilter::WriteCoords(Path* ppthToWrite, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		ppthToWrite		Pointer to the path to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out the coordinates of a polygon
				e.g. COORDS="0,0,0,100,100,100,100,0"

********************************************************************************************/
INT32 HTMLExportFilter::WriteCoords(Path* ppthToWrite, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//This is the value we will return
	INT32 lCharsWritten=0;

	//First write out a space
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_SPACE), pfileToWrite, pcBuffer);

	//Now write out COORDS
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_COORDS), pfileToWrite, pcBuffer);
				   
	//And an equals sign
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_EQUALS), pfileToWrite, pcBuffer);

	//And an opening quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//Now we must write out the path's coordinates. So find out how
	//INT32 the path is
	INT32 lNumCoords=ppthToWrite->GetNumCoords();

	//And get its coordinate and verb arrays
	DocCoord* pdcCoords=ppthToWrite->GetCoordArray();
//	PathVerb* ppvVerbs=ppthToWrite->GetVerbArray();

	//Keep a copy of the last coordinate written, to make sure
	//we don't write out two consecutive identical coordinates
	DocCoord dcLastWritten=DocCoord(-1, -1);

	//Now do the following for every coordinate in the path
	//EXCEPT the last, which will be the same as the first
	INT32 lThisCoord=0;

	do
	{
		//If this coordinate isn't the same as the last one we wrote
		if (pdcCoords[lThisCoord]!=dcLastWritten)
		{
			//Write out a comma, unless this is the first coord to be written
			if (lThisCoord>0)
				lCharsWritten+=Write(_R(IDS_HTMLEXPORT_COMMA), pfileToWrite, pcBuffer);

			//Write it out, followed by a comma
			lCharsWritten+=Write(pdcCoords[lThisCoord], pfileToWrite, pcBuffer);
		}

		//Keep a copy of this coordinate
		dcLastWritten=pdcCoords[lThisCoord];

		//And move on to the next coordinate
		ppthToWrite->FindNextEndPoint(&lThisCoord);
				
	}
	while (lThisCoord<lNumCoords-1);


	//Write a closing quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//And return the number of characters written
	return lCharsWritten;
}

/********************************************************************************************

	INT32 HTMLExportFilter::WriteCircleCoords(DocCoord dcCentre, INT32 lRadius, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		dcCentre		Centre of the circle to write
				lRadius			Radius of the circle to write
				pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out the coordinates of a circle
				e.g. COORDS="200,200,100"

********************************************************************************************/
INT32 HTMLExportFilter::WriteCircleCoords(DocCoord dcCentre, INT32 lRadius, TCHAR* pcValue, CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//This is the value we will return
	INT32 lCharsWritten=0;

	//First write out a space
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_SPACE), pfileToWrite, pcBuffer);

	//Now write out COORDS
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_COORDS), pfileToWrite, pcBuffer);
				   
	//And an equals sign
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_EQUALS), pfileToWrite, pcBuffer);

	//And an opening quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//The centre
	lCharsWritten+=Write(dcCentre, pfileToWrite, pcBuffer);

	//A comma
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_COMMA), pfileToWrite, pcBuffer);

	//The radius
	lCharsWritten+=WriteNumber(lRadius, pfileToWrite, pcBuffer);

	//Write a closing quote
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_QUOTES), pfileToWrite, pcBuffer);

	//And return the number of characters written
	return lCharsWritten;
}




/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteEOL(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out an end of line character

				Also writes out the appropriate number of tabs, according to
				how much the current text is indented.

********************************************************************************************/
INT32 HTMLExportFilter::WriteEOL(CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Keep a count of the number of characters we write
	INT32 lCharsWritten=0;

	//Now, while we write out the following characters, we must turn
	//off word wrapping, so we don't write out an end of line and then
	//do word wrapping (for instance)
	EnableWordWrap(FALSE);

	//Write an end of line
	lCharsWritten+=Write(_R(IDS_HTMLEXPORT_EOL), pfileToWrite, pcBuffer);

	//Now write out the indent
	lCharsWritten+=WriteIndent(pfileToWrite, pcBuffer);

	//Set the number of characters written on this line to zero
	m_lCharsOnThisLine=0;

	//Turn word wrapping back on
	EnableWordWrap(TRUE);

	//And return the number of characters written
	return lCharsWritten;
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteTab(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes out a tab character

********************************************************************************************/
INT32 HTMLExportFilter::WriteTab(CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	return Write(_R(IDS_HTMLEXPORT_TAB), pfileToWrite, pcBuffer);
}

/********************************************************************************************

  >	INT32 HTMLExportFilter::WriteIndent(CCLexFile* pfileToWrite=NULL, TCHAR* pcBuffer=NULL)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/4/97
	Inputs:		pfileToWrite	The file to write to (may be NULL)
				pcBuffer		The text buffer to write to (may be NULL)
	Returns:	The number of TCHARs written
	Purpose:	Writes a number of tab characters equal to the current
				indent level.

********************************************************************************************/
INT32 HTMLExportFilter::WriteIndent(CCLexFile* pfileToWrite, TCHAR* pcBuffer)
{
	//Keep a count of the number of characters written
	INT32 lCharsWritten=0;

	//And write out one tab for every indent level
	for (INT32 i=0; i<m_lIndent; i++)
	{
		lCharsWritten+=Write(_R(IDS_HTMLEXPORT_TAB), pfileToWrite, pcBuffer);
	}

	//And return the number of characters written
	return lCharsWritten;
}




/********************************************************************************************

  >	String_256 HTMLExportFilter::GetTagString(UINT32 uiResource)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		uiResource		The resource to convert to a tag
				
	Returns:	The resource string enclosed in < and >.
	Purpose:	Gets the specified UI resource enclosed by < and >.

********************************************************************************************/
String_256 HTMLExportFilter::GetTagString(UINT32 uiResource)
{
	String_256 strStart(_R(IDS_HTMLEXPORT_TAGSTART));
	strStart+=String_256(uiResource);
	strStart+=String_256(_R(IDS_HTMLEXPORT_TAGEND));

	return strStart;
}

/********************************************************************************************

  >	String_256 HTMLExportFilter::GetCloseTagString(UINT32 uiResource)

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/4/97
	Inputs:		uiResource		The resource to convert to a tag
				
	Returns:	The resource string enclosed in < and >.
	Purpose:	Gets the specified UI resource enclosed by < and >.

********************************************************************************************/
String_256 HTMLExportFilter::GetCloseTagString(UINT32 uiResource)
{
	String_256 strStart(_R(IDS_HTMLEXPORT_CLOSETAGSTART));
	strStart+=String_256(uiResource);
	strStart+=String_256(_R(IDS_HTMLEXPORT_TAGEND));

	return strStart;
}






