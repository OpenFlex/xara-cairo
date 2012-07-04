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

// SGLayer.h - the LayerSGallery (Layer SuperGallery) class


#ifndef INC_SGLAYER
#define INC_SGLAYER


//#include "sgallery.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "sgtree.h" - in camtypes.h [AUTOMATICALLY REMOVED]

#include "layergal.h"

class DocView;
class Layer;

// WEBSTER - markn 15/1/97
// Don't need this gallery in Webster
// Only need the bits left by ralph
//#ifdef WEBSTER
//	#ifndef EXCLUDE_GALS
//		#define UNDEF_EXCLUDE_GALS	// Remember to undefine EXCLUDE_GALS at the end
//		#define EXCLUDE_GALS
//	#endif
//#endif

#ifndef EXCLUDE_GALS
/***********************************************************************************************

>	class SGDisplayLayer : public SGDisplayItem

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com> (Based on template code by Jason)
	Created:	27/01/95
	Purpose:	This DisplayTree node is used by the Layer SuperGallery
				It is responsible for providing the ability to handle/redraw one Layer
				displayed in said gallery.

	SeeAlso:	LayerSGallery; SuperGallery; SGDisplayItem

***********************************************************************************************/

class CCAPI SGDisplayLayer : public SGDisplayItem
{
friend class SGLayerGroup;		// Allows access to CalculateButtonRects

	CC_DECLARE_DYNAMIC(SGDisplayLayer);

public:
	SGDisplayLayer();
	SGDisplayLayer(Layer *LayerToDisplay);
	~SGDisplayLayer();

	virtual	BOOL HandleEvent(SGEventType EventType, void *EventInfo,
							 SGMiscInfo *MiscInfo);

	// Functions that handle dragging of layers
	virtual void MoveBefore(SGDisplayNode *NodeToMove);
	virtual void MoveAfter(SGDisplayNode *NodeToMove);
	virtual void MoveLayer(SGDisplayNode *NodeToMove,BOOL Before,BOOL ToggleBackground);

protected:	// Internal handlers
	virtual void CalculateMyRect(SGFormatInfo *FormatInfo, SGMiscInfo *MiscInfo);
			// Determines item size for the current DisplayMode and calculates FormatRect

	static void CalculateButtonRects(SGMiscInfo *MiscInfo, DocRect *MyRect,
									 DocRect *VisibleBtn, DocRect *LockedBtn, DocRect *SnapButton = NULL);
			// Chops off two (three) button rects from the given 'myrect'

	virtual void HandleRedraw(SGRedrawInfo *RedrawInfo, SGMiscInfo *MiscInfo);
			// Redraws the item into the current FormatRect

	virtual void DoChangeState(OpLayerGalReason Reason,BOOL NewState);
			// Changes the state of the layer this object displays, in some way

	virtual void ChangeRangeState(SGDisplayLayer *Start, SGDisplayLayer *End,
								  BOOL Range, INT32 WhichButton, SGMiscInfo *MiscInfo);
			// Changes the state (visible or locked) of a range of layers


public:		// Specialisations of this class
	inline Layer *GetDisplayedLayer(void);


protected:		// Special member variables (Used to be private but needed by SGDisplayFrame)
	Layer *TheLayer;

private:		// Special member variables
	static SGDisplayLayer *LastClickedLayer;		// Remembers the last layer clicked on (for shift-clicks)
};



/***********************************************************************************************

>	class SGLayerGroup : public SGDisplayGroup

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/2/95
	Purpose:	This is a display tree group specifically for the layer gallery - it disables
				group things like folding, and provides column headings for the layers display.
	SeeAlso:	SuperGallery; SGDisplayGroup;

***********************************************************************************************/


class CCAPI SGLayerGroup : public SGDisplayGroup
{
	CC_DECLARE_DYNAMIC(SGLayerGroup);

public:
	SGLayerGroup(SuperGallery *ParentGal,
					Document *ParentDoc = NULL, Library *ParentLib = NULL, BOOL IsForeground = TRUE);

	virtual	BOOL HandleEvent(SGEventType EventType, void *EventInfo,
							 SGMiscInfo *MiscInfo);
		// Handles a display list event (redraw, mouse click, etc)

	// Is this group the foreground layer group (TRUE) or the background layer group (FALSE)
	BOOL IsForeground() { return Foreground; }

private:
	BOOL Foreground;
};




/********************************************************************************************

>	inline Layer *SGDisplayLayer::GetDisplayedLayer(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com> (Based on template code by Jason)
	Created:	27/1/95

	Returns:	A pointer to the Layer which this Display Item is used to display.
			
	Purpose:	To find out the Layer this object is responsible for displaying

********************************************************************************************/

Layer *SGDisplayLayer::GetDisplayedLayer(void)
{
	return(TheLayer);
}



#endif


/***********************************************************************************************

>	class LayerSGallery : public SuperGallery

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com> (Based on template code by Jason)
	Created:	27/1/95 (Based on the Colour SGallery code)
	Purpose:	The Layer SuperGallery class

	Notes:		SuperGalleries are specced in a number of docs including
					specs\sgallery.doc ("super" gallery extensions)
					specs\propui.doc  (gallery basic ui)
				There is also howtouse\sgallery.doc which describes creating a supergallery

	SeeAlso:	SuperGallery; SGDisplayLayer

***********************************************************************************************/

#ifdef EXCLUDE_GALS
class LayerSGallery : public Operation
#else
class LayerSGallery : public SuperGallery
#endif
{
	CC_DECLARE_DYNCREATE(LayerSGallery)

public:
	LayerSGallery();
	~LayerSGallery();

#ifndef EXCLUDE_GALS
	virtual MsgResult Message(Msg* Message);


protected:				// Overridden upcall methods
	virtual BOOL PreCreate(void);
	virtual BOOL PostCreate(void);

	virtual BOOL ApplyAction(SGActionType Action);

	virtual void DoShadeGallery(BOOL ShadeIt);

	// handles the copying of items between groups via item drags
	virtual SGDisplayItem *CopyDisplayItem(SGDisplayItem *SourceItem, 
								SGDisplayGroup *DestGroup,
								SGDisplayItem *TargetPosition = NULL);


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


public:
	inline Spread *GetSelectedSpread(void);
			// Returns the spread which the layer gallery is currently using


protected:
	Spread	 		*pSpread;			// The Current spread
	Document 		*pDoc;				// The Current document
	SGDisplayGroup  *DisplayForeground;	// Group of foreground layers
	SGDisplayGroup  *DisplayBackground;	// Group of background layers
	BOOL			m_NewDocBorn;		// Flag to determine when a new doc. is born.		

protected:		// Internal methods (directly ported from old LayerGallery class)
	virtual void NewSelectedSpread(Spread* pNewSelSpread = NULL);
	virtual void EnsureSelSpreadSelectionIntegrity();
#endif
public:			// Public so SGDisplayLayer items can call them
	static void ForceRedrawLayer(Document* pDoc,Layer* pLayer);
	static void MakeActiveLayer(Layer* pNewActiveLayer, BOOL TellAll = TRUE);
	static void EnsureActiveLayerIntegrity(Spread* pSpread,Layer** ppActiveLayer = NULL);

public:			// Public access functions for everybody who wants 'em
	static void SetActive(Document* pDoc,Layer* pLayer,BOOL state);
	static void MakeTopLayerActive(Spread* pSpread);
	static String_256 CreateUniqueLayerID(Spread* pSpread);

#ifndef EXCLUDE_GALS
protected:
	virtual void EnsureActiveLayerIntegrity();
	virtual BOOL CheckVarsAreValid();

	virtual SGDisplayLayer *GetSelectedLayerGalItem();

	virtual BOOL HasLayerGotChildren(Layer* pLayer);
 
	virtual BOOL PrepareToDelete(void);
	virtual BOOL DoDeleteSelection(void);

	virtual void DoCreateNewItem(void);
	virtual void DoChangeName();
	virtual void DoCopyLayer();
	virtual void DoLayerProperties();
	virtual void DoCreateGuideLayer();
	virtual void DoChangeLayerStatus(Layer* pLayer, const LayerStatus& NewStatus);

	virtual void DoMoveLayer(MoveLayerType Reason);

protected: // Used to be private but needed by FrameSGallery
	virtual INT32 GetGuideLayerState(DocView* pDocView);
	INT32 OldGuideLayerState;
	INT32 NewGuideLayerState;
	virtual BOOL IsSelectedItemGuideLayer();

public:
	static void DoChangeVisible(Layer* pLayer,BOOL Visible);
	static void DoChangeLocked(Layer* pLayer,BOOL Locked);
	virtual void DoChangeAllVisible(BOOL AllVisible);
	virtual void DoChangeMultilayer(BOOL Multilayer);

	virtual void DoChangeLayerState(Layer* pLayer,OpLayerGalReason Reason,BOOL NewState);

	static BOOL DoMoveSelectionToActiveLayer();

protected:

	// Function to determine the document mode.
	BOOL IsLayerMode(Document* pDoc);		

	// Function to close the frame gallery
	BOOL CloseLayerGallery();

	// Function to open the Layer gallery
	BOOL OpenFrameGallery();

	// Access functions to determine when a new document is born.
	void SetNewDocBorn(BOOL Val)	{ m_NewDocBorn = Val;  }
	BOOL GetNewDocBorn()			{ return m_NewDocBorn; }
	
#endif
};


#ifndef EXCLUDE_GALS


/********************************************************************************************

>	inline Spread *LayerSGallery::GetSelectedSpread(void)

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/1/95

	Returns:	A pointer to the spread that the layer gallery regards as 'current'

	Purpose:	To find the current layer gallery spread

********************************************************************************************/

Spread *LayerSGallery::GetSelectedSpread(void)
{
	return(pSpread);
}

#endif

// WEBSTER - markn 15/1/97
// Do we need to undefine EXCLUDE_GALS?
//#ifdef UNDEF_EXCLUDE_GALS
//#undef EXCLUDE_GALS
//#undef UNDEF_EXCLUDE_GALS
//#endif

#endif //INC_SGLAYER

