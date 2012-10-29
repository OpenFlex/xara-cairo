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


// SGFrame.h - the FrameSGallery (Frame SuperGallery) class
// Looks remarkably like the layer gallery but looks aren't everything!

#ifndef INC_SGFRAME
#define INC_SGFRAME


#include "layergal.h"

#include "sglayer.h"
#include "bmpprefs.h"  // For PALETTE Type

class DocView;
class UndoableOperation;

#ifndef EXCLUDE_GALS
/***********************************************************************************************

>	class SGDisplayFrame : public SGDisplayLayer

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com> (Based on Jason's Layer gallery code)
	Created:	16/4/97 (Based on Jason's Layer gallery code)
	Purpose:	This DisplayTree node is used by the Layer SuperGallery
				It is responsible for providing the ability to handle/redraw one Layer
				displayed in said gallery.

	SeeAlso:	FrameSGallery; SuperGallery; SGDisplayItem

***********************************************************************************************/

class CCAPI SGDisplayFrame : public SGDisplayLayer
{
friend class SGLayerGroup;		// Allows access to CalculateButtonRects
friend class SGFrameGroup;		// Allows access to CalculateButtonRects

	CC_DECLARE_DYNAMIC(SGDisplayFrame);

public:
	SGDisplayFrame();
	SGDisplayFrame(Layer *LayerToDisplay);
	~SGDisplayFrame();

	virtual	BOOL HandleEvent(SGEventType EventType, void *EventInfo,
							 SGMiscInfo *MiscInfo);

	virtual void MoveLayer(SGDisplayNode *NodeToMove,BOOL Before,BOOL ToggleBackground);

protected:	// Internal handlers
	virtual void HandleRedraw(SGRedrawInfo *RedrawInfo, SGMiscInfo *MiscInfo);
			// Redraws the item into the current FormatRect

	virtual void DoChangeState(OpLayerGalReason Reason,BOOL NewState);
			// Changes the state of the layer this object displays, in some way

	virtual void ChangeRangeState(SGDisplayFrame *Start, SGDisplayFrame *End,
								  BOOL Range, INT32 WhichButton, SGMiscInfo *MiscInfo);
			// Changes the state (visible or locked) of a range of layers


private:		// Special member variables
	static SGDisplayFrame *LastClickedLayer;		// Remembers the last layer clicked on (for shift-clicks)
};



/***********************************************************************************************

>	class SGFrameGroup : public SGLayerGroup

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com> (Based on Jason's Layer gallery code)
	Created:	16/4/97 (Based on Jason's Layer gallery code)
	Purpose:	This is a display tree group specifically for the layer gallery - it disables
				group things like folding, and provides column headings for the layers display.
	SeeAlso:	SuperGallery; SGDisplayGroup;

***********************************************************************************************/


class CCAPI SGFrameGroup : public SGLayerGroup
{
	CC_DECLARE_DYNAMIC(SGFrameGroup);

public:
	SGFrameGroup(SuperGallery *ParentGal,
					Document *ParentDoc = NULL, Library *ParentLib = NULL, BOOL IsForeground = TRUE);

	virtual	BOOL HandleEvent(SGEventType EventType, void *EventInfo,
							 SGMiscInfo *MiscInfo);
		// Handles a display list event (redraw, mouse click, etc)

	// Is this group the foreground layer group (TRUE) or the background layer group (FALSE)
	BOOL IsForeground() { return Foreground; }

private:
	BOOL Foreground;
};

#endif


/***********************************************************************************************

>	class FrameSGallery : public LayerSGallery

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com> (Based on Jason's Layer gallery code)
	Created:	16/4/97 (Based on Jason's Layer gallery code)
	Purpose:	The Layer SuperGallery class

	Notes:		SuperGalleries are specced in a number of docs including
					specs\sgallery.doc ("super" gallery extensions)
					specs\propui.doc  (gallery basic ui)
				There is also howtouse\sgallery.doc which describes creating a supergallery

	SeeAlso:	SuperGallery; SGDisplayFrame

***********************************************************************************************/

#ifdef EXCLUDE_GALS
class FrameSGallery : public Operation
#else
class FrameSGallery : public LayerSGallery
#endif
{
	CC_DECLARE_DYNCREATE(FrameSGallery)

public:
	FrameSGallery();
	~FrameSGallery();

#ifndef EXCLUDE_GALS
	virtual MsgResult Message(Msg* Message);


protected:				// Overridden upcall methods
	virtual BOOL PostCreate(void);

	virtual BOOL ApplyAction(SGActionType Action);

	virtual void DoShadeGallery(BOOL ShadeIt);

public:			// Overridden Command interface (for Ops and menu support)
	virtual BOOL InitMenuCommands(void);
		// Called on startup to initialise any desired menu commands. Will make repeated calls
		// to InitMenuCommand(), below.

	virtual BOOL BuildCommandMenu(GalleryContextMenu *TheMenu, SGMenuID MenuID);
		// Builds the command menu for the given menu pop-up (over an item, or options button)

	virtual OpState GetCommandState(StringBase *CommandID, String_256 *ShadeReason);
		// Returns an OpState indicating the state of this command, much like an Op GetState

	virtual void DoCommand(StringBase *CommandID);
		// Attempts to "do" the given command. Should call down to the base class to handle
		// any commands it can't deal with.


public:		   		// Personal/Internal methods
	virtual void CreateNewSubtree(Document *ParentDoc, SGDisplayGroup *ExistingGroup = NULL);
			// Creates a new subtree group to display the Layers for the given document
			// If ExistingGroup != NULL, that group will be re-cached for the given doc


protected:		// Internal methods (directly ported from old LayerGallery class)
	virtual void EnsureSelSpreadSelectionIntegrity();
#endif

public:			// Public so SGDisplayLayer items can call them
	static void MakeActiveLayer(Layer* pNewActiveLayer,	UndoableOperation * pUndoOp = NULL);
	
public:			// Public access functions for everybody who wants 'em
	static void SetActive(Document* pDoc,Layer* pLayer,BOOL state);
	static String_256 CreateUniqueLayerID(Spread* pSpread, const String_256 * pBaseName = NULL);

	// This function should be called before any frame related actions are carried out
	// It will ensure that all the visible layers are frame layers
	static BOOL EnsureFrameLayerIntegrity(Spread* pSpread);
	static BOOL DoHideNode(Node* pNodeToHide);

#ifndef EXCLUDE_GALS
protected:
	virtual SGDisplayLayer *GetSelectedLayerGalItem();

	virtual void DoMoveLayer(MoveLayerType Reason);

	virtual BOOL DoDeleteSelection(void);
	virtual void DoCreateNewItem(void);
	virtual void DoCopyLayer();

	// Special frame gallery related items
	virtual BOOL DoSaveAnimation();
	virtual BOOL DoPreviewAnimation();
	virtual	BOOL DoFrameProperties();
	virtual	BOOL DoRegenerateFrames();
	virtual	BOOL DoRegenerateSingleFrame();

	// Ensure that the frame related buttons are greyed/ungreyed
	BOOL UpdateFrameRelatedButtons();

	// Function to determine the document mode.
	BOOL IsFrameMode(Document* pDoc);		

	// Function to close the frame gallery
	BOOL CloseFrameGallery();

	// Function to open the Layer gallery
	BOOL OpenLayerGallery();

	// Access functions to determine when a new document is born.
	void SetNewDocBorn(BOOL Val)	{ m_NewDocBorn = Val;  }
	BOOL GetNewDocBorn()			{ return m_NewDocBorn; }

public:
	// new specific frame gallery related functions
	static void DoChangeSolid(Layer* pLayer,BOOL Solid);
	static void DoChangeOverlay(Layer* pLayer,BOOL Overlay);
	// solid and overlay flags have changed or a new layer has become active
	// so fix up the visibility and locked nature of the other layers
	static void FixOtherLayers(Spread* pSpread);
	static void FixOtherLayersFromActive(Layer * pActiveLayer, UndoableOperation * pUndoOp = NULL);

protected:
	BOOL	m_NewDocBorn;	// Flag to determine when a new doc. is born.		

#endif
};

#endif

