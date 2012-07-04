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

/********************************************************************************************

>	rechtext.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Purpose:	Text record handler for the new file format

********************************************************************************************/

#ifndef INC_RECH_TEXT
#define INC_RECH_TEXT

class TextStory;

/********************************************************************************************

>	class TextObjRecordHandler : public CamelotRecordHandler

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/07/96
	Base Class:	CamelotRecordHandler
	Purpose:	Record handler for text objects
	See also:	class TextAttrRecordHandler

********************************************************************************************/

class TextObjRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(TextObjRecordHandler);
	
public:
	TextObjRecordHandler() { pLastInsertedTextStory = NULL; };
	~TextObjRecordHandler() {};
	
// functions that must be implemented
public:
	UINT32* GetTagList();
	BOOL HandleRecord(CXaraFileRecord* pCXaraFileRecord);

	virtual BOOL BeginImport();

private:
	BOOL ReadTextStorySimple(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStoryComplex(CXaraFileRecord *pCXaraFileRecord);
	
	BOOL ReadTextStorySimpleStartLeft(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStorySimpleStartRight(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStorySimpleEndLeft(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStorySimpleEndRight(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStoryComplexStartLeft(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStoryComplexStartRight(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStoryComplexEndLeft(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStoryComplexEndRight(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStoryWordWrapInfo(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextStoryIndentInfo(CXaraFileRecord *pCXaraFileRecord);

	BOOL ReadTextLine(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextString(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextChar(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextEOL(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextKernCode(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextTab(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextCaret(CXaraFileRecord *PCXaraFileRecord);
	BOOL ReadTextLineInfo(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextInvalid(CXaraFileRecord *pCXaraFileRecord);

	BOOL ReadAutoKern ( CXaraFileRecord	*pCXaraFileRecord,
						TextStory		*pStory );

	// Code to keep track of the last text story inserted into the tree
	BOOL InsertTextStoryNode(TextStory* pTextStory);
	TextStory* pLastInsertedTextStory;

#ifdef XAR_TREE_DIALOG
public:
	void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord, StringBase *pStr);
	void DescribeStorySimple(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStoryComplex(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStorySimpleStartLeft(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStorySimpleStartRight(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStorySimpleEndLeft(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStorySimpleEndRight(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStoryComplexStartLeft(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStoryComplexStartRight(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStoryComplexEndLeft(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStoryComplexEndRight(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStoryWordWrapInfo(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeStoryIndentInfo(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeLine(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeString(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeChar(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeEOL(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeKern(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeCaret(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeLineInfo(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeInvalid(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
#endif
};

/********************************************************************************************

>	class TextAttrRecordHandler : public CamelotRecordHandler

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	CamelotRecordHandler
	Purpose:	Record handler for text attribute records

********************************************************************************************/

class TextAttrRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(TextAttrRecordHandler);
	
public:
	TextAttrRecordHandler() {};
	~TextAttrRecordHandler() {};
	
// functions that must be implemented
public:
	UINT32* GetTagList();
	BOOL HandleRecord(CXaraFileRecord* pCXaraFileRecord);

private:
	BOOL ReadTextStoryVanilla(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextString(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextKern(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextCaret(CXaraFileRecord *PCXaraFileRecord);
	BOOL ReadTextLineSpaceRatio(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextLineSpaceAbsolute(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextJustificationLeft(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextJustificationCentre(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextJustificationRight(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextJustificationFull(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextFontSize(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextFontTypeface(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextBoldOn(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextBoldOff(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextItalicOn(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextItalicOff(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextUnderlineOn(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextUnderlineOff(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextScriptOn(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextScriptOff(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextSuperscriptOn(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextSubscriptOn(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextTracking(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextAspectRatio(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextBaseline(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextLeftIndent(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextRightIndent(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextFirstIndent(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextRuler(CXaraFileRecord *pCXaraFileRecord);
	BOOL ReadTextInvalid(CXaraFileRecord *pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
public:
	void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord, StringBase *pStr);
	void DescribeLineSpaceRatio(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeLineSpaceAbsolute(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeJustificationLeft(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeJustificationCentre(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeJustificationRight(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeJustificationFull(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeFontSize(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeFontTypeface(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeBoldOn(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeBoldOff(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeItalicOn(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeItalicOff(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeUnderlineOn(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeUnderlineOff(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeScriptOn(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeScriptOff(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeSuperscriptOn(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeSubscriptOn(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeTracking(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeAspectRatio(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeBaseline(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeInvalid(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
#endif

};

/********************************************************************************************

>	class FontDefRecordHandler : public CamelotRecordHandler

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	12/08/96
	Base Class:	CamelotRecordHandler
	Purpose:	Record Handler for font definition records

********************************************************************************************/

class FontDefRecordHandler : public CamelotRecordHandler
{
	// Give my name in memory dumps
	CC_DECLARE_DYNAMIC(FontDefRecordHandler);
	
public:
	FontDefRecordHandler() {};
	~FontDefRecordHandler() {};
	
// functions that must be implemented
public:
	UINT32* GetTagList();
	BOOL HandleRecord(CXaraFileRecord* pCXaraFileRecord);

#ifdef XAR_TREE_DIALOG
public:
	void GetRecordDescriptionText(CXaraFileRecord* pCXaraFileRecord, StringBase *pStr);
	void DescribeFontDefTrueType(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeFontDefATM(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
	void DescribeFontDefInvalid(CXaraFileRecord *pCXaraFileRecord, StringBase *pStr);
#endif
};

#endif
