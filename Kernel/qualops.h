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


// header for Quality operations

#ifndef INC_QUALOPS
#define	INC_QUALOPS

//#include "ops.h" - in camtypes.h [AUTOMATICALLY REMOVED]
//#include "opdesc.h" - in camtypes.h [AUTOMATICALLY REMOVED]



#define OPTOKEN_QUALITYSLIDER _T("QualitySlider")


// these are the constants used for setting the quality level. These are intimitely
// linked to  quality.cpp, of which OpQuality is a friend.

#define	QUALITY_LEVEL_ANTI		110
#define	QUALITY_LEVEL_NORMAL	100
#define	QUALITY_LEVEL_SIMPLE	50
#define	QUALITY_LEVEL_OUTLINE	10


class QualitySliderDescriptor : public OpDescriptor
{
	CC_DECLARE_DYNAMIC(QualitySliderDescriptor)

public:
	QualitySliderDescriptor(
						 	UINT32 toolID,                    // Tool (Module) Identifier
						 	UINT32 txID,                      // String Resource ID
						 	CCRuntimeClass* Op,				// pointer to the Op's runtime class object
						 	TCHAR* tok,						// pointer to the token string
						 	pfnGetState gs,					// pointer to the GetState function
						 	UINT32 helpId = 0,				// help identifier 
						 	UINT32 bubbleID = 0,				// string resource for bubble help
						 	UINT32 resourceID = 0,			// resource ID
						 	UINT32 controlID = 0,				// control ID within resource
						 	BOOL ReceiveMessages = TRUE, 		
						 	BOOL Smart = FALSE, 
						 	BOOL Clean = FALSE 
						   );  
	 

	// Virtual fuunctions called from the default Message handler
	virtual void OnControlCreate(OpDescControlCreateMsg* CreateMsg);
	virtual void OnSliderSet(OpDescControlMsg* SelChangedMsg);
	virtual BOOL OnDocViewMsg(DocView* pDocView, DocViewMsg::DocViewState State);
	
	// Function to help handle the view quality changing
	void OnQualityChanged(DocView* pView);

	// GetState function for the OpDescriptor
	static OpState GetState(String_256* Description, OpDescriptor*);

	// Function to update all the slider controls if the view quality changes
	static void Update();

public:
	INT32 CurrentSliderPos;			// The current position of the slider
};


/********************************************************************************************

>	class OpQuality : public Operation

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	22/4/94
	Purpose:	Operation to set quality level on a DocView
	Notes:		Will be on a dialog somewhere eventually

********************************************************************************************/				

class OpQuality : public Operation
{
	CC_DECLARE_DYNCREATE( OpQuality )

public:

	OpQuality();

	void Do(OpDescriptor*);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);	

private:

	static INT32 ConvertToValue( OpDescriptor* );

};


#endif
