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


// header file for NodeRenderableChapter

#ifndef INC_CHAPTER
#define	INC_CHAPTER

//#include "npaper.h"			// for NodeRenderablePaper - in camtypes.h [AUTOMATICALLY REMOVED]

class RenderRegion;
class Spread;



/***********************************************************************************************

>	class Chapter : public NodeRenderablePaper

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/4/93
	Purpose:	Chapters group together pages which are automatically created from the same 
				master page. 
				
	SeeAlso:	NodeRenderablePaper  
	SeeAlso:    Spread
	SeeAlso:    Page
	SeeAlso:    Layer

***********************************************************************************************/

class Chapter: public NodeRenderablePaper
{
CC_DECLARE_DYNAMIC( Chapter )

public:
	Chapter();

	Chapter(Node* ContextNode,
			AttachNodeDirection Direction,
			MILLIPOINT FldLineXCoord = 1000,
			BOOL Locked=FALSE,
			BOOL Mangled=FALSE,
			BOOL Marked=FALSE,
			BOOL Selected=FALSE
		   	);

	String Describe(BOOL Plural, BOOL Verbose);

	virtual BOOL IsChapter() const;


	Chapter* FindPreviousChapter(void);

	Spread* FindFirstSpread();

	XLONG GetChapterDepth();

	void Render(RenderRegion* pRender);

	void SetFoldLineXCoord(MILLIPOINT value, BOOL DisplayFoldLine = TRUE);
	MILLIPOINT GetFoldLineXCoord() const;
	BOOL ShouldShowFoldLine(void) const;


#ifdef _DEBUG   
	void ShowDebugTreeDetails() const;
#endif            

	virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	virtual void GetDebugDetails(StringBase* Str);   // This is used by the Debug Tree dialog
													 // It will probably be deleted when we ship !. 

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	virtual BOOL WriteBeginChildRecordsWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WriteBeginChildRecordsNative(BaseCamelotFilter* pFilter);
	virtual BOOL WriteEndChildRecordsWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WriteEndChildRecordsNative(BaseCamelotFilter* pFilter);

protected:
	virtual Node* SimpleCopy();   
	void CopyNodeContents(Chapter* NodeCopy); 

	MILLIPOINT FoldLineXCoord;			// X Coordinate of the main fold line
	BOOL ShowFoldLine;					// TRUE if the fold line should be displayed
};

#endif

