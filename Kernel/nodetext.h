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


#ifndef INC_NODETEXT
#define INC_NODETEXT

#ifdef DO_EXPORT
#define EXPORT_TEXT 1
#else
#define EXPORT_TEXT 0
#endif

#include "nodetxts.h"
#include "textfuns.h"

class AbstractTextChar;
class TextChar;

/********************************************************************************************
>	class VisibleTextNode: public BaseTextClass

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/94
	Purpose:	The VisibleTextNode is an abstract base class. All visible objects which 
				appear on text lines such as characters, kerns, carets, etc. will be instances 
				of derived classes of VisibleTextNode.
********************************************************************************************/

class VisibleTextNode: public BaseTextClass
{
	CC_DECLARE_DYNAMIC(VisibleTextNode)

public:
	VisibleTextNode(); 	
	VisibleTextNode(Node* ContextNode, AttachNodeDirection Direction);

	VisibleTextNode*  FindNextVTNInStory();
	VisibleTextNode*  FindPrevVTNInStory();
	AbstractTextChar* FindNextAbstractTextCharInStory();
	AbstractTextChar* FindPrevAbstractTextCharInStory();
	TextChar*         FindNextTextCharInStory();
	TextChar*         FindPrevTextCharInStory();

	VisibleTextNode*  FindNextVTNInLine();
	VisibleTextNode*  FindPrevVTNInLine();

	AbstractTextChar*  FindNextAbstractTextCharInLine();
	AbstractTextChar*  FindPrevAbstractTextCharInLine();

	TextLine*         FindParentLine();
			  
	virtual CopyType GetCopyType();
	virtual INT32 ComplexCopy(CopyStage Stage, Range& RangeToCopy, Node** pOutput);
	virtual INT32 ComplexHide(UndoableOperation* pOp, Node* pNextNode);

	BOOL RenderChildAttrs(RenderRegion* pRenderRegion);
	virtual BOOL CanAttrBeAppliedToMe(CCRuntimeClass* AttrType);

	virtual UINT32 GetNodeSize() const;
	virtual void GetDebugDetails(StringBase* Str);

	virtual BOOL OnNodePopUp(Spread* pSpread, DocCoord PointerPos, ContextMenu* pMenu);
	void ScrollToShow();

	BOOL GetStoryAndCharMatrix(Matrix* pMatrix);
	virtual BOOL ValidateBoundingRect(FormatRegion* pFormatRegion=NULL)
		{ ERROR2(FALSE,"VisibleTextNode::ValidateBoundingRect() - should never be called!"); }

	MILLIPOINT CalcCharDistAlongLine(BOOL IncludeThisChar);
	BOOL WrapRestOfLineForward(UndoableOperation* pUndoOp);
	BOOL WrapFromStartOfLineBack(UndoableOperation* pUndoOp);
	BOOL DoMoveNodes(UndoableOperation* pUndoOp, VisibleTextNode* pLastNode,
						Node* pDestNode, AttachNodeDirection Direction);
	BOOL DoMoveNode(UndoableOperation* pUndoOp, Node* pDestNode, AttachNodeDirection Direction);

	inline virtual BOOL IsAVisibleTextNode() const { return TRUE;  }
	inline virtual BOOL IsACaret()           const { return FALSE; }
	inline virtual BOOL IsAnEOLNode()        const { return FALSE; }
	inline virtual BOOL IsASpace()        { return FALSE; }
	inline virtual BOOL IsAVisibleSpace() { return FALSE; }
	inline virtual BOOL IsAHyphen()       { return FALSE; }
	inline virtual BOOL IsADecimalPoint() { return FALSE; }

	virtual MILLIPOINT GetCharAdvance()					{ return 0; }
	virtual MILLIPOINT GetCharWidth()					{ return 0; }
	virtual MILLIPOINT GetBaseLineShift()				{ return 0; }
	virtual MILLIPOINT GetAutoKernSize(FormatRegion*)	{ return 0; }	// Jonathan (17/10/2000

	// private member access functions
	MILLIPOINT GetPosInLine()             { return PosInLine; }
	void       SetPosInLine(MILLIPOINT x) { PosInLine=x; }

	void SetMatrix( const Matrix &matrix ) { CharMatrix = matrix; }
	Matrix  GetMatrix()  { return CharMatrix; }
	Matrix* GetpMatrix() { return &CharMatrix; }

protected:
	void Init();
	void CopyNodeContents(VisibleTextNode* NodeCopy);
	virtual Node* SimpleCopy();

private:
	Matrix     CharMatrix;		// character matrix
	MILLIPOINT PosInLine;		// x pos of char in line
};


/********************************************************************************************
>	class AbstractTextChar: public VisibleTextNode

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/94
	Purpose:	This is the base class for all VisibleTextNodes which have an associated
				Unicode character.
********************************************************************************************/

class AbstractTextChar: public VisibleTextNode
{
	CC_DECLARE_DYNAMIC(AbstractTextChar)

public:
	AbstractTextChar(); 	
	AbstractTextChar(Node* ContextNode, AttachNodeDirection Direction);

	virtual String Describe(BOOL Plural, BOOL Verbose);  		   
	virtual UINT32 GetNodeSize() const;
	virtual void GetDebugDetails(StringBase* Str);

	virtual DocRect GetBoundingRect(BOOL DontUseAttrs=FALSE, BOOL HitTest=FALSE);
	virtual DocRect GetBlobBoundingRect();
	virtual DocRect GetImagemapClickableRectangle();
	
	void  RenderObjectBlobs(RenderRegion* pRenderRegion);
	void  RenderTinyBlobs(RenderRegion* pRenderRegion);

	virtual BOOL ReCacheMetrics(FormatRegion* pFormatRegion);
	Path* CreateMetricsRectPath();
	BOOL  GetMetricsRect(DocRect* pRect);
	BOOL  GetMetricsRectInStory(DocRect* pRect);
	BOOL  GetMetricsRectBounds(DocRect* pRect);

	BOOL IsAnAbstractTextChar() const { return TRUE; }
	virtual WCHAR GetUnicodeValue() { return FONTEMCHAR; }
	MILLIPOINT GetVisibleAdvance();

	virtual MILLIPOINT GetCharWidth()     { return mCharWidth; }
	virtual MILLIPOINT GetCharAdvance()   { return mCharAdvance; }
	virtual MILLIPOINT GetBaseLineShift() { return mBaseLineShift; }

	MILLIPOINT GetFontAscent()    { return mFontAscent; }
	MILLIPOINT GetFontDescent()   { return mFontDescent; }
	MILLIPOINT GetFontSize()      { return mFontSize; }

	void SetCharAdvance(  MILLIPOINT Advance) { mCharAdvance   = Advance; }
	void SetCharWidth(    MILLIPOINT Width)   { mCharWidth     = Width; }
	void SetFontAscent(   MILLIPOINT Ascent)  { mFontAscent    = Ascent; }
	void SetFontDescent(  MILLIPOINT Descent) { mFontDescent   = Descent; }
	void SetFontSize(     MILLIPOINT Size)    { mFontSize      = Size; }
	void SetBaseLineShift(MILLIPOINT Size)    { mBaseLineShift = Size; }

	void    SetAttrdCharBounds(DocRect& rect) { mAttrdCharBounds = rect; }
	DocRect GetAttrdCharBounds()              { return mAttrdCharBounds; }

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	void Init();
	void CopyNodeContents(AbstractTextChar* NodeCopy);
	virtual Node* SimpleCopy();

	DocRect GetImagemapRectForAdjacentChars(BOOL fForwards);

private:
	MILLIPOINT mCharWidth;
	MILLIPOINT mCharAdvance;
	MILLIPOINT mBaseLineShift;
	MILLIPOINT mFontAscent;
	MILLIPOINT mFontDescent;
	MILLIPOINT mFontSize;
	DocRect    mAttrdCharBounds;	// bounds of char path (including effects of text attributes)
};


/********************************************************************************************
>	class TextChar: public AbstractTextChar

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/94
	Purpose:	Simplest type of TextStory character. The only data stored is a Unicode value.
********************************************************************************************/

class TextChar: public AbstractTextChar
{
	CC_DECLARE_DYNAMIC(TextChar)

public:
	TextChar(); 	
	TextChar(Node* ContextNode, AttachNodeDirection Direction, WCHAR ChCode);

	virtual BOOL SupportsClipboardFormat(InternalClipboardFormat *Format) const;
	virtual BOOL Snap(DocCoord* pDocCoord);

	virtual UINT32 GetNodeSize() const; 	// Returns size of node in bytes
	virtual void GetDebugDetails(StringBase* Str); // Can be deleted before we ship

	virtual void Render(RenderRegion* pRenderRegion);
	BOOL RenderCore(RenderRegion* pRenderRegion);
	void RenderEorDrag(RenderRegion* pRenderRegion);
	BOOL CreateNodePath(NodePath** ppNodePath, FormatRegion* pFormatRegion); 

	virtual BOOL IsATextChar() const			{ return TRUE; }
	virtual BOOL IsSetCandidate() const			{ return TRUE; }

	virtual BOOL IsASpace()        { return Ch==' '; }
	virtual BOOL IsAVisibleSpace() { return iswspace(Ch); }
	virtual BOOL IsAHyphen()       { return Ch=='-'; }

	virtual WCHAR GetUnicodeValue() { return Ch; }
	virtual void SetUnicodeValue(WCHAR Char) { Ch = Char; }

	virtual MILLIPOINT GetAutoKernSize(FormatRegion* pFormatRegion);

	virtual BOOL  ExportRender(RenderRegion* pRegion);		// Graeme (13/10/99).

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	virtual Node* SimpleCopy();
	void CopyNodeContents(TextChar* NodeCopy);

public:
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFIlter);
	virtual BOOL WritePostChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL WritePostChildrenNative(BaseCamelotFilter* pFilter);
	virtual BOOL CanWriteChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL CanWriteChildrenNative(BaseCamelotFilter* pFilter);

private:
	WCHAR Ch;	// 16 bit unicode character
};


/********************************************************************************************
>	class KernCode: public AbstractTextChar

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/94
	Purpose:	A Kern code. 
********************************************************************************************/

class KernCode: public AbstractTextChar
{
	CC_DECLARE_DYNAMIC(KernCode)

public:
	KernCode();
	KernCode(DocCoord& Value);
	KernCode(Node* ContextNode, AttachNodeDirection Direction, DocCoord& Value);

	virtual BOOL  ExportRender(RenderRegion* pRegion);
	virtual UINT32 GetNodeSize() const;
	virtual void  GetDebugDetails(StringBase* Str);

	void     SetValue(DocCoord& KernValue) { Value = KernValue; } 
	DocCoord GetValue()                    { return Value; }

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	virtual Node* SimpleCopy();
	void CopyNodeContents(KernCode* NodeCopy);
	
public:
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFIlter);

private:
	DocCoord Value; // Defines Kern offset
};

/********************************************************************************************
>	class HorizontalTab: public AbstractTextChar

	Author:		Martin Wuerthner (xara@mw-software.com)
	Created:	07/06/06
	Purpose:	A horizontal tab character
********************************************************************************************/

class HorizontalTab: public AbstractTextChar
{
	CC_DECLARE_DYNAMIC(HorizontalTab)

public:
	HorizontalTab() {}
	HorizontalTab(Node* ContextNode, AttachNodeDirection Direction);

	virtual BOOL  ExportRender(RenderRegion* pRegion);
	virtual UINT32 GetNodeSize() const;
	void PolyCopyNodeContents(NodeRenderable* pNodeCopy);
protected:
	virtual Node* SimpleCopy();
public:
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFIlter);
};

/********************************************************************************************
>	class CaretNode: public VisibleTextNode

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/2/95
	Purpose:	Some Notes about the Caret
	
				There will be a single CaretNode stored in every TextObject.
			
				The Caret's path will be rendered by the TextStory as an object blob, this 
				is so that it only gets shown if the Text object is selected.
													   
				The appearance of the Caret will vary depending on what is going on around it.
				In particular its height will be dependent on the heights of its ajacent chars.
				Because of this it makes sense to delay generating the caret's path until it 
				needs to be  rendered.
********************************************************************************************/

class CaretNode: public VisibleTextNode
{
	CC_DECLARE_DYNAMIC(CaretNode)

public:
	CaretNode(); 	
	CaretNode(Node* ContextNode, AttachNodeDirection Direction);
 
	virtual void SetSelected(BOOL Status);
	virtual BOOL DiscardsAttributeChildren() const;
	BOOL DoApplyAttrsTo(UndoableOperation* pUndoOp, VisibleTextNode* pDstVTN, BOOL bDeleteDups = TRUE);

	Path* CreatePath(Matrix* pMatrix); 
	void RenderObjectBlobs(RenderRegion* pRender); 
	BOOL RenderObjectBlobsCore(RenderRegion* pRender); 
	
	virtual BOOL ValidateBoundingRect(FormatRegion* pFormatRegion=NULL);
	virtual DocRect GetBoundingRect(BOOL DontUseAttrs=FALSE, BOOL HitTest=FALSE);
	virtual DocRect GetBlobBoundingRect();
		
	virtual BOOL ExportRender(RenderRegion* pRegion);

	virtual UINT32 GetNodeSize() const; 	
	virtual void GetDebugDetails(StringBase* Str); 
	virtual String Describe(BOOL Plural, BOOL Verbose);

	inline virtual BOOL IsACaret() const {return TRUE;};
	BOOL HasMoved();

protected:
 	virtual Node* SimpleCopy(); 

public:
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFIlter);
	virtual BOOL CanWriteChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL CanWriteChildrenNative(BaseCamelotFilter* pFilter);

private:
	DocRect BlobBounds;
};

/********************************************************************************************
>	class EOLNode: public VisibleTextNode

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/2/95
	Purpose:	Every TextLine that is created will have a EOLNode as its last child.
				This means that every TextLine will always have at least one child node.
********************************************************************************************/

class EOLNode: public AbstractTextChar
{
	CC_DECLARE_DYNAMIC(EOLNode)

public:
	EOLNode(); 	
	EOLNode(Node* ContextNode, AttachNodeDirection Direction);

	virtual DocRect GetBlobBoundingRect();
	virtual void RenderObjectBlobs(RenderRegion* pRender);
	virtual void RenderTinyBlobs(RenderRegion* pRender);
	BOOL GetBlobPath(Path*);

	virtual BOOL  ExportRender(RenderRegion* pRegion);
	virtual UINT32 GetNodeSize() const; 
	virtual void GetDebugDetails(StringBase* Str);
	virtual String Describe(BOOL Plural, BOOL Verbose);

	virtual BOOL ValidateBoundingRect(FormatRegion* pFormatRegion=NULL);
	virtual DocRect GetBoundingRect(BOOL DontUseAttrs=FALSE, BOOL HitTest=FALSE);

	inline virtual BOOL IsAnEOLNode() const {return TRUE;};

	BOOL IsVirtual() const       { return Virtual; }
	void SetVirtual(BOOL Status) { Virtual = Status; }

	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:
	virtual Node* SimpleCopy();
	void CopyNodeContents(EOLNode* NodeCopy);

public:
	virtual BOOL WritePreChildrenWeb(BaseCamelotFilter *pFilter);
	virtual BOOL WritePreChildrenNative(BaseCamelotFilter *pFIlter);
	virtual BOOL CanWriteChildrenWeb(BaseCamelotFilter* pFilter);
	virtual BOOL CanWriteChildrenNative(BaseCamelotFilter* pFilter);

private:
	BYTE Virtual   : 1;	// EOL is transient ie when converting a cut/copied selection to a story on the clipboard
};
 
#endif
