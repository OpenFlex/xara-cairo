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

// newcol.h - The NewColourDlg class

#ifndef INC_NEWCOL
#define INC_NEWCOL



// Prototypes
class IndexedColour;
class DocColour;
class ColourList;
class ColourDropDown;


#define OPTOKEN_NEWCOLOURDLG _T("NewColourDlg")

typedef enum
{
	NEWCOLOUR_NAMEDORUNNAMED,		// NOTE: MUSTBENAMED is always forced TRUE now!
	NEWCOLOUR_MUSTBENAMED,
	NEWCOLOUR_MUSTBEUNNAMED
} NewColourDlgType;


/********************************************************************************************

>	class NewColourDlg: public DialogOp

	Author:		Jason_Williams (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/9/95
	Purpose:	Allows the user to create a new colour (based on another one)

	Notes:		Call one of the InvokeDialog overloads to show the dialogue

********************************************************************************************/

class NewColourParam : public OpParam		// Internal parameter-passing class
{
CC_DECLARE_MEMDUMP(NewColourParam)

public:
	ColourList		*TheList;
	IndexedColour	*TheColour;
	NewColourDlgType TheFlags;
	BOOL			 Result;
public:
	NewColourParam()	\
				{ TheList = NULL; TheColour = NULL; TheFlags = NEWCOLOUR_NAMEDORUNNAMED; Result = FALSE; }

	NewColourParam(ColourList *ParentList, IndexedColour *ColourToEdit, NewColourDlgType Flags)	\
				{ TheList = ParentList; TheColour = ColourToEdit; TheFlags = Flags; Result = FALSE; }
};



class NewColourDlg : public DialogOp
{         
CC_DECLARE_DYNCREATE(NewColourDlg)

public:		// External inteface
	static BOOL InvokeDialog(ColourList *ParentList, IndexedColour *SourceAndResult,
											NewColourDlgType Flags = NEWCOLOUR_NAMEDORUNNAMED);


public:		// DialogOp interface
	NewColourDlg();
	virtual ~NewColourDlg();

	void DoWithParam(OpDescriptor*, OpParam*);
	BOOL Create(); 

	static const INT32 IDD;
	static const CDlgMode Mode;

	static OpState GetState(String_256*, OpDescriptor*);	
	static BOOL Init();                        

	virtual MsgResult Message(Msg* Message);

protected:
	void ShadeControls(void);	// Ensures controls are shaded appropriately for the current selections
	void SetNameText(void);		// Sets the name field appropriately for the selection

	void CommitDetails(BOOL Force = FALSE, BOOL ForceMakeShade = FALSE);
/*
	void CommitDetails(UINT32 ForceRadio1 = 0, UINT32 ForceRadio2 = 0);
*/
								// (Reads from the dialogue to) commit the choices, and End()s

protected:	// Data members
	NewColourParam *Info;

	static BOOL MakeShade;
/*
	static UINT32 LastRadio1;		// Memories of the last radio button settings used
	static UINT32 LastRadio2;
*/
	String_256 AutoName;		// The name we last auto-generated (so we can detect when the user
								// has set their own name in the field)

	ColourDropDown *ParentDropDown;		// The dropdown list of available parent colours
}; 


#endif

