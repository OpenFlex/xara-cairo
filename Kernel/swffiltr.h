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

#ifndef INC_SWF_EXPORT
#define INC_SWF_EXPORT

#include "swfrndr.h"	// Definition of FlashRenderRegion.

/********************************************************************************************

>	class SWFFilter : public VectorFilter

	Author:		Graeme_Sutherland (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/08/99
	Purpose:	Enables Camelot to export images in the Flash (SWF) file format.
	SeeAlso:	VectorFilter

********************************************************************************************/

class FlashFilter : public VectorFilter
{
	friend class FlashRenderCallback;

	CC_DECLARE_DYNAMIC( FlashFilter );

public:
	FlashFilter( void );							// Constructor.
	BOOL Init( void );								// Initialise the filter.

	BOOL DoImport( SelOperation *Op,				// Do an import.
					CCLexFile* pFile, 
					Document *DestDoc,
					BOOL AutoChosen,
					ImportPosition *Pos,
					KernelBitmap** ppImportedBitmap,
					DocCoord* pPosTranslate,
					String_256* URL );

	BOOL DoExport( Operation* pOp,					// Export file.
					CCLexFile* pFile,
					PathName* pPath, 
					Document* TheDocument,
					BOOL ShowOptions );

	BOOL PrepareToExport( CCLexFile* pFile,
						   Spread* pSpread );

	virtual BOOL ExportSelectionOnly(BOOL MaskedRender = FALSE);	// Should only export selected nodes.
	virtual BOOL ExportVisibleLayersOnly();							// Should hidden layers be exported.

	// Gets the colour of a page background.
	static DocColour GetPageColour( Spread	*pSpread,
									 Node** pBackground );

protected:
	// Custom export render method.
	virtual BOOL WriteNodes( RenderRegion *pRegion,
							  ExportDC *pDC,
							  BOOL VisibleLayersOnly,
							  BOOL CheckSelected,
							  BOOL ShowProgress );

private:
	void CleanUpAfterExport( BOOL Success );		// Tidy up after export.

	// Functions for extracting button state details.
	LayerState GetButtonState( Node *pNode );		// Determine whether pNode is a button.
	BOOL GetButtonName( Node *pNode,				// Get the name of pNode's button.
						 String_256 &ButtonName );

	// Members
	Node*		mpBackgroundNode;						// Pointer to the background colour node.
	BOOL		mOnlySelected;						// Only render selected nodes.
	DocColour*	mpBackgroundCol;					// Background colour for the image.
	DocRect		mPageRect;							// Bounding rectangle for spread.
};


/********************************************************************************************

>	class FlashRenderCallback : public RenderCallback

	Author:		Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
	Created:	01/12/2004
	Purpose:	Handling callbacks from RenderTree
	Notes:		RenderTree function calls the main function in this class when it's about
				to render any Node.

********************************************************************************************/

class FlashRenderCallback : public RenderCallback
{
public:
	FlashRenderCallback(FlashFilter* pFilter, FlashRenderRegion* pFRR, BOOL bVisibleLayersOnly, BOOL bSelectedOnly, Node* pBackgroundNode)
	{
		m_pFilter = pFilter;
		m_pFRR = pFRR;
		m_bVisibleLayersOnly = bVisibleLayersOnly;
		m_bSelectedOnly = bSelectedOnly;
		m_pBackgroundNode = pBackgroundNode;
	}

	virtual BOOL BeforeNode(RenderRegion* pRegion, Node* pNode);
	virtual BOOL BeforeSubtree(RenderRegion* pRegion,
								Node* pNode,
								Node** ppNextNode,
								BOOL bClip,
								SubtreeRenderState* pState);

private:
	FlashFilter* m_pFilter;
	FlashRenderRegion* m_pFRR;
	Node* m_pBackgroundNode;
	BOOL m_bVisibleLayersOnly;
	BOOL m_bSelectedOnly;
};


#endif // INC_SWF_EXPORT
