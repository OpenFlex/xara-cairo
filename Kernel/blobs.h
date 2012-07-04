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

// Provides a class for dealing with Camelots various Blob types

#ifndef INC_BLOBS
#define INC_BLOBS

//#include "doccoord.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "pump.h" - in camtypes.h [AUTOMATICALLY REMOVED]

class NodeRenderable;
class RenderRegion;
class DocRect;
class Spread;
class Tool_v1;


//static BOOL bToolBlobsAreOff;

/********************************************************************************************

>	class BlobStyle

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/6/94
	Purpose:	Class for holding which blobs are required and which are not. Objects of
				this class are passed into the Blob Manager to tell it which of the blobs
				a tool wants to display and should be used something like this :-
				MonoOn
				BlobStyle ThisToolsBlobs;
				ThisToolsBlobs.Object = TRUE;		// Display Object blobs in this tool
				ThisToolsBlobs.Fill = TRUE;			// Display Fill blobs in this tool
				BlobManager->ToolInterest(ThisToolsBlobs);
				MonoOff
	SeeAlso:	BlobManager

********************************************************************************************/

class BlobStyle
{
public:
	// Constructors
	BlobStyle();
	BlobStyle(	BOOL BObject, BOOL BArtistic = FALSE, BOOL BFill = FALSE,
				BOOL BTiny = FALSE, BOOL BPen = FALSE, BOOL BToolObject = FALSE, BOOL BEffect = FALSE );
	~BlobStyle() {}


/********************************************************************************************

>	BlobStyle::SetAll()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/6/94
	Purpose:	Sets all the blobs type flags to TRUE

********************************************************************************************/
	void SetAll()  { Object = Artistic = Fill = Tiny = Pen = ToolObject = Effect = TRUE; }


/********************************************************************************************

>	void BlobStyle::SetNone()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	23/6/94
	Purpose:	Sets all the blobs styles to false

********************************************************************************************/
	void SetNone() { Object = Artistic = Fill = Tiny = Pen = ToolObject = Effect = FALSE; }

	// Vars
	UINT32 Fill		: 1;
	UINT32 Object	: 1;
	UINT32 Artistic	: 1;
	UINT32 Tiny		: 1;
	UINT32 Pen		: 1;
	UINT32 ToolObject: 1;
	UINT32 Effect	: 1;
};



/********************************************************************************************

>	class BlobManager : public MessageHandler

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	15/6/94
	Purpose:	Class to Manage the various types of selection blobs in Camelot. Currently
				Camelot knows about the following forms of selection blob :-

				Fill Blobs - The blobs rendered by things like Graduated fills to show
				where the fill starts and ends, it direction etc.

				Object Blobs - The blobs that appear to edit the shape of an object. ie
				the control point blobs on a path

				Artistic Blobs - Used to edit information such as pressure details along
				shapes.

				Tiny Blobs - the Blob that is displayed by an object when it is the
				Boundary selection mode of the selector tool to indicate that it is one
				of the selected objects.

				ToolObject Blobs -	These blobs are displayed and used by an object only
									when a specific tool is selected. They are similar to
									object blobs except that the _object_ has the final say
									in whether they are rendered/used or not.

********************************************************************************************/

class BlobManager : public MessageHandler
{
	// Give my name in memory dumps
	CC_DECLARE_MEMDUMP(BlobManager);

public:
	// Constructors etc
	BlobManager();
	~BlobManager() {}

	// Functions to allow the tools to register their interest in various groups of blobs
	void ToolInterest(BlobStyle);
	void AddInterest(BlobStyle);
	void RemoveInterest(BlobStyle);

	// Find out what the current blob interest is
	BlobStyle GetCurrentInterest(BOOL bIgnoreOffState = FALSE);

	// Functions to stop and start the rendering of blobs during periods of uncertainy
	void BlobRenderingOff(BOOL Redraw);
	void BlobRenderingOn(BOOL Redraw);

	// Functions to find out about the size of a blob (not a cow)
	INT32 GetBlobSize();
	void GetBlobRect( const DocCoord &Centre, DocRect* Rect, BOOL MFill = FALSE,
								BlobType eBlobType = BT_SELECTEDLARGEST);

	// Functions to render blobs
	void Render(DocRect* Rect, Spread *pSpread);
	void RenderOn(DocRect* Rect, Spread *pSpread);
	void RenderOff(DocRect* Rect, Spread *pSpread);

	void RenderMyBlobs(DocRect* Rect, Spread *pSpread, NodeRenderable* pNode);
	void RenderMyBlobsOn(DocRect* Rect, Spread *pSpread, NodeRenderable* pNode);
	void RenderMyBlobsOff(DocRect* Rect, Spread *pSpread, NodeRenderable* pNode);

	void RenderObjectBlobs(DocRect* Rect, Spread *pSpread, NodeRenderable* pNode);
	void RenderObjectBlobsOn(DocRect* Rect, Spread *pSpread, NodeRenderable* pNode);
	void RenderObjectBlobsOff(DocRect* Rect, Spread *pSpread, NodeRenderable* pNode);

	void RenderToolBlobsOn(Tool_v1* pTool, Spread* pSpread, DocRect* pClipRect);
	void RenderToolBlobsOff(Tool_v1* pTool, Spread* pSpread, DocRect* pClipRect);

	BOOL IsRemovingBlobs() { return RemovingBlobs; }

protected:
	// Functions to help the blob manager with the rendering of the blobs
	void RenderRequiredBlobs(NodeRenderable*, RenderRegion*);
	void RenderSpecificBlobs(NodeRenderable*, RenderRegion*, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL);

	void RenderRequiredBlobsOnSelection(DocRect* Rect);
	void RenderSpecificBlobsOnSelection(DocRect* Rect, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL);

	BOOL NeedToRenderSelectionBlobs(DocRect* Rect);
	BOOL NeedToRenderNodeBlobs(DocRect* Rect, Spread *pSpread, NodeRenderable* pNode);

protected:
	// message handler
	MsgResult Message(Msg* Msg);

// vars
protected:
	// Which blobs are we displaying?
	BOOL IsFillBlob;
	BOOL IsObjectBlob;
	BOOL IsArtisticBlob;
	BOOL IsTinyBlob;
	BOOL IsPenBlob;
	BOOL IsToolObjectBlob;
	BOOL IsEffectBlob;

	// should we be drawing blobs at all
	BOOL DrawBlobsAtAll;

	// Flag to tell whether blobs are being removed or not
	BOOL RemovingBlobs;
	BOOL bToolBlobsAreOff;
};

#endif  // INC_BLOBS


