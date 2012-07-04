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


#ifndef INC_RECTANGLE
#define INC_RECTANGLE


#include "regshape.h"
//#include "simon.h"

#define OPTOKEN_RECTANGLE 	_T("RectangleTool")


/********************************************************************************************

>	class RectangleTool : public QuickShapeBase

	Author:		Peter_Arnold (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/03/95
	Purpose:	The QuickShape Rectangle tool.

********************************************************************************************/

class CCAPI RectangleTool : public QuickShapeBase
{
CC_DECLARE_MEMDUMP(RectangleTool);

public:
	RectangleTool();
	~RectangleTool();

	BOOL Init();
	void Describe(void* InfoPtr);
	UINT32 GetID() { return TOOLID_RECTANGLE; };

	// The creation mode functions
	INT32 GetNumSides() {return 4;};						
	INT32 GetCreationMode() {return CreationMode;};
	BOOL GetPolygon() {return TRUE;};
	BOOL GetStellation() {return FALSE;};
	BOOL GetCurved() {return FALSE;};
	void SetNumSides(INT32 NewValue) {};
	void SetCreationMode(INT32 NewValue) {CreationMode = NewValue;};
	void SetPolygon(BOOL NewValue) {};
	void SetStellation(BOOL NewValue) {};
	void SetCurved(BOOL NewValue) {};
	BOOL ForcePolygonToGrey() {return FALSE;};
	BOOL ForceEllipseToGrey() {return TRUE;};
	BOOL ForceStellationToGrey() {return TRUE;};
	BOOL ForceCurvatureToGrey() {return FALSE;};
	BOOL ForceNumSidesToGrey() {return TRUE;};
	BOOL DoesPolygonExist() {return FALSE;};
	BOOL DoesEllipseExist() {return FALSE;};
	BOOL DoesStellationExist() {return FALSE;};
	BOOL DoesCurvatureExist() {return TRUE;};
	BOOL DoesReformSidesExist() {return FALSE;};
	BOOL DoesNumSidesExist() {return FALSE;};
	BOOL IsInterestingShape(NodeRegularShape* pShape);
	INT32 GetShapesToAffect() {return EditRegularShapeParam::AFFECT_RECTANGLES;};
	INT32 GetCursorID() {return _R(IDC_RECTTOOLCURSOR);};
	INT32 GetShapeID() {return _R(IDS_RECTANGLE_DESCRS);};
	INT32 GetShapesID() {return _R(IDS_RECTANGLE_DESCRP);};
									    
	virtual BOOL IsRectangle() {return TRUE;};

private:
	INT32 CreationMode;

	// Standard tool static vars
	static 	TCHAR* FamilyName;				
	static 	TCHAR* ToolName;					
	static 	TCHAR* Purpose;					
	static 	TCHAR* Author;					
};


#endif	// INC_Rectangle




