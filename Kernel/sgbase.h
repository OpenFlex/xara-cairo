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

// SGTEMPLATE.h - the TEMPLATESGallery (TEMPLATE SuperGallery) class


// You must do the following things:
//	1 Copy this file into your own header file, and screw that up, not this! ;-)
//	2 Strip back the topmost line to say '// #Header#' (where # is a dollar sign)
//	3 Change the INC_SGBASE lines below to relevant names
//	4 Do a GLOBAL, CASE SENSITIVE replace of 'TEMPLATE' with your gallery name (eg 'Bitmap')
//	5 Do a CASE SENSITIVE replace of 'DATATYPE' with your gallery type (eg 'KernelBitmap')
//	  (This means a DisplayItem will hold a (KernelBitmap *) pointer, etc - search for
//	  DATATYPE before replacing to see what I mean)
//	6 Do a global CASE SENSITIVE replace of 'AUTHOR' with your name
//	7 Delete these instructional comment lines
// Remember to add this new file to all.lst and kernel.mak

#ifndef INC_SGBASE
#define INC_SGBASE




class TEMPLATE;		// TO DO: You may or not need this
class DATATYPE;


/***********************************************************************************************

>	class SGDisplayDATATYPE : public SGDisplayItem

	Author:		Unattributed (Xara Group Ltd) <camelotdev@xara.com> (Based on template code by Jason)
	Created:	27/01/95
	Purpose:	This DisplayTree node is used by the TEMPLATE SuperGallery
				It is responsible for providing the ability to handle/redraw one DATATYPE
				displayed in said gallery.

	SeeAlso:	TEMPLATESGallery; SuperGallery; SGDisplayItem

***********************************************************************************************/

class CCAPI SGDisplayDATATYPE : public SGDisplayItem
{
	CC_DECLARE_DYNAMIC(SGDisplayDATATYPE);

public:
	SGDisplayDATATYPE();
	SGDisplayDATATYPE(DATATYPE *DATATYPEToDisplay);

	virtual	BOOL HandleEvent(SGEventType EventType, void *EventInfo,
							 SGMiscInfo *MiscInfo);

	virtual void GetNameText(String_256 *Result);
			// Returns the name text for this item


protected:	// Internal handlers
	virtual void CalculateMyRect(SGFormatInfo *FormatInfo, SGMiscInfo *MiscInfo);
			// Determines item size for the current DisplayMode and calculates FormatRect

	virtual void HandleRedraw(SGRedrawInfo *RedrawInfo, SGMiscInfo *MiscInfo);
			// Redraws the item into the current FormatRect


public:		// Specialisations of this class
	inline DATATYPE *GetDisplayedDATATYPE(void);


private:		// Special member variables
	DATATYPE *TheDATATYPE;
};



/********************************************************************************************

>	inline DATATYPE *SGDisplayDATATYPE::GetDisplayedDATATYPE(void)

	Author:		Unattributed (Xara Group Ltd) <camelotdev@xara.com> (Based on template code by Jason)
	Created:	27/1/95

	Returns:	A pointer to the DATATYPE which this Display Item is used to display.
			
	Purpose:	To find out the DATATYPE this object is responsible for displaying

********************************************************************************************/

DATATYPE *SGDisplayDATATYPE::GetDisplayedDATATYPE(void)
{
	return(TheDATATYPE);
}






/***********************************************************************************************

>	class TEMPLATESGallery : public SuperGallery

	Author:		Unattributed (Xara Group Ltd) <camelotdev@xara.com> (Based on template code by Jason)
	Created:	27/1/95 (Based on the Colour SGallery code)
	Purpose:	The TEMPLATE SuperGallery class

	Notes:		SuperGalleries are specced in a number of docs including
					specs\sgallery.doc ("super" gallery extensions)
					specs\propui.doc  (gallery basic ui)
				There is also howtouse\sgallery.doc which describes creating a supergallery

	SeeAlso:	SuperGallery; SGDisplayTEMPLATE

***********************************************************************************************/

class TEMPLATESGallery : public SuperGallery
{
	CC_DECLARE_DYNCREATE(TEMPLATESGallery)

public:
	TEMPLATESGallery();
	~TEMPLATESGallery();

	virtual MsgResult Message(Msg* Message);


protected:				// Overridden upcall methods
	virtual BOOL PreCreate(void);

	virtual BOOL ApplyAction(SGActionType Action);


protected:		   		// Personal/Internal methods
	void CreateNewSubtree(Document *ParentDoc, SGDisplayGroup *ExistingGroup = NULL);
			// Creates a new subtree group to display the TEMPLATEs for the given document
			// If ExistingGroup != NULL, that group will be re-cached for the given doc
};





/********************************************************************************************

>	class OpDisplayTEMPLATEGallery: public Operation

	Author:		Unattributed (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/2/95 (Based on the Colour SGallery code)

	Purpose:	Displays the TEMPLATE gallery.
				This op can be attached to a menu, button or keypress
	SeeAlso:	TEMPLATESGallery

********************************************************************************************/

#define OPTOKEN_DISPLAYTEMPLATEGALLERY _T("DisplayTEMPLATEGallery")

class CCAPI OpDisplayTEMPLATEGallery: public Operation
{         
	CC_DECLARE_DYNCREATE( OpDisplayTEMPLATEGallery );

public:
	static BOOL		Init();				
	static OpState	GetState(String_256*, OpDescriptor*);		
    void 			Do(OpDescriptor*);

private:
	static DialogBarOp *FindGallery(void);
			// Finds the TEMPLATE gallery class instance
};  


#endif

