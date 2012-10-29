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

// Defines the OpBackground class

#ifndef INC_BACKGROUND_H
#define INC_BACKGROUND_H


#if !defined(EXCLUDE_FROM_RALPH)

class Document;
class Spread;
class Layer;
class DocRect;
class KernelBitmap;
class DocColour;
class NodeRegularShape;

/********************************************************************************************

>	class OpBackgroundParam : public OpParam

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/3/97
	Purpose:	Param passed to OpBackground::DoWithParams()

********************************************************************************************/

class OpBackgroundParam : public OpParam
{
	CC_DECLARE_MEMDUMP(OpBackgroundParam)

public:
	OpBackgroundParam() { pDoc = NULL; pSpread = NULL; pDocColour = NULL; pBitmap = NULL; }	

public:
	Document *	pDoc;
	Spread *	pSpread;

	DocColour * pDocColour;
	KernelBitmap * pBitmap;
};

/********************************************************************************************

>	class OpBackground : public UndoableOperation

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	26/3/97
	Purpose:	Allows the background layer to be set up and changed

********************************************************************************************/

class OpBackground : public UndoableOperation
{

CC_DECLARE_DYNCREATE(OpBackground);

public:
	#define OPTOKEN_BACKGROUND _T("Background")	

	// Construction/Destruction
	OpBackground();
	~OpBackground();

	virtual void DoWithParam(OpDescriptor* pOpDesc,OpParam* pParam);

//	virtual BOOL Undo();
//	virtual BOOL Redo();
	
	// These functions required for the OpDescriptor class
	static BOOL Init();
	static OpState GetState(String_256* Description, OpDescriptor*);
	void GetOpName(String_256* OpName);

	static BOOL FixBackgroundLayer(Layer * pLayer, const DocRect& NewPagesRect, const DocRect& OldPagesRect);

	// These should be useable by outside ops 
	static BOOL MakePageBackground(UndoableOperation * pOp, Spread * pSpread, DocColour * pDocColour);
	static BOOL MakePageBackground(UndoableOperation * pOp, Spread * pSpread, KernelBitmap * pBitmap);
	static BOOL GetPageColour(Spread *pSpread, KernelBitmap **pOutBitmap, DocColour **pOutColour);

protected:
	// The all important Do functions

	// This is the main workhorse
	static BOOL DoMakePageBackground(UndoableOperation * pOp, Spread * pSpread, KernelBitmap * pBitmap,
									 DocColour * pDocColour = NULL);
	
	// Creating the special page background layer
	static Layer* CreateBackgroundLayer();
	static Layer* DoCreateBackgroundLayer(UndoableOperation * pOp, Spread * pSpread);

	// Finding and creating the page covering retangle
	static NodeRegularShape * DoFindPageRectangle(Spread * pSpread, Layer* pBackgroundLayer);
	static NodeRegularShape * DoCreateRectangle(Spread * pSpread);
	static NodeRegularShape * FindPageRectangle(Layer* pBackgroundLayer, const DocRect& PagesRect);

	// Applying the attributes to the rectangle
	static BOOL ApplyDocColour(DocColour * pColourToApply, NodeRegularShape * pShape);
	static BOOL ApplyBitmap(KernelBitmap * pBitmapToApply, NodeRegularShape * pShape);
	static BOOL ApplyDefaultAttributes(NodeRegularShape * pShape);

private:
	// The member variables
//	Document *		m_pDoc;
//	Spread *		m_pSpread;
//	DocColour *		m_pDocColour;
//	KernelBitmap *	m_pBitmap;

	// Versions of the parameters used in the drag and drop process
//	KernelBitmap *	m_pDroppedBitmap;
//	DocColour *		m_pDroppedDocColour;
};

#endif
#endif // INC_BACKGROUND_H
