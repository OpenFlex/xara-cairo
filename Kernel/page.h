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


#ifndef INC_PAGE
#define	INC_PAGE


class RenderRegion;

// The LinkDirection type specifies a direction in which one page is linked to another                                
enum LinkDirection { LEFT, RIGHT, TOP, BOTTOM }; 

/***********************************************************************************************

>	class Page : public NodeRenderablePaper

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/4/93
	Purpose:	Represents the actual bits of paper on which the document will be printed. 
	SeeAlso:	NodeRenderablePaper   
	SeeAlso:    Chapter
	SeeAlso:    Spread
	SeeAlso:    Layer
	

***********************************************************************************************/

class Page: public NodeRenderablePaper
{   
	CC_DECLARE_DYNAMIC( Page ) 

public:  
	Page(); 
	
	Page(Node* ContextNode,  
		 AttachNodeDirection Direction,
	     const DocRect& NewPageRect, 
		 BOOL Locked=FALSE, 
	     BOOL Mangled=FALSE,  
		 BOOL Marked=FALSE, 
		 BOOL Selected=FALSE 
		);   
			  
	String Describe(BOOL Plural, BOOL Verbose);    		   	
		   		   
	void Render( RenderRegion* pRender );
	
	const DocRect& GetPageRect(void) const; 
	BOOL SetPageRect(DocRect NewPageRect);		// set new size of page
	
	Page* FindNextPage(void); 
	Page* FindRightPage(void); 
	Page* FindBottomPage(void);     
	void CopyIntoSpread(Page* pContextPage, LinkDirection ld);      
	
	#ifdef _DEBUG						  
	void ShowDebugTreeDetails() const;   
	#endif
	
	static void SetPageColour(DocColour &NewColour); 
	static DocColour &GetPageColour(void);  

    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

	
	virtual void GetDebugDetails(StringBase* Str);   // This is used by the Debug Tree dialog
													 // It will probably be deleted when we ship !. 
	
	// Snapping functions
   	virtual BOOL Snap(DocCoord* pDocCoord);
	virtual BOOL Snap(DocRect* pDocRect,const DocCoord& PrevCoord,const DocCoord& CurCoord);

	// Version 2 file format functions
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter* pFilter);

	static DocColour PageColour; 

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	DocRect PageRect; // Pages document rectangle	
	virtual Node* SimpleCopy();   
	void CopyNodeContents(Page* NodeCopy); 

private:
	INT32 SnapOrdinate(INT32 Lo, INT32 Hi,INT32 Src,INT32 SnapDist);

};
#endif

