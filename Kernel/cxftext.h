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

>	cxftext.h

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Purpose:	Exporting functions for text related objects

********************************************************************************************/

#ifndef INC_CXF_TEXT
#define INC_CXF_TEXT

class String_64;

/********************************************************************************************

>	class CXaraFileTxtStory

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/07/96
	Base Class:	-
	Purpose:	Exporting code for text stories for the new file format

********************************************************************************************/

class CXaraFileTxtStory
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, TextStory *pStory);

	static BOOL CanWriteChildrenWeb(BaseCamelotFilter* pFilter,TextStory *pStory);
	static BOOL CanWriteChildrenNative(BaseCamelotFilter* pFilter,TextStory *pStory);

	static BOOL WriteBeginChildRecordsWeb(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteBeginChildRecordsNative(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteEndChildRecordsWeb(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteEndChildRecordsNative(BaseCamelotFilter *pFilter, TextStory *pStory);

private:
	static BOOL WriteTextStory(BaseCamelotFilter *pFilter, TextStory *pStory);

	static BOOL WriteTextStorySimple(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteTextStoryComplex(BaseCamelotFilter *pFilter, TextStory *pStory);

	static BOOL WriteTextStorySimpleStartLeft(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteTextStorySimpleStartRight(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteTextStorySimpleEndLeft(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteTextStorySimpleEndRight(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteTextStoryComplexStartLeft(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteTextStoryComplexStartRight(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteTextStoryComplexEndLeft(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteTextStoryComplexEndRight(BaseCamelotFilter *pFilter, TextStory *pStory);

	static BOOL WriteTextStoryWordWrapInfo(BaseCamelotFilter *pFilter, TextStory *pStory);
	static BOOL WriteTextStoryIndentInfo(BaseCamelotFilter *pFilter, TextStory *pStory);

	static BOOL WriteTextStoryInvalid(BaseCamelotFilter *pFilter, TextStory *pStory);

	// WEBSTER - markn 31/1/97
	// Replaced with general system
	//static BOOL WriteTextStoryAsOutlines(BaseCamelotFilter *pFilter, TextStory *pStory);

	static BOOL IsGuaranteedFont(BaseCamelotFilter *pFilter,String_64* pFontName);
	static BOOL SiblingAndChildTypefaceAttrsAllGuaranteedFonts(BaseCamelotFilter *pFilter,Node* pNode);
	static BOOL MustConvertToOutlines(BaseCamelotFilter *pFilter, TextStory *pStory);


// member variables
protected:
	const static double mEpsilon;
};

/********************************************************************************************

>	class CXaraFileTxtLine

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/07/96
	Base Class:	-
	Purpose:	Exporting code for text line objects for the new file format

********************************************************************************************/

class CXaraFileTxtLine
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, TextLine *pLine);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, TextLine *pLine);
	static BOOL WriteBeginChildRecordsWeb(BaseCamelotFilter *pFilter, TextLine *pLine);
	static BOOL WriteBeginChildRecordsNative(BaseCamelotFilter *pFilter, TextLine *pLine);
	static BOOL WriteEndChildRecordsWeb(BaseCamelotFilter *pFilter, TextLine *pLine);
	static BOOL WriteEndChildRecordsNative(BaseCamelotFilter *pFilter, TextLine *pLine);

private:
	static BOOL WriteTextLine(BaseCamelotFilter *pFilter, TextLine *pLine);
	static BOOL WriteTextLineInfo(BaseCamelotFilter *pFilter, TextStory *pStory);
};

/********************************************************************************************

>	class CXaraFileTxtChar

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/07/96
	Base Class:	-
	Purpose:	Exporting code for text char objects for the new file format

********************************************************************************************/

class CXaraFileTxtChar
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, TextChar *pChar);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, TextChar *pChar);
private:
	static BOOL WriteTextChar(BaseCamelotFilter *pFilter, TextChar *pChar);
};

/********************************************************************************************

>	class CXaraFileTxtKern

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/07/96
	Base Class:	-
	Purpose:	Exporting code for text kern objects for the new file format

********************************************************************************************/

class CXaraFileTxtKern
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, KernCode *pKern);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, KernCode *pKern);
private:
	static BOOL WriteTextKern(BaseCamelotFilter *pFilter, KernCode *pKern);
};

/********************************************************************************************

>	class CXaraFileTxtTab

	Author:		Martin Wuerthner <xara@mw-software.com>
	Created:	29/06/06
	Base Class:	-
	Purpose:	Exporting code for tab objects for the new file format

********************************************************************************************/

class CXaraFileTxtTab
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, HorizontalTab *pTab);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, HorizontalTab *pTab);
private:
	static BOOL WriteTextTab(BaseCamelotFilter *pFilter, HorizontalTab* pTab);
};

/********************************************************************************************

>	class CXaraFileTxtCaret

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/07/96
	Base Class:	-
	Purpose:	Exporting code for text caret objects for the new file format

********************************************************************************************/

class CXaraFileTxtCaret
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, CaretNode *pCaret);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, CaretNode *pCaret);
private:
	static BOOL WriteTextCaret(BaseCamelotFilter *pFilter, CaretNode *pCaret);
};

/********************************************************************************************

>	class CXaraFileTxtEOL

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	10/07/96
	Base Class:	-
	Purpose:	Exporting code for text EOL objects for the new file format

********************************************************************************************/

class CXaraFileTxtEOL
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, EOLNode *pEOL);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, EOLNode *pEOL);
private:
	static BOOL WriteTextEOL(BaseCamelotFilter *pFilter, EOLNode *pEOL);
};

/********************************************************************************************

>	class CXaraFileTxtBold

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtBold
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtBold *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtBold *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtBold *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtFontTypeface

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

*******************************************************************************************/

class CXaraFileTxtFontTypeface
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtFontTypeface *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtFontTypeface *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtFontTypeface *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtItalic

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtItalic
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtItalic *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtItalic *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtItalic *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtUnderline

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtUnderline
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtUnderline *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtUnderline *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtUnderline *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtAspectRatio

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtAspectRatio
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtAspectRatio *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtAspectRatio *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtAspectRatio *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtJustification

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtJustification
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtJustification *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtJustification *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtJustification *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtTracking

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtTracking
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtTracking *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtTracking *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtTracking *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtFontSize

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtFontSize
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtFontSize *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtFontSize *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtFontSize *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtScript

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtScript
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtScript *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtScript *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtScript *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtBaseLine

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtBaseLine
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtBaseLine *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtBaseLine *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtBaseLine *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtLeftMargin

	Author:		Martin Wuerthner <xara@mw-software.com>
	Created:	04/07/06
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtLeftMargin
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtLeftMargin *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtLeftMargin *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtLeftMargin *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtRightMargin

	Author:		Martin Wuerthner <xara@mw-software.com>
	Created:	04/07/06
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtRightMargin
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtRightMargin *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtRightMargin *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtRightMargin *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtFirstIndent

	Author:		Martin Wuerthner <xara@mw-software.com>
	Created:	04/07/06
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtFirstIndent
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtFirstIndent *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtFirstIndent *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtFirstIndent *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtRuler

	Author:		Martin Wuerthner <xara@mw-software.com>
	Created:	04/07/06
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtRuler
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtRuler *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtRuler *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtRuler *pAttr);
};

/********************************************************************************************

>	class CXaraFileTxtLineSpace

	Author:		Andy_Hayward (Xara Group Ltd) <camelotdev@xara.com>
	Created:	09/07/96
	Base Class:	-
	Purpose:	Export code for the new file format

********************************************************************************************/

class CXaraFileTxtLineSpace
{
public:
	static BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter, AttrTxtLineSpace *pAttr);
	static BOOL WritePreChildrenNative(BaseCamelotFilter *pFilter, AttrTxtLineSpace *pAttr);
private:
	static BOOL WritePreChildrenAux(BaseCamelotFilter *pFilter, AttrTxtLineSpace *pAttr);
};

#endif
